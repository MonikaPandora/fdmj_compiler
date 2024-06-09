#include "regalloc.h"
#include "ig.h"

#define ARCH_SIZE 4
#define NUM_INT_REGS 11
#define NUM_FLOAT_REGS 32
#define NUM_FOR_SPILL 3
#define NUM_START_INT_CALLEE 4
#define NUM_START_FLOAT_CALLEE 16

static Temp_tempList used_callee_saved;

static G_table simplify;    // stack used for simplify

typedef struct TAB_table_* RA_table;
static RA_table color;   // color table, temp --> reg

typedef struct TAB_table_* RA_off;
static RA_off spill;
AS_instrList ls_for_spill;  // instructions to load and store for actually-spilled temps
static int spill_off;

static void RA_enter(RA_table t, Temp_temp temp, Temp_temp reg) {
    TAB_enter(t, temp, reg);
}

static Temp_temp RA_look(RA_table t, Temp_temp temp) {
    return TAB_look(t, temp);
}

static void RA_off_enter(RA_off t, Temp_temp temp, int off) {
    TAB_enter(t, temp, (void*)(long long)off);
}

static int RA_off_look(RA_off t, Temp_temp temp) {
    return (long long)TAB_look(t, temp);
}

typedef struct {
    enum {
        COLOR,
        SPILL
    } kind;
    int off;
    G_nodeList pred;
    G_nodeList succ;
}simplify_entry_;

typedef simplify_entry_* simplify_entry;

static simplify_entry Simp_Color_Entry(G_node n) {
    simplify_entry p = (simplify_entry)checked_malloc(sizeof(*p));
    p->kind = COLOR;
    p->pred = G_pred(n);
    p->succ = G_succ(n);
    return p;
}

static simplify_entry Simp_Spill_Entry(G_node n) {
    simplify_entry p = (simplify_entry)checked_malloc(sizeof(*p));
    p->kind = SPILL;
    p->pred = G_pred(n);
    p->succ = G_succ(n);
    return p;
}

void rmNode(G_node n) {
    for(G_nodeList pred = G_pred(n); pred; pred = pred->tail)G_rmEdge(pred->head, n);
    for(G_nodeList succ = G_succ(n); succ; succ = succ->tail)G_rmEdge(n, succ->head);
}

void simplify_and_spill(G_nodeList ig_local) {
    bool finished = FALSE;
    while(!finished) {
        finished = TRUE;
        bool all_cannot_simplify = TRUE;
        G_node spill = NULL;
        for(G_nodeList i = ig_local; i; i = i->tail) {
            G_node n = i->head;
            Temp_temp t = G_nodeInfo(n);
            if(t->num < 99 || G_look(simplify, n))continue; // skip pre-colored or simplified nodes
            finished = FALSE;
            int k = t->type == T_int ? NUM_INT_REGS - NUM_FOR_SPILL : NUM_FLOAT_REGS - NUM_FOR_SPILL;
            if(G_degree(n) < k){
                G_enter(simplify, n, Simp_Color_Entry(n));

                rmNode(n);

                all_cannot_simplify = FALSE;
            }
            else spill = n;
        }
        if(!finished && all_cannot_simplify) {
            assert(spill);

            G_enter(simplify, spill, Simp_Spill_Entry(spill));

            rmNode(spill);
        }
    }
}

Temp_tempList conflict_registers(G_nodeList pred, G_nodeList succ) {
    Temp_tempList interfered_with = NULL;
    for(; pred; pred = pred->tail){
        Temp_temp reg = RA_look(color, G_nodeInfo(pred->head));
        assert(reg);
        if(reg)interfered_with = Temp_TempList(reg, interfered_with);
        else interfered_with = Temp_TempList(G_nodeInfo(pred->head), interfered_with);
    }
    for(; succ; succ = succ->tail){
        Temp_temp reg = RA_look(color, G_nodeInfo(succ->head));
        if(reg)interfered_with = Temp_TempList(reg, interfered_with);
        else interfered_with = Temp_TempList(G_nodeInfo(succ->head), interfered_with);
    }
    return interfered_with;
}

bool is_callee_saved(Temp_temp reg) {
    int num_regs = reg->type == T_int ? NUM_INT_REGS : NUM_FLOAT_REGS;
    int num_callee_start = reg->type == T_int ? NUM_START_INT_CALLEE : NUM_START_FLOAT_CALLEE;
    return num_callee_start <= reg->num && reg->num < num_regs - NUM_FOR_SPILL;
}

bool is_spill_register(Temp_temp reg) {
    int num_regs = reg->type == T_int ? NUM_INT_REGS : NUM_FLOAT_REGS;
    return num_regs - NUM_FOR_SPILL <= reg->num && reg->num < num_regs;
}

void do_color_spill(G_node n, G_nodeList pred, G_nodeList succ, bool is_spill) {
    Temp_temp t = G_nodeInfo(n);
    Temp_tempList interfered_with = conflict_registers(pred, succ);

    int num_regs = t->type == T_int ? NUM_INT_REGS : NUM_FLOAT_REGS;
    if(!is_spill)num_regs -= NUM_FOR_SPILL; // for spill, there are some special regs, thus subtract that amount for color
    for(int i = 0; i < num_regs; i++) {
        Temp_temp reg = Temp_namedtemp(i, t->type);
        if(!Temp_TempInTempList(reg, interfered_with)) {
            // find an valid regs

            // record the used callee saved
            if(is_callee_saved(reg) && !Temp_TempInTempList(reg, used_callee_saved)){
                used_callee_saved = Temp_TempList(reg, used_callee_saved);
            }
            if(is_spill_register(reg)){
                // actual spill
                // record info into table spill
                RA_off_enter(spill, t, spill_off);
                spill_off += ARCH_SIZE;
            }
            else RA_enter(color, t, reg);
            return;
        }
    }
    // should never be here
    *(int*)0=0;
    assert(0);
}

int count_templist(Temp_tempList lst) {
    int cnt = 0;
    while(lst)cnt++, lst = lst->tail;
    return cnt;
}

void color_and_actual_spill(AS_instrList il) {
    /* step 1: reverse mode color and actual spill */
    _for_in_table(iter, simplify) {
        G_node n = iter->key;
        simplify_entry entry = iter->value;
        G_nodeList pred = entry->pred;
        G_nodeList succ = entry->succ;

        do_color_spill(n, pred, succ, entry->kind == SPILL);
    }

    /* step 2: replace all temps with regs and
               insert instructions for actual spill*/
    AS_instrList prev = NULL;
    int space_for_callee = count_templist(used_callee_saved) * ARCH_SIZE;
    for(AS_instrList cur = il; cur; prev = prev ? prev->tail : cur, cur = cur->tail) {
        AS_instr ins = cur->head;
        if(ins->kind == I_LABEL)continue;

        int spill_pos = 0;
        // for any defines
        for(Temp_tempList dst = ins->u.OPER.dst; dst; dst = dst->tail) {
            Temp_temp reg = RA_look(color, dst->head);
            int off = RA_off_look(spill, dst->head);

            if(reg) {
                // colored nodes
                assert(!off);
                dst->head = reg;
            }
            else if(off) {
                // actually spilled nodes
                // store after any define
                T_type tp = dst->head->type;
                string str_ir = (string)checked_malloc(IR_MAXLEN);
                if(tp == T_int)sprintf(str_ir, "str `s0, [fp, #%d]", off);
                else sprintf(str_ir, "vstr.f32 `s0, [fp, #%d]", off);

                int num_regs = tp == T_int ? NUM_INT_REGS : NUM_FLOAT_REGS;
                int spill_regs_start = num_regs - NUM_FOR_SPILL;
                Temp_temp spill_to = Temp_namedtemp(spill_regs_start + (spill_pos++), tp);
                assert(spill_to < num_regs);

                if(!Temp_TempInTempList(spill_to, used_callee_saved))used_callee_saved = Temp_TempList(spill_to, used_callee_saved);

                AS_instr str_ins = AS_Oper(str_ir, NULL, Temp_TempList(spill_to, NULL), NULL);
                ls_for_spill = AS_InstrList(str_ins, ls_for_spill);
                prev = cur;
                cur = cur->tail = AS_InstrList(str_ins, cur->tail);
                dst->head = spill_to;
            }
            else {
                // pre-colored nodes
                assert(dst->head->num < dst->head->type == T_int ? NUM_INT_REGS : NUM_FLOAT_REGS);
                continue; 
            }
        }

        // for any use
        for(Temp_tempList src = ins->u.OPER.src; src; src = src->tail) {
            Temp_temp reg = RA_look(color, src->head);
            int off = RA_off_look(spill, src->head);

            if(reg) {
                // colored nodes
                assert(!off);
                src->head = reg;
            }
            else if(off) {
                // actually spilled nodes
                // load before any use
                T_type tp = src->head->type;
                string str_ir = (string)checked_malloc(IR_MAXLEN);
                if(tp == T_int)sprintf(str_ir, "ldr `d0, [fp, #%d]", off);
                else sprintf(str_ir, "vldr.f32 `d0, [fp, #%d]", off);

                int num_regs = tp == T_int ? NUM_INT_REGS : NUM_FLOAT_REGS;
                int spill_regs_start = num_regs - NUM_FOR_SPILL;
                Temp_temp spill_to = Temp_namedtemp(spill_regs_start + (spill_pos++), tp);
                assert(spill_to < num_regs);

                if(!Temp_TempInTempList(spill_to, used_callee_saved))used_callee_saved = Temp_TempList(spill_to, used_callee_saved);

                AS_instr str_ins = AS_Oper(str_ir, Temp_TempList(spill_to, NULL), NULL, NULL);
                ls_for_spill = AS_InstrList(str_ins, ls_for_spill);
                prev = prev->tail = AS_InstrList(str_ins, cur);
                src->head = spill_to;
            }
            else {
                // pre-colored nodes
                assert(src->head->num < src->head->type == T_int ? NUM_INT_REGS : NUM_FLOAT_REGS);
                continue; 
            }
        }
    }
}

AS_instrList build_frame(AS_instrList il) {
    AS_instrList head = il;

    AS_instrList in = AS_InstrList(AS_Oper("push {fp, lr}", NULL, NULL, NULL), NULL);
    AS_instrList in_last = in;
    AS_instrList out = NULL;
    in_last = in_last->tail = AS_InstrList(AS_Oper("mov fp, sp", NULL, NULL, NULL), NULL);

    /* used callee saved registers */
    int num_used_callee = 0;
    for(Temp_tempList callee = used_callee_saved; callee; callee = callee->tail) {
        num_used_callee++;
        if(callee->head->type == T_int){
            in_last = in_last->tail = AS_InstrList(AS_Oper("push {`s0}", NULL, Temp_TempList(callee->head, NULL), NULL), NULL);
            out = AS_InstrList(AS_Oper("pop {`d0}", Temp_TempList(callee->head, NULL), NULL, NULL), out);
        }
        else {
            in_last = in_last->tail = AS_InstrList(AS_Oper("vpush.f32 {`s0}", NULL, Temp_TempList(callee->head, NULL), NULL), NULL);
            out = AS_InstrList(AS_Oper("vpop.f32 {`d0}", Temp_TempList(callee->head, NULL), NULL, NULL), out);
        }
    }

    in_last->tail = head;
    head = in;

    string recover_sp = (string)checked_malloc(IR_MAXLEN);
    sprintf(recover_sp, "sub sp, fp, #%d", num_used_callee * ARCH_SIZE);

    // find all ret instructions
    for(AS_instrList prev = in_last; il; il = il->tail, prev = prev->tail) {
        if(!strncmp(il->head->u.OPER.assem, "bx", 2)){
            prev = prev->tail = AS_InstrList(AS_Oper(recover_sp, NULL, NULL, NULL), NULL);
            
            for(AS_instrList lst = out; lst; lst = lst->tail)prev = prev->tail = AS_InstrList(lst->head, NULL);

            prev = prev->tail = AS_InstrList(AS_Oper("pop {fp, lr}", NULL, NULL, NULL), il);
        }
    }

    int num_spilled_temps = 0;
    _for_in_table(iter, spill){
        num_spilled_temps++;
    }


    // for all instruction for actual spill
    for(; ls_for_spill; ls_for_spill = ls_for_spill->tail) {
        string assem = ls_for_spill->head->u.OPER.assem;
        while(*assem != '#')assem++;
        assem++;

        // replace the offset with the true offset
        int off = atoi(assem) + num_used_callee * ARCH_SIZE;
        off = -off;
        sprintf(assem, "%d]", off);
        while(*assem != ']')assem++;
        *(assem + 1) = '\0';
    }

    if(num_spilled_temps != 0){
        string rsfp_ir = (string)checked_malloc(IR_MAXLEN);
        sprintf(rsfp_ir, "sub sp, sp, #%d", num_spilled_temps * ARCH_SIZE);
        AS_instr reserve_space_for_spilled = AS_Oper(rsfp_ir, NULL, NULL, NULL);
        in_last->tail = AS_InstrList(reserve_space_for_spilled, in_last->tail);
    }
    return head;
}

AS_instrList regalloc(AS_instrList il, G_nodeList ig_local)
{
    if (!il)
        return NULL;
    // TODO regalloc

    /* step 1: initialization */
    simplify = G_empty();
    color = TAB_empty();
    spill = TAB_empty();
    spill_off = ARCH_SIZE;
    ls_for_spill = NULL;
    used_callee_saved = NULL;

    /* step 2: simplify & spill */
    simplify_and_spill(ig_local);

    /* step 3: color */
    color_and_actual_spill(il);

    /* step 4: build the frame and save & load for callee-saved registers */
    il = build_frame(il);
    return il;
}