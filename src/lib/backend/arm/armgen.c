#include "armgen.h"

#define ARMGEN_DEBUG
#undef ARMGEN_DEBUG

#define ARCH_SIZE 4
// #define TYPELEN 10

#define CALLER_SAVED_REGS() (Temp_TempList( \
        Temp_namedtemp(0, T_int), \
        Temp_TempList( \
            Temp_namedtemp(1, T_int), \
            Temp_TempList( \
                Temp_namedtemp(2, T_int), \
                Temp_TempList( \
                    Temp_namedtemp(3, T_int), \
                    Temp_TempList( \
                        Temp_namedtemp(0, T_float), \
                        Temp_TempList( \
                            Temp_namedtemp(1, T_float), \
                            Temp_TempList( \
                                Temp_namedtemp(2, T_float), \
                                Temp_TempList( \
                                    Temp_namedtemp(3, T_float), \
                                    Temp_TempList( \
                                        Temp_namedtemp(4, T_float), \
                                        Temp_TempList( \
                                            Temp_namedtemp(5, T_float), \
                                            Temp_TempList( \
                                                Temp_namedtemp(6, T_float), \
                                                Temp_TempList( \
                                                    Temp_namedtemp(7, T_float), \
                                                    Temp_TempList( \
                                                        Temp_namedtemp(8, T_float), \
                                                        Temp_TempList( \
                                                            Temp_namedtemp(9, T_float), \
                                                            Temp_TempList( \
                                                                Temp_namedtemp(10, T_float), \
                                                                Temp_TempList( \
                                                                    Temp_namedtemp(11, T_float), \
                                                                    Temp_TempList( \
                                                                        Temp_namedtemp(12, T_float), \
                                                                        Temp_TempList( \
                                                                            Temp_namedtemp(13, T_float), \
                                                                            Temp_TempList( \
                                                                                Temp_namedtemp(14, T_float), \
                                                                                Temp_TempList( \
                                                                                    Temp_namedtemp(15, T_float), \
                                                                                    NULL \
                                                                                ) \
                                                                            ) \
                                                                        ) \
                                                                    ) \
                                                                ) \
                                                            ) \
                                                        ) \
                                                    ) \
                                                ) \
                                            ) \
                                        ) \
                                    ) \
                                ) \
                            ) \
                        ) \
                    ) \
                ) \
            ) \
        ) \
    )) 

static bool all_callee_saved;

static AS_instrList iList = NULL, last = NULL;
static void emit(AS_instr inst)
{
    if (last)
    {
        last = last->tail = AS_InstrList(inst, NULL);
    }
    else
    {
        last = iList = AS_InstrList(inst, NULL);
    }
}

typedef enum
{
    NONE,
    BR,
    RET,
    ADD,
    SUB,
    MUL,
    DIV,
    FADD,
    FSUB,
    FMUL,
    FDIV,
    F2I,
    I2F,
    I2P,
    P2I,
    LOAD,
    STORE,
    CALL,
    EXTCALL,
    ICMP,
    FCMP,
    LABEL,
    PHI
} AS_type;

AS_type gettype(AS_instr ins)
{
    AS_type ret = NONE;
    string assem = ins->u.OPER.assem;
    if (ins->kind == I_LABEL)
    {
        ret = LABEL;
        return ret;
    }
    if (ins->kind == I_MOVE)
    {
        assem = ins->u.MOVE.assem;
    }

    if (!strncmp(assem, "br", 2))
    {
        ret = BR;
        return ret;
    }
    else if (!strncmp(assem, "ret", 3))
    {
        ret = RET;
        return ret;
    }
    else if (!strncmp(assem, "%`d0 = fadd", 11))
    {
        ret = FADD;
        return ret;
    }
    else if (!strncmp(assem, "%`d0 = add", 10))
    {
        ret = ADD;
        return ret;
    }
    else if (!strncmp(assem, "%`d0 = fsub", 11))
    {
        ret = FSUB;
        return ret;
    }
    else if (!strncmp(assem, "%`d0 = sub", 10))
    {
        ret = SUB;
        return ret;
    }
    else if (!strncmp(assem, "%`d0 = fmul", 11))
    {
        ret = FMUL;
        return ret;
    }
    else if (!strncmp(assem, "%`d0 = mul", 10))
    {
        ret = MUL;
        return ret;
    }
    else if (!strncmp(assem, "%`d0 = fdiv", 11))
    {
        ret = FDIV;
        return ret;
    }
    else if (!strncmp(assem, "%`d0 = sdiv", 11))
    {
        ret = DIV;
        return ret;
    }
    else if (!strncmp(assem, "%`d0 = fptosi", 13))
    {
        ret = F2I;
        return ret;
    }
    else if (!strncmp(assem, "%`d0 = sitofp", 13))
    {
        ret = I2F;
        return ret;
    }
    else if (!strncmp(assem, "%`d0 = inttoptr", 15))
    {
        ret = I2P;
        return ret;
    }
    else if (!strncmp(assem, "%`d0 = load", 11))
    {
        ret = LOAD;
        return ret;
    }
    else if (!strncmp(assem, "store", 5))
    {
        ret = STORE;
        return ret;
    }
    else if (!strncmp(assem, "%`d0 = ptrtoint", 15))
    {
        ret = P2I;
        return ret;
    }
    else if (!strncmp(assem, "%`d0 = call", 11))
    {
        ret = CALL;
        return ret;
    }
    else if (!strncmp(assem, "call", 4))
    {
        ret = EXTCALL;
        return ret;
    }
    else if (!strncmp(assem, "%`d0 = icmp", 11))
    {
        ret = ICMP;
        return ret;
    }
    else if (!strncmp(assem, "%`d0 = fcmp", 11))
    {
        ret = FCMP;
        return ret;
    }
    else if (!strncmp(assem, "%`d0 = phi", 10))
    {
        ret = PHI;
        return ret;
    }
    return ret;
}

static AS_instrList armprolog(AS_instr prologi) {
    if(!prologi)return NULL;

    string prolog_assem = prologi->u.OPER.assem;
    ASSERT(prolog_assem);

    ASSERT(strncmp(prolog_assem, "define", strlen("define")) == 0);

    while(*prolog_assem && *prolog_assem != '@')prolog_assem++;
    prolog_assem++;

    string mtdname = (string)checked_malloc(IR_MAXLEN);
    int i = 0;
    while(*prolog_assem != '(')mtdname[i++] = *prolog_assem++;
    mtdname[i++] = '\0';

    string ins = (string)checked_malloc(IR_MAXLEN);

    sprintf(ins, ".text\n.align 1\n.global %s\n%s:", mtdname, mtdname);

    AS_instrList header = AS_InstrList(AS_Oper(ins, NULL, NULL, NULL), NULL);

    if(all_callee_saved){
    /* push fp to the stack */
        header = AS_splice(header, AS_InstrList(AS_Oper("push {fp, lr}", NULL, NULL, NULL), NULL));

    /* mov fp, sp */
        header = AS_splice(header, AS_InstrList(AS_Oper("mov fp, sp", NULL, NULL, NULL), NULL));

    /* callee-saved registers */
    /* we currently save all !!! */
    /* UPDATE: added after register allocation */
        header = AS_splice(header, AS_InstrList(AS_Oper("push {r4-r10}", NULL, NULL, NULL), NULL));
        header = AS_splice(header, AS_InstrList(AS_Oper("push {s16-s31}", NULL, NULL, NULL), NULL));
    }

    /* passing parameters (if any) */
    int cnt = 0;
    for(Temp_tempList args = prologi->u.OPER.src; args; args = args->tail, cnt++) {
        if(cnt < 4) {
            string ir = args->head->type == T_int ? "mov `d0, `s0" : "vmov.f32 `d0, `s0";
            header = AS_splice(header,
                AS_InstrList(
                    AS_Oper(
                        ir, 
                        Temp_TempList(args->head, NULL), 
                        // we need to reimplement the AS_print
                        // to print s_i for T_float and r_i for T_int
                        Temp_TempList(Temp_namedtemp(cnt, args->head->type), NULL)
                    , NULL)
                , NULL)
            );
        }
        else {
            // in this teaching version, has atmost 4 parameters
            ASSERT(0);
        }
    }

    return header;
}

static AS_instrList seek_last_two(AS_instrList instrs) {
    ASSERT(instrs->tail && instrs->tail->head);

    AS_instrList last_two = instrs;
    instrs = instrs->tail;
    while(instrs->tail && instrs->tail->head->kind != I_LABEL){
        last_two = last_two->tail;
        instrs = instrs->tail;
    }

    return last_two;
}

static void remove_phi_function(G_nodeList bg) {
    // remove the epilog of llvm_ins
    for(G_nodeList nodes = bg; nodes; nodes = nodes->tail) {
        if(nodes->tail) continue;
        // the last node, which links to epilog of llvm_ins
        G_node n = nodes->head;
        AS_block blk = G_nodeInfo(n);
        AS_instrList pre = blk->instrs;
        AS_instrList instrs = blk->instrs->tail;
        while(instrs->tail)instrs = instrs->tail, pre = pre->tail;
        pre->tail = NULL;
    }

    // the correctness must be guaranteed outside this function
    for(G_nodeList nodes = bg; nodes; nodes = nodes->tail) {
        G_node n = nodes->head;

        AS_block blk = G_nodeInfo(n);

        if(blk->instrs == NULL)continue;
        
        AS_instrList lst = blk->instrs;
        for(AS_instrList instrs = blk->instrs->tail; instrs; instrs = instrs->tail, lst = lst->tail) {
            AS_instr ins = instrs->head;
            AS_type tp = gettype(ins);
            if(tp == LABEL || tp == NONE)break;
            if(tp != PHI){
                // abandon all phi functions in this block
                blk->instrs->tail = instrs;
                break;
            }

            G_nodeList pred = G_pred(n);
            Temp_temp dst = ins->u.OPER.dst->head;
            Temp_tempList src = ins->u.OPER.src;


            for(; pred && src; pred = pred->tail, src = src->tail) {
                G_node p = pred->head;
                Temp_temp s = src->head;

                AS_block p_blk = G_nodeInfo(p);
                AS_instrList last_two = seek_last_two(p_blk->instrs);
                AS_instrList tail = last_two->tail;

                if(dst->type == T_int){
                    last_two->tail = AS_splice(
                        AS_InstrList(
                            AS_Move("%`d0 = add i64 %`s0, 0", Temp_TempList(dst, NULL), Temp_TempList(s, NULL)), 
                            NULL
                        ),
                        tail
                    );
                }
                else {
                    last_two->tail = AS_splice(
                        AS_InstrList(
                            AS_Move("%`d0 = fadd double %`s0, 0", Temp_TempList(dst, NULL), Temp_TempList(s, NULL)), 
                            NULL
                        ),
                        tail
                    );
                }
            }

            ASSERT(!pred && !src);
        }
    }
}

typedef enum {
    EQ,
    NEQ,
    GE,
    GT,
    LE,
    LT
} CND;

static CND last_cnd;

string strfind(string s, char c) {
    if(!s)return NULL;
    while(*s && *s != c)s++;
    if(*s == c)return s;
    return NULL;
}

typedef union {
    int i;
    float f;
    unsigned u;
}imme_pat;

static imme_pat pat;

#define IMM_INT(val) (pat.i = (val), load_immediate(T_int))
#define IMM_FLOAT(val) (pat.f = (val), load_immediate(T_float))

Temp_temp load_immediate(T_type type) {
    Temp_temp tmp = Temp_newtemp(T_int);
    char buf[20];
    sprintf(buf, "%.8x", pat.u);

    string mov_lower = (string)checked_malloc(IR_MAXLEN);
    sprintf(mov_lower, "mov `d0, #0x%.4s", buf + 4);
    emit(AS_Oper(mov_lower, Temp_TempList(tmp, NULL), NULL, NULL));

    string mov_upper = (string)checked_malloc(IR_MAXLEN);
    sprintf(mov_upper, "movt `d0, #0x%.4s", buf);
    emit(AS_Oper(mov_upper, Temp_TempList(tmp, NULL), NULL, NULL));

    if(type == T_int)return tmp;

    Temp_temp ret = Temp_newtemp(T_float);
    emit(AS_Move("vmov.f32 `d0, `s0", Temp_TempList(ret, NULL), Temp_TempList(tmp, NULL)));
    return ret;
}

/* Temp_temp get_imm8(T_type type) {
    // if immediate in `pat` has more than 8 bits
    // mov it to a new reg and return the new temp
    // else return null

    return load_immediate(type);    // UPDATE: always load bit pattern to ensure correctness

    if(!((~0xff) & pat.u))return NULL;    // only lower 8 bits are used

    Temp_temp tmp = Temp_newtemp(T_int);
    char buf[20];
    sprintf(buf, "%.8x", pat.u);

    string mov_lower = (string)checked_malloc(IR_MAXLEN);
    sprintf(mov_lower, "mov `d0, #0x%.4s", buf + 4);
    emit(AS_Oper(mov_lower, Temp_TempList(tmp, NULL), NULL, NULL));

    if((~0xffff) & pat.u) {
        // upper 16bits are also used
        string mov_upper = (string)checked_malloc(IR_MAXLEN);
        sprintf(mov_upper, "movt `d0, #0x%.4s", buf);
        emit(AS_Oper(mov_upper, Temp_TempList(tmp, NULL), NULL, NULL));
    }

    if(type == T_int)return tmp;

    Temp_temp ret = Temp_newtemp(T_float);
    emit(AS_Oper("vmov.f32 `d0, `s0", Temp_TempList(ret, NULL), Temp_TempList(tmp, NULL), NULL));
    return ret;
}

Temp_temp get_imm16(T_type type) {
    // if immediate in `pat` has more than 16 bits
    // mov it to a new reg and return the new temp
    // else return null

    return load_immediate(type);    // UPDATE: always load bit pattern to ensure correctness

    if(!((~0xffff) & pat.u))return NULL;    // only lower 16 bits are used

    Temp_temp tmp = Temp_newtemp(T_int);
    char buf[20];
    sprintf(buf, "%.8x", pat.u);

    string mov_lower = (string)checked_malloc(IR_MAXLEN);
    sprintf(mov_lower, "mov `d0, #0x%.4s", buf + 4);
    emit(AS_Oper(mov_lower, Temp_TempList(tmp, NULL), NULL, NULL));

    string mov_upper = (string)checked_malloc(IR_MAXLEN);
    sprintf(mov_upper, "movt `d0, #0x%.4s", buf);
    emit(AS_Oper(mov_upper, Temp_TempList(tmp, NULL), NULL, NULL));

    if(type == T_int)return tmp;

    Temp_temp ret = Temp_newtemp(T_float);
    emit(AS_Oper("vmov.f32 `d0, `s0", Temp_TempList(ret, NULL), Temp_TempList(tmp, NULL), NULL));
    return ret;
} */

typedef struct {
    T_type tp;
    bool isConst;
    union {
        Temp_temp t;
        int i;
        float f;
    } u;
}Arg_;
typedef Arg_* Arg;

Arg ArgIntConst(int i) {
    Arg p = (Arg)checked_malloc(sizeof(*p));
    p->isConst = TRUE;
    p->tp = T_int;
    p->u.i = i;
    return p;
}

Arg ArgFloatConst(float f) {
    Arg p = (Arg)checked_malloc(sizeof(*p));
    p->isConst = TRUE;
    p->tp = T_float;
    p->u.f = f;
    return p;
}

Arg ArgReg(Temp_temp t) {
    Arg p = (Arg)checked_malloc(sizeof(*p));
    p->isConst = FALSE;
    p->tp = t->type;
    p->u.t = t;
    return p;
}

typedef struct Arglist_* Arglist;
struct Arglist_{
    Arg head;
    Arglist tail;
};

Arglist ArgList(Arg head, Arglist tail) {
    Arglist p = (Arglist)checked_malloc(sizeof(*p));
    p->head = head;
    p->tail = tail;
    return p;
}

static Arglist extract_args(string assem, Temp_tempList regs) {
    if(!assem){
        Arglist ret = NULL, tail = NULL;
        while(regs) {
            if(ret)tail = tail->tail = ArgList(ArgReg(regs->head), NULL);
            else ret = tail = ArgList(ArgReg(regs->head), NULL);
            regs = regs->tail;
        }
        return ret;
    }
    // if `assem` is not null
    // we need to extract the possible constant args

    // [note] currently, `assem` will be null only for calling __aeabi_idiv
    // we assume there must be a `()` pair in the `assem`

    while(*assem && *assem != '(')assem++;
    assem++;

    int cnt = 0;
    Arglist ret = NULL, tail = NULL;

    while(TRUE){
        if(*assem == ')')break;
        if(*assem == ' ')cnt++;
        if(cnt == 1){
            // before an argument
            cnt = -1;   // reset fo find next
            Arg arg = NULL;
            if(*(assem + 1) == '%'){
                // a register argument
                arg = ArgReg(regs->head);
                regs = regs->tail;
            }
            else {
                // a const argument
                bool find_point = FALSE;
                for(int i = 0; assem[1 + i] != ',' && assem[1 + i] != ')'; i++){
                    if(assem[1 + i] == '.'){
                        find_point = TRUE;
                        break;
                    }
                }

                if(find_point)arg = ArgFloatConst(atof(assem + 1));
                else arg = ArgIntConst(atoi(assem + 1));
            }
            if(ret)tail = tail->tail = ArgList(arg, NULL);
            else ret = tail = ArgList(arg, NULL);
        }
        assem++;
    }

    return ret;
}

static Temp_tempList pass_params_to_call(Arglist args) {
    Temp_tempList ret = NULL;
    for(int cnt = 0; args; args = args->tail, cnt++) {
        if(cnt == 4)ASSERT(0);
        string ir = NULL;
        Temp_tempList src = NULL;
        if(args->head->isConst){
            ir = (string)checked_malloc(IR_MAXLEN);

            Temp_temp t = args->head->tp == T_int ? IMM_INT(args->head->u.i) : IMM_FLOAT(args->head->u.f);

            src = Temp_TempList(t, NULL);
            if(args->head->tp == T_int)sprintf(ir, "mov `d0, `s0");
            else sprintf(ir, "vmov.f32 `d0, `s0");
        }
        else {
            ir = args->head->tp == T_int ? "mov `d0, `s0" : "vmov.f32 `d0, `s0";
            src = Temp_TempList(args->head->u.t, NULL);
        }
        emit(AS_Move(
                ir, 
                Temp_TempList(Temp_namedtemp(cnt, args->head->tp), NULL),
                src));
        ret = Temp_TempListSplice(ret, Temp_TempList(Temp_namedtemp(cnt, args->head->tp), NULL));
    }
    return ret;
}

static void push_caller_save() {
    emit(AS_Oper("push {r1-r3}", NULL, NULL, NULL));
    emit(AS_Oper("push {s1-s15}", NULL, NULL, NULL));
}

static void pop_caller_save() {
    emit(AS_Oper("push {s1-s15}", NULL, NULL, NULL));
    emit(AS_Oper("push {r1-r3}", NULL, NULL, NULL));
}

static void get_return_value(Temp_temp dst) {
    if(!dst){
        // pop_caller_save();
        return;     // for void
    }
    if(dst->type == T_int)emit(AS_Oper("mov `d0, `s0", Temp_TempList(dst, NULL), Temp_TempList(Temp_namedtemp(0, T_int), NULL), NULL));
    else emit(AS_Oper("vmov.f32 `d0, `s0", Temp_TempList(dst, NULL), Temp_TempList(Temp_namedtemp(0, T_float), NULL), NULL));
    // pop_caller_save();
}

static void munchNamedCallImpl(string assem, Temp_temp dst, Temp_tempList regs, string mtdname) {
    Arglist args = extract_args(assem, regs);

    Temp_tempList parameters = pass_params_to_call(args);
    string ir = (string)checked_malloc(IR_MAXLEN);
    sprintf(ir, "bl %s", mtdname);
    emit(AS_Oper(ir, CALLER_SAVED_REGS(), parameters, NULL));
    get_return_value(dst);
}

static void munchCall(AS_instr llvm_ins) {
    // for both call and extcall
    string assem = llvm_ins->u.OPER.assem;

    if(llvm_ins->u.OPER.dst){
        while(*assem && *assem != '=')assem++;    // skip the possibly leading %`d0
    }

    while(*assem && *assem != '@' && *assem != '%')assem++;   // move to the method ptr
    if(!*assem){
        INFO("[call] %s\n", llvm_ins->u.OPER.assem);
        ASSERT(0);
    }
    bool isName = *assem == '@';

    Temp_temp dst = llvm_ins->u.OPER.dst ? llvm_ins->u.OPER.dst->head : NULL;

    // push_caller_save();
    
    if(isName){
        string mtdname = (string)checked_malloc(IR_MAXLEN);
        assem++;
        int i = 0;
        for(; *assem != '('; i++){
            mtdname[i] = *assem++;
        }
        mtdname[i] = '\0';
        munchNamedCallImpl(llvm_ins->u.OPER.assem, dst, llvm_ins->u.OPER.src, mtdname);
    }
    else {
        Arglist args = extract_args(llvm_ins->u.OPER.assem, llvm_ins->u.OPER.src->tail);
        Temp_tempList parameters = pass_params_to_call(args);
        emit(AS_Oper("blx `s0", CALLER_SAVED_REGS(), Temp_TempList(llvm_ins->u.OPER.src->head, parameters), NULL));
        get_return_value(dst);
    }
}

static void munchSDiv(AS_instr llvm_ins) {
    munchNamedCallImpl(NULL, llvm_ins->u.OPER.dst->head, llvm_ins->u.OPER.src, "__aeabi_idiv");
}

static void munchAdd_RegReg(Temp_temp dst, Temp_temp reg1, Temp_temp reg2) {
    string ir = dst->type == T_int ? "add `d0, `s0, `s1" : "vadd.f32 `d0, `s0, `s1";
    emit(AS_Oper(ir, Temp_TempList(dst, NULL), Temp_TempList(reg1, Temp_TempList(reg2, NULL)), NULL));
}

static void munchAdd_RegConst(Temp_temp dst, Temp_temp reg1, string const_start) {
    if(dst->type == T_int) {
        int val = atoi(const_start);
        Temp_temp t = IMM_INT(val);
        munchAdd_RegReg(dst, reg1, t);
    }
    else {
        float val = atof(const_start);
        Temp_temp t = IMM_FLOAT(val);
        munchAdd_RegReg(dst, reg1, t);
    }
}

static void munchAdd_ConstConst(Temp_temp dst, string const1_start, string const2_start) {
    Temp_temp v1 = NULL, v2 = NULL;
    if(dst->type == T_int) {
        int val1 = atoi(const1_start);
        int val2 = atoi(const2_start);
        v1 = IMM_INT(val1);
        v2 = IMM_INT(val2);
    }
    else {
        float val1 = atof(const1_start);
        float val2 = atof(const2_start);
        v1 = IMM_FLOAT(val1);
        v2 = IMM_FLOAT(val2);
    }
    munchAdd_RegReg(dst, v1, v2);
}

static void munchAdd(AS_instr llvm_ins) {
    Temp_tempList src = llvm_ins->u.OPER.src;
    T_type tp = llvm_ins->u.OPER.dst->head->type;
    string assem = llvm_ins->u.OPER.assem + strlen(llvm_ins->u.OPER.assem);
    string first_operand_start = NULL, second_operand_start = NULL;
    while(*assem != ' ')assem--;
    second_operand_start = (assem--) + 1;
    while(*assem != ' ')assem--;
    first_operand_start = assem + 1;

    if(!src) {
        // both operands are consts
        munchAdd_ConstConst(llvm_ins->u.OPER.dst->head, first_operand_start, second_operand_start);
    }
    else if(!src->tail) {
        // one operand is a const
        if(*first_operand_start == '%'){
            // second is a const
            munchAdd_RegConst(llvm_ins->u.OPER.dst->head, src->head, second_operand_start);
        }
        else {
            // first is a const
            munchAdd_RegConst(llvm_ins->u.OPER.dst->head, src->head, first_operand_start);
        }
    }
    else munchAdd_RegReg(llvm_ins->u.OPER.dst->head, src->head, src->tail->head);
}

static void munchSub_RegReg(Temp_temp dst, Temp_temp reg1, Temp_temp reg2) {
    string ir = dst->type == T_int ? "sub `d0, `s0, `s1" : "vsub.f32 `d0, `s0, `s1";
    emit(AS_Oper(ir, Temp_TempList(dst, NULL), Temp_TempList(reg1, Temp_TempList(reg2, NULL)), NULL));
}

static void munchSub_RegConst(Temp_temp dst, Temp_temp reg1, string const_start) {
    Temp_temp t;
    if(dst->type == T_int) {
        int val = atoi(const_start);
         t = IMM_INT(val);
    }
    else {
        float val = atof(const_start);
        t = IMM_FLOAT(val);
    }
    munchSub_RegReg(dst, reg1, t);
}

static void munchSub_ConstReg(Temp_temp dst, Temp_temp reg1, string const_start) {
    if(dst->type == T_int) {
        int val = atoi(const_start);
        Temp_temp t = IMM_INT(val);
        munchSub_RegReg(dst, t, reg1);
    }
    else {
        float val = atof(const_start);
        Temp_temp t = IMM_FLOAT(val);
        munchSub_RegReg(dst, t, reg1);
    }
}

static void munchSub_ConstConst(Temp_temp dst, string const1_start, string const2_start) {
    Temp_temp v1 = NULL, v2 = NULL;
    if(dst->type == T_int) {
        int val1 = atoi(const1_start);
        int val2 = atoi(const2_start);
        v1 = IMM_INT(val1);
        v2 = IMM_INT(val2);
    }
    else {
        float val1 = atof(const1_start);
        float val2 = atof(const2_start);
        v1 = IMM_FLOAT(val1);
        v2 = IMM_FLOAT(val2);
    }
    munchSub_RegReg(dst, v1, v2);
}

static void munchSub(AS_instr llvm_ins) {
    Temp_tempList src = llvm_ins->u.OPER.src;
    T_type tp = llvm_ins->u.OPER.dst->head->type;
    string assem = llvm_ins->u.OPER.assem + strlen(llvm_ins->u.OPER.assem);
    string first_operand_start = NULL, second_operand_start = NULL;
    while(*assem != ' ')assem--;
    second_operand_start = (assem--) + 1;
    while(*assem != ' ')assem--;
    first_operand_start = assem + 1;

    if(!src) {
        // both operands are consts
        munchSub_ConstConst(llvm_ins->u.OPER.dst->head, first_operand_start, second_operand_start);
    }
    else if(!src->tail) {
        // one operand is a const
        if(*first_operand_start == '%'){
            // second is a const
            munchSub_RegConst(llvm_ins->u.OPER.dst->head, src->head, second_operand_start);
        }
        else {
            // first is a const
            munchSub_ConstReg(llvm_ins->u.OPER.dst->head, src->head, first_operand_start);
        }
    }
    else munchSub_RegReg(llvm_ins->u.OPER.dst->head, src->head, src->tail->head);
}

static void munchMulFdiv_RegReg(Temp_temp dst, Temp_temp reg1, Temp_temp reg2, string op) {
    string ir = (string)checked_malloc(IR_MAXLEN);
    sprintf(ir, "%s `d0, `s0, `s1", op);
    emit(AS_Oper(ir, Temp_TempList(dst, NULL), Temp_TempList(reg1, Temp_TempList(reg2, NULL)), NULL));
}

static void munchMulFdiv_RegConst(Temp_temp dst, Temp_temp reg1, string const_start, string op) {
    T_type tp = dst->type;
    Temp_temp reg2 = NULL;
    if(tp == T_int) {
        int val = atoi(const_start);
        reg2 = IMM_INT(val);
    }
    else {
        float val = atof(const_start);
        reg2 = IMM_FLOAT(val);
    }
    assert(reg2);
    munchMulFdiv_RegReg(dst, reg1, reg2, op);    
}

static void munchMulFdiv_ConstReg(Temp_temp dst, Temp_temp reg2, string const_start, string op) {
    T_type tp = dst->type;
    Temp_temp reg1 = NULL;
    if(tp == T_int) {
        int val = atoi(const_start);
        reg1 = IMM_INT(val);
    }
    else {
        float val = atof(const_start);
        reg1 = IMM_FLOAT(val);
    }
    assert(reg1);
    munchMulFdiv_RegReg(dst, reg1, reg2, op);   
}

static void munchMulFdiv_ConstConst(Temp_temp dst, string const1_start, string const2_start, string op) {
    T_type tp = dst->type;
    Temp_temp v1 = NULL, v2 = NULL;
    if(tp == T_int) {
        int val1 = atoi(const1_start);
        int val2 = atoi(const2_start);
        v1 = IMM_INT(val1);
        v2 = IMM_INT(val2);
    }
    else {
        float val1 = atof(const1_start);
        float val2 = atof(const2_start);
        v1 = IMM_FLOAT(val1);
        v2 = IMM_FLOAT(val2);
    }
    munchMulFdiv_RegReg(dst, v1, v2, op);
}

static void munchMulFdiv(AS_instr llvm_ins) {
    Temp_tempList src = llvm_ins->u.OPER.src;
    T_type tp = llvm_ins->u.OPER.dst->head->type;
    string assem = llvm_ins->u.OPER.assem + strlen(llvm_ins->u.OPER.assem);
    string first_operand_start = NULL, second_operand_start = NULL;
    while(*assem != ' ')assem--;
    second_operand_start = (assem--) + 1;
    while(*assem != ' ')assem--;
    first_operand_start = assem + 1;

    string op = NULL;
    switch(gettype(llvm_ins)) {
        case FDIV: op = "vdiv.f32"; break;
        case MUL: op = "mul"; break;
        case FMUL: op = "vmul.f32"; break;
        default: assert(0);
    }

    if(!src) {
        // both operands are consts
        munchMulFdiv_ConstConst(llvm_ins->u.OPER.dst->head, first_operand_start, second_operand_start, op);
    }
    else if(!src->tail) {
        // one operand is a const
        if(*first_operand_start == '%'){
            // second is a const
            munchMulFdiv_RegConst(llvm_ins->u.OPER.dst->head, src->head, second_operand_start, op);
        }
        else {
            // first is a const
            munchMulFdiv_ConstReg(llvm_ins->u.OPER.dst->head, src->head, first_operand_start, op);
        }
    }
    else munchMulFdiv_RegReg(llvm_ins->u.OPER.dst->head, src->head, src->tail->head, op);
}

static void munchBinOp(AS_instr llvm_ins) {
    switch (gettype(llvm_ins)) {
        case ADD: 
        case FADD: munchAdd(llvm_ins); return;
        case MUL: 
        case FMUL: 
        case FDIV: munchMulFdiv(llvm_ins); return;
        case SUB: 
        case FSUB: munchSub(llvm_ins); return;
        case DIV: munchSDiv(llvm_ins); return;
        
        default: ASSERT(0);
    }
}

static void munchCMP(AS_instr llvm_ins) {
    Temp_tempList src = llvm_ins->u.OPER.src;
    T_type tp = llvm_ins->u.OPER.dst->head->type;
    
    string assem = llvm_ins->u.OPER.assem + strlen(llvm_ins->u.OPER.assem);
    string first_operand_start = NULL, second_operand_start = NULL;
    while(*assem != ' ')assem--;
    second_operand_start = (assem--) + 1;
    while(*assem != ' ')assem--;
    first_operand_start = assem + 1;

    AS_type ins_tp = gettype(llvm_ins);
    string op = NULL;
    if(ins_tp == ICMP)op = "cmp";
    else if(ins_tp == FCMP)op = "vcmp.f32";
    else ASSERT(0);

    string ir = (string)checked_malloc(IR_MAXLEN);
    if(!src) {
        // both operands are consts
        Temp_tempList emit_src = NULL;
        if(tp == T_int) {
            int val1 = atoi(first_operand_start);
            int val2 = atoi(second_operand_start);
            Temp_temp v1 = IMM_INT(val1);
            Temp_temp v2 = IMM_INT(val2);
            sprintf(ir, "%s `s0, `s1", op);
            emit_src = Temp_TempList(v1, Temp_TempList(v2, NULL));
        }
        else {
            float val1 = atof(first_operand_start);
            float val2 = atof(second_operand_start);
            Temp_temp v1 = IMM_FLOAT(val1);
            Temp_temp v2 = IMM_FLOAT(val2);
            sprintf(ir, "%s `s0, `s1", op);
            emit_src = Temp_TempList(v1, Temp_TempList(v2, NULL));
        }
        emit(AS_Oper(ir, llvm_ins->u.OPER.dst, emit_src, NULL));
    }
    else if(!src->tail) {
        // one operand is a const
        if(*first_operand_start == '%'){
            // second is a const
            Temp_tempList emit_src = NULL;
            if(tp == T_int) {
                int val = atoi(second_operand_start);
                Temp_temp t = IMM_INT(val);
                sprintf(ir, "%s `s0, `s1", op);
                emit_src = Temp_TempList(llvm_ins->u.OPER.src->head, Temp_TempList(t, NULL));
            }
            else {
                float val = atof(second_operand_start);
                Temp_temp t = IMM_FLOAT(val);
                sprintf(ir, "%s `s0, `s1", op);
                emit_src = Temp_TempList(llvm_ins->u.OPER.src->head, Temp_TempList(t, NULL));
            }
            emit(AS_Oper(ir, llvm_ins->u.OPER.dst, emit_src, NULL));
        }
        else {
            // first is a const
            Temp_tempList emit_src = NULL;
            if(tp == T_int) {
                int val = atoi(second_operand_start);
                Temp_temp t = IMM_INT(val);
                sprintf(ir, "%s `s0, `s1", op);
                emit_src = Temp_TempList(t, Temp_TempList(llvm_ins->u.OPER.src->head, NULL));
            }
            else {
                float val = atof(second_operand_start);
                Temp_temp t = IMM_FLOAT(val);
                sprintf(ir, "%s `s0, `s1", op);
                emit_src = Temp_TempList(t, Temp_TempList(llvm_ins->u.OPER.src->head, NULL));
            }
            emit(AS_Oper(ir, llvm_ins->u.OPER.dst, emit_src, NULL));
        }
    }
    else {
        // both operands are temps
        sprintf(ir, "%s `s0, `s1", op);
        emit(AS_Oper(ir, llvm_ins->u.OPER.dst, llvm_ins->u.OPER.src, NULL));
    }

    if(ins_tp == FCMP)emit(AS_Oper("vmrs APSR_nzcv, FPSCR", NULL, NULL, NULL));
}

static void munchBR(AS_instr llvm_ins, AS_instrList llvm_ins_node) {
    if(llvm_ins->u.OPER.src){
        // br cnd label1, label2
        // in our implementation
        // one of the two labels must be the next block
        Temp_labelList labels = llvm_ins->u.OPER.jumps->labels;
        ASSERT(labels && labels->tail);
        Temp_label t = labels->head, f = labels->tail->head;
        ASSERT(t && f);

        ASSERT(llvm_ins == llvm_ins_node->head);
        ASSERT(llvm_ins_node->tail);
        ASSERT(llvm_ins_node->tail->head);
        ASSERT(llvm_ins_node->tail->head->kind == I_LABEL);
        Temp_label next_label = llvm_ins_node->tail->head->u.LABEL.label;

        string assem = NULL;
        switch(last_cnd) {
            case EQ: assem = next_label == f ? "beq `j0" : "bne `j1"; break;
            case NEQ: assem = next_label == f ? "bne `j0" : "bne `j1"; break;
            case GE: assem = next_label == f ? "bge `j0" : "blt `j1"; break;
            case GT: assem = next_label == f ? "bgt `j0" : "ble `j1"; break;
            case LE: assem = next_label == f ? "ble `j0" : "bgt `j1"; break;
            case LT: assem = next_label == f ? "blt `j0" : "bge `j1"; break;
            default: ASSERT(0);
        }

        emit(AS_Oper(assem, NULL, NULL, llvm_ins->u.OPER.jumps));
    }
    else {
        // br label
        emit(AS_Oper("b `j0", NULL, NULL, llvm_ins->u.OPER.jumps));
    }
}

static void munchRET(AS_instr llvm_ins) {
    if(llvm_ins->u.OPER.src){
        // return value saved in a temp
        if(llvm_ins->u.OPER.src->head->type == T_int)
            emit(AS_Oper("mov `d0, `s0", Temp_TempList(Temp_namedtemp(0, T_int), NULL), Temp_TempList(llvm_ins->u.OPER.src->head, NULL), NULL));
        else emit(AS_Oper("vmov.f32 `d0, `s0", Temp_TempList(Temp_namedtemp(0, T_float), NULL), Temp_TempList(llvm_ins->u.OPER.src->head, NULL), NULL));
    }
    else {
        // return value is a printed const...
        string ir = (string)checked_malloc(IR_MAXLEN);

        string val_str = llvm_ins->u.OPER.assem + strlen(llvm_ins->u.OPER.assem);
        while(*val_str != ' ')val_str--;
        val_str++;

        if(strfind(llvm_ins->u.OPER.assem, '.')){
            float val = atof(val_str);
            Temp_temp t = IMM_FLOAT(val);
            sprintf(ir, "vmov.f32 `d0, `s0");
            emit(AS_Oper(ir, Temp_TempList(Temp_namedtemp(0, T_float), NULL), Temp_TempList(t, NULL), NULL));
        }
        else {
            int val = atoi(val_str);
            Temp_temp t = IMM_INT(val);
            sprintf(ir, "mov `d0, `s0");
            emit(AS_Oper(ir, Temp_TempList(Temp_namedtemp(0, T_int), NULL), Temp_TempList(t, NULL), NULL));
        }
        
    }

    // don't forget to go back to the caller frame
    if(all_callee_saved){
        string recover_sp = (string)checked_malloc(IR_MAXLEN);
        sprintf(recover_sp, "sub sp, fp, #%d", 24 * ARCH_SIZE);
        emit(AS_Oper(recover_sp, NULL, NULL, NULL));
        emit(AS_Oper("pop {s16-s31}", NULL, NULL, NULL));
        emit(AS_Oper("pop {r4-r10}", NULL, NULL, NULL));
        emit(AS_Oper("pop {fp, lr}", NULL, NULL, NULL));
    }
    emit(AS_Oper("bx lr", NULL, NULL, NULL));
}

static void munchF2I(AS_instr llvm_ins) {
    if(llvm_ins->u.OPER.src){
        // convert a value in a temp
        Temp_temp inter = Temp_newtemp(T_float);
        emit(AS_Move("vcvt.s32.f32 `d0, `s0", Temp_TempList(inter, NULL), llvm_ins->u.OPER.src));
        emit(AS_Move("vmov.f32 `d0, `s0", llvm_ins->u.OPER.dst, Temp_TempList(inter, NULL)));
    }
    else {
        // convert a const
        string ir = (string)checked_malloc(IR_MAXLEN);
        string const_start = llvm_ins->u.OPER.assem + strlen(llvm_ins->u.OPER.assem);
        while(*const_start != ' ')const_start--;
        const_start++;
        while(*const_start != ' ')const_start--;
        const_start++;
        while(*const_start != ' ')const_start--;
        const_start++;

        float val = atof(const_start);
        int v = val;
        Temp_temp t = IMM_INT(v);
        sprintf(ir, "mov `d0, `s0");
        emit(AS_Oper(ir, llvm_ins->u.OPER.dst, Temp_TempList(t, NULL), NULL));
    }
}

static void munchI2F(AS_instr llvm_ins) {
    if(llvm_ins->u.OPER.src){
        // convert a value in a temp
        Temp_temp inter1 = Temp_newtemp(T_float);
        Temp_temp inter2 = Temp_newtemp(T_float);
        emit(AS_Move("vmov.f32 `d0, `s0", Temp_TempList(inter2, NULL), llvm_ins->u.OPER.src));
        emit(AS_Move("vcvt.f32.s32 `d0, `s0", Temp_TempList(inter1, NULL), Temp_TempList(inter2, NULL)));
        emit(AS_Move("vmov.f32 `d0, `s0", llvm_ins->u.OPER.dst, Temp_TempList(inter1, NULL)));
    }
    else {
        // convert a const
        string ir = (string)checked_malloc(IR_MAXLEN);
        string const_start = llvm_ins->u.OPER.assem + strlen(llvm_ins->u.OPER.assem);
        while(*const_start != ' ')const_start--;
        const_start++;
        while(*const_start != ' ')const_start--;
        const_start++;
        while(*const_start != ' ')const_start--;
        const_start++;

        int val = atoi(const_start);
        float v = val;
        Temp_temp t = IMM_FLOAT(v);
        sprintf(ir, "vmov.f32 `d0, `s0");
        emit(AS_Oper(ir, llvm_ins->u.OPER.dst, Temp_TempList(t, NULL), NULL));
    }
}

static void llvm2arm(AS_instrList llvm_ins_node) {
    AS_instr llvm_ins = llvm_ins_node->head;

    if(llvm_ins->kind == I_MOVE){
        if(llvm_ins->u.MOVE.dst->head->type == T_int){
            emit(AS_Move("mov `d0, `s0", llvm_ins->u.MOVE.dst, llvm_ins->u.MOVE.src));
        }
        else emit(AS_Move("vmov.f32 `d0, `s0", llvm_ins->u.MOVE.dst, llvm_ins->u.MOVE.src));
        return;
    }

    switch(gettype(llvm_ins)) {
        case BR: munchBR(llvm_ins, llvm_ins_node); break;
        case RET: munchRET(llvm_ins); break;
        case ADD: 
        case SUB:
        case MUL:
        case DIV:
        case FADD:
        case FSUB:
        case FMUL:
        case FDIV: munchBinOp(llvm_ins); break;
        case F2I: munchF2I(llvm_ins); break;
        case I2F: munchI2F(llvm_ins); break;
        case I2P: emit(AS_Move("mov `d0, `s0", llvm_ins->u.OPER.dst, llvm_ins->u.OPER.src)); break;
        case P2I: {
            if(llvm_ins->u.OPER.src) {
                // the pointer is in a temp
                emit(AS_Move("mov `d0, `s0",llvm_ins->u.OPER.dst, llvm_ins->u.OPER.src));
            }
            else {
                // pointer is a label
                string assem = llvm_ins->u.OPER.assem;
                while(*assem && *assem != '@')assem++;
                assem++;
                string name = (string)checked_malloc(IR_MAXLEN);
                int i = 0;
                for(; *assem && *assem != ' '; i++){
                    name[i] = *assem++;
                }
                assem[i] = '\0';

                string ir = (string)checked_malloc(IR_MAXLEN);
                if(llvm_ins->u.OPER.dst->head->type == T_int)sprintf(ir, "ldr `d0, =%s", name);
                else sprintf(ir, "vldr.f32 `d0, =%s", name);
                emit(AS_Oper(ir, llvm_ins->u.OPER.dst, NULL, NULL));
            }
        } break;
        case LOAD: {
            if(llvm_ins->u.OPER.dst->head->type == T_int) {
                emit(AS_Oper("ldr `d0, [`s0]", llvm_ins->u.OPER.dst, llvm_ins->u.OPER.src, NULL));
            }
            else emit(AS_Oper("vldr.f32 `d0, [`s0]", llvm_ins->u.OPER.dst, llvm_ins->u.OPER.src, NULL));
        } break;
        case STORE: {
            if(llvm_ins->u.OPER.src->head->type == T_int) {
                emit(AS_Oper("str `s0, [`s1]", NULL, llvm_ins->u.OPER.src, NULL));
            }
            else emit(AS_Oper("vstr.f32 `s0, [`s1]", NULL, llvm_ins->u.OPER.src, NULL));
        } break;
        case CALL:
        case EXTCALL: munchCall(llvm_ins); break;
        case ICMP: {
            munchCMP(llvm_ins);
            string assem = llvm_ins->u.OPER.assem + strlen("%`d0 = icmp ");
            char cnd[4] = {0};
            int i = 0;
            for(; *assem != ' '; i++){
                if(i >= 3)ASSERT(0);
                cnd[i] = *assem++;
            }

            if(!strcmp(cnd, "eq")) {
                last_cnd = EQ;
            }
            else if(!strcmp(cnd, "ne")) {
                last_cnd = NEQ;
            }
            else if(!strcmp(cnd, "sgt")) {
                last_cnd = GT;
            }
            else if(!strcmp(cnd, "sge")) {
                last_cnd = GE;
            }
            else if(!strcmp(cnd, "slt")) {
                last_cnd = LT;
            }
            else if(!strcmp(cnd, "sle")) {
                last_cnd = LE;
            }
            else {
                INFO("assem: %s, cnd: %s\n",llvm_ins->u.OPER.assem, cnd);
                ASSERT(0);
            }
        } break;
        case FCMP: {
            munchCMP(llvm_ins);

            string assem = llvm_ins->u.OPER.assem + strlen("%`d0 = fcmp ");
            char cnd[4] = {0};
            int i = 0;
            for(; *assem != ' '; i++){
                if(i >= 3)ASSERT(0);
                cnd[i] = *assem++;
            }

            if(!strcmp(cnd, "oeq")) {
                last_cnd = EQ;
            }
            else if(!strcmp(cnd, "one")) {
                last_cnd = NEQ;
            }
            else if(!strcmp(cnd, "ogt")) {
                last_cnd = GT;
            }
            else if(!strcmp(cnd, "oge")) {
                last_cnd = GE;
            }
            else if(!strcmp(cnd, "olt")) {
                last_cnd = LT;
            }
            else if(!strcmp(cnd, "ole")) {
                last_cnd = LE;
            }
            else ASSERT(0);
        } break;
        case LABEL:
        case NONE:
        case PHI:
        default: {
            INFO("llvm_ins: %s, type %d, kind: %d\n", llvm_ins->u.OPER.assem, gettype(llvm_ins), llvm_ins->kind);
            ASSERT(0);
        }
    }
}

static AS_instrList gen_arm_instrs(AS_instrList bodyil_without_phi) {
    iList = last = NULL;

    for(AS_instrList bd = bodyil_without_phi; bd; bd = bd->tail) {
        AS_instr llvm_ins = bd->head;
        if(llvm_ins->kind == I_LABEL)emit(llvm_ins);
        else llvm2arm(bd);
    }

    return iList;
}

AS_instrList AS_instrList_to_arm(AS_instr prologi, G_nodeList bg, bool save_all_callee){
    all_callee_saved = save_all_callee;
    AS_instrList armpro = armprolog(prologi);
    INFO("prolog\n");
    AS_instrList armbody = NULL;
    AS_instrList armepi = AS_InstrList(AS_Oper("", NULL, NULL, NULL), NULL);

    /* step 1: remove phi functions */
    remove_phi_function(bg);
    INFO("Removed phi\n");

    /* step 2: tiling for arm */
    AS_instrList bodyil_without_phi = ((AS_block)G_nodeInfo(bg->head))->instrs;
    armbody = gen_arm_instrs(bodyil_without_phi);
    INFO("Arm_body got\n");

    /* step 3: [hw13] register allocation */

    if(armbody)return AS_splice(armpro, AS_splice(armbody, armepi));
    return AS_splice(armpro, armepi);
}