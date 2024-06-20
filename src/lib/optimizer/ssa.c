#include "assem.h"
#include "graph.h"
#include "ssa.h"

#define __DEBUG
#undef __DEBUG


static G_node get_start_node_init_tables(G_nodeList bg, G_table dominators) {
  G_node s0 = NULL;
  G_nodeList all_nodes = bg;
  while(bg){
    if(!G_inDegree(bg->head)){
      if(s0){
        fprintf(stderr, "More than one start node\n");
      }
      else s0 = bg->head;
      G_enter(dominators, s0, G_NodeList(s0, NULL));
    }
    else G_enter(dominators, bg->head, all_nodes);
    bg = bg->tail;
  }
  if(!s0){
    fprintf(stderr, "Start node not found!\n");
    exit(-1);
  }
  return s0;
}

static G_nodeList G_nodeList_intersect(G_nodeList a, G_nodeList b) {
  /* return a & b, allocate new memory if both are not null*/
  if(!a)return b;
  if(!b)return a;
  G_nodeList ret = NULL, iter = NULL;
  while(a) {
    if(G_inNodeList(a->head, b)){
      if(!ret)iter = ret = G_NodeList(a->head, NULL);
      else iter = iter->tail = G_NodeList(a->head, NULL);
    }
    a = a->tail;
  }
  return ret;
}

static G_nodeList G_nodeList_union(G_nodeList a, G_nodeList b) {
  /* return a | b */
  for(; a; a = a->tail) {
    if(!G_inNodeList(a->head, b)) b = G_NodeList(a->head, b);
  }
  return b;
}

static bool G_nodeList_same(G_nodeList a, G_nodeList b) {
  /* return true if a contains the same nodes as b */
  /* works fast when the sequence of nodes are also the same */
  G_nodeList cp_a = a, cp_b = b;

  while(TRUE){
    if(a == NULL && b == NULL)break;
    if(a == NULL && b != NULL || a != NULL && b == NULL)return FALSE;
    if(a->head == b->head || G_inNodeList(a->head, cp_b) && G_inNodeList(b->head, cp_a)){
      a = a->tail;
      b = b->tail;
      continue;
    }
    else return FALSE;
  }

  return TRUE;
}

static void compute_dominators(G_table dominators) {
  bool changed = TRUE;
  while(changed) {
    changed = FALSE;  // assume not to be change
    _for_in_table(iter, dominators) {
      G_node n = iter->key;
      G_nodeList d = iter->value;
      G_nodeList pred = G_pred(n);
      if(!pred)continue; // no predecessors, pass
      G_nodeList nd = G_NodeList(n, NULL);
      G_nodeList intersect = G_look(dominators, pred->head);  // get the D[p] of first predecessor
      pred = pred->tail;  // move to second predecessor
      while(pred) { // compute the intersection part of the formula
        intersect = G_nodeList_intersect(intersect, G_look(dominators, pred->head));
        pred = pred->tail;
      }
      nd = G_nodeList_union(nd, intersect); // compute the union part of the formula
      if(!G_nodeList_same(iter->value, nd)){  // check if the result changed
        iter->value = nd;
        changed = TRUE;
      }
    }
  }
}

static void show_dominators(FILE* out, G_table dominators) {
  _for_in_table(iter, dominators) {
    G_node n = iter->key;
    G_nodeList d = iter->value;
    fprintf(out, "(%d):", n->mykey);
    while(d){
      fprintf(out, " %d", d->head->mykey);
      d = d->tail;
    }
    fprintf(out, "\n");
  }
}

static void show_immediate_dominators(FILE* out, G_table idom) {
  _for_in_table(iter, idom) {
    G_node n = iter->key;
    G_node d = iter->value;
    fprintf(out, "(%d): %d\n", n->mykey, d->mykey);
  }
}

static void show_dominance_frontier(FILE* out, G_table df) {
  _for_in_table(iter, df) {
    G_node n = iter->key;
    G_nodeList d = iter->value;
    fprintf(out, "(%d):", n->mykey);
    while(d){
      fprintf(out, " %d", d->head->mykey);
      d = d->tail;
    }
    fprintf(out, "\n");
  }
}

static G_table retrive_immediate_dominator(G_table dominators) {
  G_table idom = G_empty();
  _for_in_table(iter, dominators) {
    G_node n = iter->key;
    /* find the immediate dominator of n */
    for(G_nodeList d = iter->value; d; d = d->tail) {
      if(d->head == n)continue;
      /* check if d->head is the immediate dominator of n */
      bool isImm = TRUE;
      for(G_nodeList other = iter->value; other; other = other->tail) {
        if(other->head == n || other->head == d->head)continue;
        if(G_inNodeList(d->head, G_look(dominators, other->head))){
          isImm = FALSE;
          break;
        }
      }
      if(isImm){
        G_enter(idom, n, d->head);
        break;
      }
    }
  }
  return idom;
}

static void compute_dominance_frontier_impl(G_node n, G_table df, G_table dominators, G_table idom) {
  G_nodeList local = NULL;
  /* compute local */
  for(G_nodeList succ = G_succ(n); succ; succ = succ->tail) {
    G_node idom_of_succ = G_look(idom, succ->head);
    if(idom_of_succ != n) local = G_NodeList(succ->head, local);
  }

  /* recursively compute children[n] */
  _for_in_table(iter, idom) {
    G_node child = iter->key;
    G_node idom_of_child = iter->value;
    if(idom_of_child != n) continue; // not the child of n
    compute_dominance_frontier_impl(child, df, dominators, idom);

    /* add nodes in dominance frontier of child that not strictly dominated by n */
    for(G_nodeList df_of_child = G_look(df, child); df_of_child; df_of_child = df_of_child->tail) {
      if(G_inNodeList(n, G_look(dominators, df_of_child->head)) && df_of_child->head != n)continue;
      local = G_NodeList(df_of_child->head, local);
    }
  }

  G_enter(df, n, local);
}

static G_table compute_dominance_frontier(G_node s0, G_table dominators, G_table idom) {
  G_table df = G_empty();
  compute_dominance_frontier_impl(s0, df, dominators, idom);
  return df;
}


/* These are for temp defsites */
typedef struct TAB_table_  *Temp_defsites;

static Temp_defsites Temp_defsites_empty() {
  return TAB_empty();
}

static G_nodeList Temp_defsites_look(Temp_defsites t, Temp_temp temp) {
  return TAB_look(t, temp);
}

/* remove the first node of defsites of temp */
static G_node Temp_defsites_remove(Temp_defsites t, Temp_temp temp) {
  binder temp_sites = TAB_getBinder(t, temp);
  if(!temp_sites)return NULL;
  G_nodeList sites = temp_sites->value;
  if(!sites)return NULL;
  G_node ret = sites->head;
  temp_sites->value = sites->tail;
  return ret;
}

static void Temp_defsites_append(Temp_defsites t, Temp_temp temp, G_node site) {
  if(!site)return;
  binder temp_sites = TAB_getBinder(t, temp);
  if(!temp_sites){
    TAB_enter(t, temp, NULL);
    temp_sites = TAB_getBinder(t, temp);
  }
  ASSERT(temp_sites);
  if(!G_inNodeList(site, temp_sites->value))
    temp_sites->value = G_NodeList(site, temp_sites->value);
}

static bool strfind(string s, string pattern) {
  for(int i = 0; i < strlen(s) - strlen(pattern); ++i) {
    bool find = TRUE;
    for(int j = 0; j < strlen(pattern); ++j) {
      if(s[i + j] != pattern[j]){
        find = FALSE;
        break;
      }
    }
    if(find)return TRUE;
  }
  return FALSE;
}

static bool isInt2ptr(AS_instr ins) {
  if(ins->kind == I_LABEL || ins->kind == I_MOVE)return FALSE;
  string assem = ins->u.OPER.assem;
  if(!assem)return FALSE;

  // find '='
  while(*assem && *assem != '=')assem++;
  if(!*assem)return FALSE;

  return strfind(assem, "inttoptr");
}

static bool isCmp(AS_instr ins) {
  if(ins->kind == I_LABEL || ins->kind == I_MOVE)return FALSE;
  string assem = ins->u.OPER.assem;
  if(!assem)return FALSE;

  // find '='
  while(*assem && *assem != '=')assem++;
  if(!*assem)return FALSE;

  int len = strlen(assem);
  if(len < 6)return FALSE;
  if(assem[3] == 'c' && assem[4] == 'm' && assem[5] == 'p')return TRUE;
  return FALSE;
}

static G_nodeList lg_find_spot(G_nodeList lg, AS_instr ins) {
  for(; lg; lg = lg->tail) {
    AS_instr i = G_nodeInfo(lg->head);
    if(i == ins)return lg;
  }
  return NULL;
}

static Temp_defsites insert_phi_functions(G_nodeList lg, G_nodeList bg, G_table df) {
  /* 
   * initializations:
   * 1. set all A_phi[n] and A_orig[n] to empty
   * 2. find all defsites of all temps as well as initializing A_orig[n], and all live-out
   * 
   */
  Temp_defsites defsites = Temp_defsites_empty();
  G_table A_orig = G_empty();
  G_table A_phi = G_empty();
  G_table live_in = G_empty();
  G_table live_out = G_empty();

  for(G_nodeList i = bg; i; i = i->tail) {
    // init.1
    G_node n = i->head;
    G_enter(A_orig, n, NULL);
    G_enter(A_phi, n, NULL);

    // init.2
    AS_block block = G_nodeInfo(n);
    if(block->instrs == NULL || block->instrs->head == NULL || block->instrs->head->kind != I_LABEL){
      fprintf(stderr, "wrong basic block\n");
      exit(-1);
    }

    G_nodeList label_node = lg_find_spot(lg, block->instrs->head);  // label
    G_enter(live_in, n, FG_In(label_node->head));
    G_nodeList fgnodes = label_node->tail;
    for(AS_instrList instrs = block->instrs->tail; instrs; instrs = instrs->tail, fgnodes = fgnodes->tail) {
      if(instrs->head->kind == I_LABEL){
        fprintf(stderr, "wrong basic block\n");
        exit(-1);
      }
      // add temps to A_orig[n]
      binder orig = TAB_getBinder(A_orig, n);
      orig->value = Temp_TempListUnion(orig->value, FG_def(fgnodes->head));

      // add n to defsite[defs]
      for(Temp_tempList defs = FG_def(fgnodes->head); defs; defs = defs->tail) {
        Temp_defsites_append(defsites, defs->head, n);
      }

      // if it's the last, record the live-out
      if(instrs->tail == NULL)G_enter(live_out, n, FG_Out(fgnodes->head));
    }
  }

  /*
   * inserting phi functions
   *
   */
  _for_in_table(var_defsites, defsites) {
    // for each varible a
    Temp_temp a = var_defsites->key;
    G_node n = NULL;

    // while W not empty
    while(n = Temp_defsites_remove(defsites, a)) {
      // avoid temps that will only be used within 'n'
      Temp_tempList lvout = G_look(live_out, n);
      if(!Temp_TempInTempList(a, lvout))continue;

      for(G_nodeList frontiers = G_look(df, n); frontiers; frontiers = frontiers->tail) {
        // for each Y in DF[n]
        G_node y = frontiers->head;
        binder bind_a_phy_y = TAB_getBinder(A_phi, y);
        Temp_tempList a_phi_y = bind_a_phy_y->value;
        if(Temp_TempInTempList(a, a_phi_y))continue;
        if(!Temp_TempInTempList(a, G_look(live_in, y)))continue;

        // if a not in A_phi[Y] and a in live-in of Y , need to insert phi function

        AS_block block = G_nodeInfo(y);
        string assem = checked_malloc(IR_MAXLEN);
        if(a->type == T_float)sprintf(assem, "%%`d0 = phi double ");
        else sprintf(assem, "%%`d0 = phi i64 ");
        int cnt = 0;
        Temp_tempList dst = Temp_TempList(a, NULL);
        Temp_tempList src = NULL, src_tail = NULL;
        Temp_labelList jumps = NULL, jumps_tail = NULL;
        for(G_nodeList pred = G_pred(y); pred; pred = pred->tail, cnt++) {
          sprintf(assem + strlen(assem), "[%%`s%d, %%`j%d], ", cnt, cnt);
          AS_block pre = G_nodeInfo(pred->head);
          if(!src){
            src = src_tail = Temp_TempList(a, NULL);
            jumps = jumps_tail = Temp_LabelList(pre->label, NULL);
          }
          else {
            src_tail = src_tail->tail = Temp_TempList(a, NULL);
            jumps_tail = jumps_tail->tail = Temp_LabelList(pre->label, NULL);
          }
        }
        assem[strlen(assem) - 2] = '\0';
        block->instrs =  AS_splice(
          AS_InstrList(block->instrs->head, NULL), 
          AS_InstrList(
            AS_Oper(assem, dst, src, AS_Targets(jumps))
            , block->instrs->tail
          )
        ); // end inserting

        // maintain the sets
        bind_a_phy_y->value = Temp_TempListUnion(bind_a_phy_y->value, Temp_TempList(a, NULL));
        if(!Temp_TempInTempList(a, G_look(A_orig, y)))Temp_defsites_append(defsites, a, y);
      }
    }
  }

  return defsites;
}

typedef struct TAB_table_  *Temp_stack;

static Temp_stack Temp_stack_empty() {
  return (Temp_stack)TAB_empty();
}

static Temp_temp Temp_stack_look(Temp_stack stack, Temp_temp temp) {
  return (Temp_temp)TAB_look(stack, temp);
}

static void Temp_stack_enter(Temp_stack stack, Temp_temp temp, Temp_temp latest) {
  TAB_enter(stack, temp, latest);
}

static void Temp_stack_beginScope(Temp_stack stack) {
  Temp_stack_enter(stack, Temp_namedtemp(-1, T_int), NULL);
}

static void Temp_stack_endScope(Temp_stack stack) {
  Temp_temp t;
  do t = TAB_pop(stack);
  while (t->num != -1);
}

static bool isPhi(AS_instr ins) {
  if(ins->kind == I_LABEL)return FALSE;
  if(ins->kind != I_OPER)return FALSE;
  if(!(ins->u.OPER.dst && ins->u.OPER.src && ins->u.OPER.jumps))return FALSE;
  if(!ins->u.OPER.jumps->labels)return FALSE;
  return TRUE;
}

int next_new_num;

static void rename_temps_impl(G_node n, S_table stack, G_nodeList bg, G_table idom) {
  Temp_stack_beginScope(stack);

  for(AS_instrList instrs = ((AS_block)G_nodeInfo(n))->instrs; instrs; instrs = instrs->tail) {
    AS_instr ins = instrs->head;
    if(ins->kind == I_LABEL)continue;
    if(!isPhi(ins)){
      // not a phi
      Temp_tempList uses = ins->kind == I_OPER ? ins->u.OPER.src : ins->u.MOVE.src;
      while(uses) {
        Temp_temp t = uses->head;
        Temp_temp replace = Temp_stack_look(stack, t);
        if(replace)uses->head = replace;
        uses = uses->tail;
      }
    }

    Temp_tempList defs = ins->kind == I_OPER ? ins->u.OPER.dst : ins->u.MOVE.dst;
    while(defs) {
      Temp_temp t = defs->head;
      Temp_temp redef = Temp_namedtemp(next_new_num++, t->type);
      Temp_stack_enter(stack, t, redef);
      defs->head = redef;
      defs = defs->tail;
    }
  }

  for(G_nodeList succ = G_succ(n); succ; succ = succ->tail) {
    G_node y = succ->head;
    G_nodeList pred_y = G_pred(y);
    int pos = 0;
    while(pred_y->head != n)pos++, pred_y = pred_y->tail;
    for(AS_instrList instrs = ((AS_block)G_nodeInfo(y))->instrs; instrs; instrs = instrs->tail) {
      AS_instr ins = instrs->head;
      if(ins->kind == I_LABEL)continue;
      if(!isPhi(ins))break;

      // find the temp indexed at pos and replace
      Temp_tempList phi_para = ins->u.OPER.src;
      for(int i = 0; i < pos; ++i)phi_para = phi_para->tail;
      Temp_temp replace = Temp_stack_look(stack, phi_para->head);
      if(replace)phi_para->head = replace;
    }
  }

  _for_in_table(iter, idom) {
    G_node c = iter->key;
    G_node p = iter->value;
    if(p == n)rename_temps_impl(c, stack, bg, idom);
  }

  Temp_stack_endScope(stack);
}

static void rename_temps(G_node s0, G_nodeList bg, Temp_defsites defsites, G_table idom) {
  /*
   * initialize and call implementation
   */
  Temp_stack stack = Temp_stack_empty();
  int max_num = 0;
  _for_in_table(iter, defsites) {
    Temp_temp var = iter->key;
    Temp_stack_enter(stack, var, var);
    if(max_num < var->num)max_num = var->num;
  }
  next_new_num = max_num + 1;
  rename_temps_impl(s0, stack, bg, idom);
}

AS_instrList AS_instrList_to_SSA(AS_instrList bodyil, G_nodeList lg, G_nodeList bg){
  /* step 0: initialization */
  G_table dominators = G_empty();
  G_node s0 = get_start_node_init_tables(bg, dominators);
  if(!s0)return NULL;
  INFO("initialized\n");

  /* step 1: construct the dominator tree, store info into table: idom */
  compute_dominators(dominators);
  INFO("dominators computed\n");
  // show_dominators(stderr, dominators);
  G_table idom = retrive_immediate_dominator(dominators);
  INFO("immediate dominators retrived\n");
  // show_immediate_dominators(stderr, idom);

  /* step 2: compute the dominance frontier, store info into table: df */
  G_table df = compute_dominance_frontier(s0, dominators, idom);
  INFO("dominance frontier computed\n");
  // show_dominance_frontier(stderr, df);

  /* step 3: insert the phi function */
  Temp_defsites defsites = insert_phi_functions(lg, bg, df);
  INFO("inserted phi functions\n");

  /* step 4: rename temps */
  rename_temps(s0, bg, defsites, idom);
  INFO("renamed temps\n");

  /* step 5: reconstruct body instruction list from bg */
  AS_instrList ret = NULL;
  for(G_nodeList bgnode = bg; bgnode; bgnode = bgnode->tail) {
    AS_block block = G_nodeInfo(bgnode->head);
    ret = AS_splice(ret, block->instrs);
  }
  INFO("reconstructed\n");
  return ret;
}

