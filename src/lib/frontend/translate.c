#include <stdlib.h>
#include <stdarg.h>
#include "translate.h"

extern int SEM_ARCH_SIZE;

/* patchList */

typedef struct patchList_ *patchList;
struct patchList_ {
  Temp_label *head;
  patchList tail;
};

static patchList PatchList(Temp_label *head, patchList tail) {
  patchList p = checked_malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

void doPatch(patchList pl, Temp_label tl) {
  for (; pl; pl = pl->tail)
    *(pl->head) = tl;
}

patchList joinPatch(patchList first, patchList second) {
  if (!first) return second;
  if (!second) return first;
  patchList tmp = first;
  while (tmp->tail) tmp = tmp->tail;
  tmp->tail = second;
  return first;
}

/* Tr_exp */

typedef struct Cx_ *Cx;

struct Cx_ {
  patchList trues;
  patchList falses;
  T_stm stm;
};

struct Tr_exp_ {
  enum  {Tr_ex, Tr_nx, Tr_cx} kind;
  union {
    T_exp ex;
    T_stm nx;
    Cx cx;
  } u;
};

static Tr_exp Tr_Ex(T_exp ex) {
  Tr_exp exp = checked_malloc(sizeof(*exp));
  exp->kind = Tr_ex;
  exp->u.ex = ex;
  return exp;
}

static Tr_exp Tr_Nx(T_stm nx) {
  Tr_exp exp = checked_malloc(sizeof(*exp));
  exp->kind = Tr_nx;
  exp->u.nx = nx;
  return exp;
}

static Tr_exp Tr_Cx(patchList trues, patchList falses, T_stm stm) {
  Tr_exp exp = checked_malloc(sizeof(*exp));
  exp->kind = Tr_cx;
  exp->u.cx = checked_malloc(sizeof(*(exp->u.cx)));
  exp->u.cx->trues = trues;
  exp->u.cx->falses = falses;
  exp->u.cx->stm = stm;
  return exp;
}

static T_exp unEx(Tr_exp exp) {
  if (!exp) return NULL;
  switch (exp->kind) {
  case Tr_ex:
    return exp->u.ex;
  case Tr_cx: {
    Temp_temp r = Temp_newtemp(T_int);
    Temp_label t = Temp_newlabel();
    Temp_label f = Temp_newlabel();
    Temp_label e = Temp_newlabel();
    doPatch(exp->u.cx->trues, t);
    doPatch(exp->u.cx->falses, f);
    return
    T_Eseq(
    T_Seq(exp->u.cx->stm,
    T_Seq(T_Label(t),
    T_Seq(T_Move(T_Temp(r), T_IntConst(1)),
    T_Seq(T_Jump(e),
    T_Seq(T_Label(f),
    T_Seq(T_Move(T_Temp(r), T_IntConst(0)), 
    T_Label(e))))))),
    T_Temp(r));
  }
  case Tr_nx:
    return T_Eseq(exp->u.nx, T_IntConst(0));
  default:
    ASSERT(0);
  }
}

static T_stm unNx(Tr_exp exp) {
  if (!exp) return NULL;
  switch (exp->kind) {
  case Tr_ex:
    return T_Exp(exp->u.ex);
  case Tr_cx: 
    return exp->u.cx->stm;
  case Tr_nx:
    return exp->u.nx;
  default:
    ASSERT(0);
  }
}

static Cx unCx(Tr_exp exp) {
  if (!exp) return NULL;
  switch (exp->kind) {
  case Tr_ex: {
    T_stm stm = T_Cjump(T_ne, unEx(exp), T_IntConst(0), NULL, NULL);
    patchList trues = PatchList(&stm->u.CJUMP.t, NULL);
    patchList falses = PatchList(&stm->u.CJUMP.f, NULL);
    Tr_exp cx = Tr_Cx(trues, falses, stm);
    return cx->u.cx;
  }
  case Tr_cx:
    return exp->u.cx;
  default:
    ASSERT(0);
  }
}

/* sequence */
void SeqBufInit() {
  if(seqbuf)return;
  seqbuf = checked_malloc(sizeof(*seqbuf));
  seqbuf->top = -1;
  seqbuf->size = INIT_BUF_SZ;
  seqbuf->seqs = checked_malloc(sizeof(T_stm) * INIT_BUF_SZ);
}

void seqBufPush(Tr_exp exp) {
  if(seqbuf == NULL)SeqBufInit();
  if(seqbuf->top == seqbuf->size - 1){
    T_stm *tmp = checked_malloc(sizeof(T_stm) * seqbuf->size * 2);
    for(int i = 0; i <= seqbuf->top; ++i){
      tmp[i] = seqbuf->seqs[i];
    }
    free(seqbuf->seqs);
    seqbuf->seqs = tmp;
  }
  seqbuf->seqs[++seqbuf->top] = unNx(exp);
}

int seqBufSize(){
  if(seqbuf == NULL)SeqBufInit();
  return seqbuf->top + 1;
}

void seqBufClear(){
  if(seqbuf == NULL)SeqBufInit();
  seqbuf->top = -1;
}

// concat at least two T_stm with T_Seq
Tr_exp SequenceImpl(T_stm first, ...){
  T_stm iter = NULL;
  va_list args;
  va_start(args, first);
  ASSERT(seqBufSize() == 0);
  seqBufPush(Tr_Nx(first));

  while((iter = va_arg(args, T_stm)) != NULL){
    seqBufPush(Tr_Nx(iter));
  }

  Tr_exp ret = SequenceFromBufferImpl(0);
  seqBufClear();
  return ret;
}

Tr_exp SequenceFromBufferImpl(int i){
  int remain = seqBufSize() - i;
  if(remain <= 0)return NULL;
  if(remain == 1){
    return Tr_Nx(seqbuf->seqs[i]);
  }
  else if(remain == 2){
    return Tr_Nx(T_Seq(seqbuf->seqs[i], seqbuf->seqs[i+1]));
  }
  return Tr_Nx(T_Seq(seqbuf->seqs[i], unNx(SequenceFromBufferImpl(i + 1))));
}

/* TODO: translate */

// methods
T_funcDeclList Tr_FuncDeclList(T_funcDecl fd, T_funcDeclList fdl){
  return T_FuncDeclList(fd, fdl);
}

T_funcDecl Tr_MainMethod(Tr_exp vdl, Tr_exp sl){
  T_funcDecl p = checked_malloc(sizeof(*p));
  p->name = String("main");
  p->args = NULL;
  if(vdl && sl)p->stm = T_Seq(unNx(vdl), unNx(sl));
  else if(vdl)p->stm = unNx(vdl);
  else p->stm = unNx(sl);
  return p;
}

T_funcDecl Tr_ClassMethod(string name, Temp_tempList paras, Tr_exp vdl, Tr_exp sl){
  T_stm stms = unNx(vdl);
  if(!stms)stms = unNx(sl);
  else if(sl)stms = unNx(Sequence(stms, unNx(sl)));
  return T_FuncDecl(name, paras, stms);
}

// stms
Tr_exp Tr_StmList(Tr_exp head, Tr_exp tail){
  ASSERT(head && tail);
  return Tr_Nx(
      T_Seq(unNx(head), unNx(tail))
    );
}

Tr_exp Tr_IfStm(Tr_exp test, Tr_exp then, Tr_exp elsee){
  Cx cond = unCx(test);
  if(!then && !elsee){
    Temp_label j = Temp_newlabel();
    doPatch(cond->trues, j);
    doPatch(cond->falses, j);
    return Sequence(
        cond->stm,
        T_Label(j)
    );
  }

  Temp_label t = Temp_newlabel();
  Temp_label f = Temp_newlabel();
  doPatch(cond->trues, t);
  doPatch(cond->falses, f);
  if(!then && elsee){
    return Sequence(
      cond->stm,
      T_Label(f),
      unNx(elsee),
      T_Label(t)
    );
  }
  if(elsee){
    Temp_label end = Temp_newlabel();
    return Sequence(
      cond->stm,
      T_Label(t),
      unNx(then),
      T_Jump(end),
      T_Label(f),
      unNx(elsee),
      T_Label(end)
    );
  }
  return Sequence(
    cond->stm,
    T_Label(t),
    unNx(then),
    T_Label(f)
  );
}

Tr_exp Tr_WhileStm(Tr_exp test, Tr_exp loop, Temp_label whiletest, Temp_label whileend){
  Cx cond = unCx(test);
  if(loop){
    Temp_label body = Temp_newlabel();
    doPatch(cond->trues, body);
    doPatch(cond->falses, whileend);
    return Sequence(
      T_Label(whiletest),
      cond->stm,
      T_Label(body),
      unNx(loop),
      T_Jump(whiletest),
      T_Label(whileend)
    );
  }
  doPatch(cond->trues, whiletest);
  doPatch(cond->falses, whileend);
  return Sequence(
    T_Label(whiletest),
    cond->stm,
    T_Label(whileend)
  );
}

Tr_exp Tr_AssignStm(Tr_exp location, Tr_exp value){
  T_exp loc = unEx(location);
  ASSERT(loc->kind == T_MEM || loc->kind == T_TEMP);
  T_exp val = unEx(value);
  val = smart_cast(val, loc->type);
  return Tr_Nx(T_Move(loc, val));
}

Tr_exp Tr_ArrayInit(Tr_exp arr, Tr_expList init, T_type type){
  T_exp a = unEx(arr);
  T_stm mlc = T_Move(a, NULL);
  T_stm len = T_Move(T_Mem(T_Binop(T_minus, a, T_IntConst(-SEM_ARCH_SIZE)), T_int), NULL);
  seqBufClear();
  seqBufPush(Tr_Nx(mlc));
  seqBufPush(Tr_Nx(len));
  unsigned count = 0;
  while(init){
    T_exp e = unEx(init->head);
    // ASSERT(e->kind == T_CONST);;
    e = smart_cast(e, type);
    ASSERT(e);
    if(count)seqBufPush(Tr_Nx(T_Move(T_Mem(T_Binop(T_plus, a, T_IntConst(SEM_ARCH_SIZE * count)), type), e)));
    else seqBufPush(Tr_Nx(T_Move(T_Mem(a, T_int), e)));
    init = init->tail;
    count++;
  }
  mlc->u.MOVE.src = T_Binop(T_plus, T_ExtCall(String("malloc"), T_ExpList(T_IntConst((count + 1) * SEM_ARCH_SIZE), NULL), T_int), T_IntConst(SEM_ARCH_SIZE));
  len->u.MOVE.src = T_IntConst(count);

  Tr_exp ret = SequenceFromBuffer();
  seqBufClear();
  return ret;
}

Tr_exp Tr_CallStm(string meth, Tr_exp clazz, Tr_exp thiz, Tr_expList el, T_type type, unsigned long long offset){
  T_expList tel = T_ExpList(unEx(thiz), NULL);
  T_expList it = tel;
  while(el){
    it->tail = T_ExpList(unEx(el->head), NULL), it = it->tail;
    el = el->tail;
  }
  T_exp meth_addr = offset ? T_Mem(T_Binop(T_plus, unEx(clazz), T_IntConst(offset)), T_int) : unEx(clazz);
  return Tr_Ex(T_Call(
    meth,
    meth_addr,
    tel,
    type
  ));
}

Tr_exp Tr_Continue(Temp_label whiletest){
  return Tr_Nx(T_Jump(whiletest));
}

Tr_exp Tr_Break(Temp_label whileend){
  return Tr_Nx(T_Jump(whileend));
}

Tr_exp Tr_Return(Tr_exp ret, T_type type){
  T_exp ret_val = unEx(ret);
  ret_val = smart_cast(ret_val, type);
  Tr_exp r = Tr_Nx(T_Return(ret_val));
  return r;
}

Tr_exp Tr_Putint(Tr_exp exp){
  T_exp val = unEx(exp);
  val = smart_cast(val, T_int);
  return Tr_Ex(T_ExtCall(String("putint"), T_ExpList(val, NULL), T_int));
}

Tr_exp Tr_Putfloat(Tr_exp exp){
  T_exp val = unEx(exp);
  val = smart_cast(val, T_float);
  return Tr_Ex(T_ExtCall(String("putfloat"), T_ExpList(val, NULL), T_int));
}

Tr_exp Tr_Putch(Tr_exp exp){
  T_exp val = unEx(exp);
  val = smart_cast(val, T_int);
  return Tr_Ex(T_ExtCall(String("putch"), T_ExpList(val, NULL), T_int));
}

Tr_exp Tr_Putarray(Tr_exp pos, Tr_exp arr){
  return Tr_Ex(
    T_ExtCall(String("putarray"), T_ExpList(unEx(pos), T_ExpList(unEx(arr), NULL)), T_int)
  );
}

Tr_exp Tr_Starttime(){
  return Tr_Ex(T_ExtCall(String("starttime"), NULL, T_int));
}

Tr_exp Tr_Stoptime(){
  return Tr_Ex(T_ExtCall(String("stoptime"), NULL, T_int));
}

// exps
Tr_expList Tr_ExpList(Tr_exp head, Tr_expList tail){
  Tr_expList p = checked_malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

Tr_exp Tr_OpExp(A_binop op, Tr_exp left, Tr_exp right){
  T_stm rel_stm;
  if(op == A_and || op == A_or){
    Cx lcx = unCx(left);
    Cx rcx = unCx(right);
    Temp_label next = Temp_newlabel();
    doPatch(op == A_and ? lcx->trues : lcx->falses, next);
    joinPatch(op == A_and ? lcx->falses : lcx->trues,
              op == A_and ? rcx->falses : rcx->trues);
    Tr_exp stm = Sequence(
      lcx->stm,
      T_Label(next),
      rcx->stm
    );
    return Tr_Cx(
      op == A_and ? rcx->trues : lcx->trues,
      op == A_and ? lcx->falses : rcx->falses,
      unNx(stm)
    );
  }

  switch(op){
    case A_plus: return Tr_Ex(T_Binop(T_plus, unEx(left), unEx(right)));
    case A_minus: return Tr_Ex(T_Binop(T_minus, unEx(left), unEx(right)));
    case A_times: return Tr_Ex(T_Binop(T_mul, unEx(left), unEx(right)));
    case A_div: return Tr_Ex(T_Binop(T_div, unEx(left), unEx(right)));
    case A_less: rel_stm = T_Cjump(T_lt, unEx(left), unEx(right), NULL, NULL); break;
    case A_le: rel_stm = T_Cjump(T_le, unEx(left), unEx(right), NULL, NULL); break;
    case A_greater: rel_stm = T_Cjump(T_gt, unEx(left), unEx(right), NULL, NULL); break;
    case A_ge: rel_stm = T_Cjump(T_ge, unEx(left), unEx(right), NULL, NULL); break;
    case A_eq: rel_stm = T_Cjump(T_eq, unEx(left), unEx(right), NULL, NULL); break;
    case A_ne: rel_stm = T_Cjump(T_ne, unEx(left), unEx(right), NULL, NULL); break;
    default: ASSERT(0);
  }
  return Tr_Cx(
    PatchList(&rel_stm->u.CJUMP.t, NULL), 
    PatchList(&rel_stm->u.CJUMP.f, NULL), 
    rel_stm
    );
}

Tr_exp Tr_ArrayExp(Tr_exp arr, Tr_exp pos, T_type type){
  T_exp off = unEx(pos);
  if(off->kind == T_CONST)off = T_IntConst(SEM_ARCH_SIZE * (off->type == T_int ? off->u.CONST.i : off->u.CONST.f));
  else off = T_Binop(T_mul, off, T_IntConst(SEM_ARCH_SIZE));

  return Tr_Ex(
    T_Mem(T_Binop(T_plus, unEx(arr), off), type)
  );
}

Tr_exp Tr_CallExp(string meth, Tr_exp clazz, Tr_exp thiz, Tr_expList el, T_type type, unsigned long long offset){
  T_expList tel = T_ExpList(unEx(thiz), NULL);
  T_expList it = tel;
  while(el){
    it->tail = T_ExpList(unEx(el->head), NULL), it = it->tail;
    el = el->tail;
  }
  T_exp meth_addr = offset ? T_Mem(T_Binop(T_plus, unEx(clazz), T_IntConst(offset)), T_int) : unEx(clazz);
  Temp_temp t = Temp_newtemp(type);
  return Tr_Ex(
    T_Eseq(
      T_Move(
        T_Temp(t), 
        T_Call(
          meth,
          meth_addr,
          tel,
          type
          )
      ),
      T_Temp(t)
    ));
}

Tr_exp Tr_ClassVarExp(Tr_exp clazz, unsigned long long offset, T_type type){
  if(offset == 0)return Tr_Ex(
    T_Mem(unEx(clazz), type)
  );
  return Tr_Ex(
    T_Mem(T_Binop(T_plus, unEx(clazz), T_IntConst(offset)), type)
  );
}

Tr_exp Tr_ClassMethExp(Tr_exp clazz, Tr_exp offset){
  ASSERT(0);
}

Tr_exp Tr_ClassMethLabel(Temp_label label){
  ASSERT(0);
}

Tr_exp Tr_BoolConst(bool b){
  return Tr_Ex(T_IntConst(b));
}

Tr_exp Tr_NumConst(float num, T_type type){
  if(type == T_int)return Tr_Ex(T_IntConst(num));
  return Tr_Ex(T_FloatConst(num));
}

Tr_exp Tr_LengthExp(Tr_exp arr){
  return Tr_Ex(
    T_Mem(T_Binop(T_minus, unEx(arr), T_IntConst(SEM_ARCH_SIZE)), T_int)
  );
}

Tr_exp Tr_IdExp(Temp_temp tmp){
  return Tr_Ex(T_Temp(tmp));
}

Tr_exp Tr_ThisExp(Temp_temp tmp){
  return Tr_Ex(T_Temp(tmp));
}

Tr_exp Tr_NewArrExp(Tr_exp size){
  Temp_temp t = Temp_newtemp(T_int);
  T_exp sz = unEx(size);
  if(sz->kind == T_CONST){
    if(sz->type == T_float)sz = T_IntConst(sz->u.CONST.f);
    T_exp alloc_sz = T_IntConst((sz->u.CONST.i + 1) * SEM_ARCH_SIZE);
    return Tr_Ex(
      T_Eseq(
        unNx(
          Sequence(
            T_Move(
              T_Temp(t),
              T_ExtCall(String("malloc"), T_ExpList(alloc_sz, NULL), T_int)
            ),
            T_Move(
              T_Mem(T_Temp(t), T_int),
              sz
            ),
            T_Move(
              T_Temp(t),
              T_Binop(T_plus, T_Temp(t), T_IntConst(SEM_ARCH_SIZE))
            )
          )
        ),
        T_Temp(t)
      )
    );
  }
  else {
    Temp_temp sz_t = Temp_newtemp(T_int);
    Temp_temp alloc_sz_t = Temp_newtemp(T_int);
    return Tr_Ex(
      T_Eseq(
        unNx(Sequence(
          T_Move(
            T_Temp(sz_t),
            sz
          ),
          T_Move(
            T_Temp(alloc_sz_t),
            T_Binop(T_mul, T_Binop(T_plus, T_Temp(sz_t), T_IntConst(1)), T_IntConst(SEM_ARCH_SIZE))
          ),
          T_Move(
            T_Temp(t),
            T_ExtCall(String("malloc"), T_ExpList(T_Temp(alloc_sz_t), NULL), T_int)
          ),
          T_Move(
            T_Mem(T_Temp(t), T_int),
            T_Temp(sz_t)
          ),
          T_Move(
            T_Temp(t),
            T_Binop(T_plus, T_Temp(t), T_IntConst(SEM_ARCH_SIZE))
          )
        )),
        T_Temp(t)
      )
    );
  }
}

Tr_exp Tr_NewObjExp(S_symbol cls_name, E_enventry offset_entry, E_enventry cls, S_table method_map){
  Temp_temp t = Temp_newtemp(T_int);
  Tr_exp ret = NULL;
  seqBufClear();
  seqBufPush(Tr_Nx(T_Move(
          T_Temp(t),
          T_ExtCall(String("malloc"), T_ExpList(T_IntConst(offset_entry->u.off.local_size), NULL), T_int)
        )));
  
  // try to init class varibles
  _for_in_table(iter, cls->u.cls.vtbl){
    E_enventry ve = iter->value;
    T_exp offset = T_IntConst((int)(unsigned long long)S_look(offset_entry->u.off.local_offtbl, S_Symbol(ve->u.var.vd->v)));
    T_exp addr = offset->u.CONST.i ? T_Binop(T_plus, T_Temp(t), offset) : T_Temp(t);
    A_expList init = ve->u.var.vd->elist;
    if(!init)break; // no need to init
    switch(ve->u.var.vd->t->t){
        case A_intType:
        case A_floatType: {
          seqBufPush(Tr_Nx(
          T_Move(
              T_Mem(addr, T_int), 
              ve->u.var.vd->t->t == A_intType ? T_IntConst(init->head->u.num) : T_FloatConst(init->head->u.num)
              )
          ));
          }
          break;
        case A_intArrType: 
        case A_floatArrType: {
          // alloc memory
          // init arrays into temp a(that contains the address of the array)
          Temp_temp arr = Temp_newtemp(T_int);
          T_exp a = T_Temp(arr);
          T_stm mlc = T_Move(a, NULL);
          T_stm len = T_Move(T_Mem(T_Binop(T_minus, a, T_IntConst(-SEM_ARCH_SIZE)), T_int), NULL);
          seqBufPush(Tr_Nx(mlc));
          seqBufPush(Tr_Nx(len));
          unsigned count = 0;
          T_type type = ve->u.var.vd->t->t == A_intArrType ? T_int : T_float;
          while(init){
            ASSERT(init->head->kind == A_numConst);
            T_exp e = type == T_int ? T_IntConst(init->head->u.num) : T_FloatConst(init->head->u.num);
            ASSERT(e);
            if(count)seqBufPush(Tr_Nx(T_Move(T_Mem(T_Binop(T_plus, a, T_IntConst(SEM_ARCH_SIZE * count)), type), e)));
            else seqBufPush(Tr_Nx(T_Move(T_Mem(a, T_int), e)));
            init = init->tail;
            count++;
          }
          mlc->u.MOVE.src = T_Binop(T_plus, T_ExtCall(String("malloc"), T_ExpList(T_IntConst((count + 1) * SEM_ARCH_SIZE), NULL), T_int), T_IntConst(SEM_ARCH_SIZE));
          len->u.MOVE.src = T_IntConst(count);

          seqBufPush(Tr_Nx(
            T_Move(
              T_Mem(addr, T_int), 
              a
            )));
        } break;
        case A_idType: break; // no need to init
        ASSERT(0);
    }
  }

  // init class methods
  _for_in_table(iter, cls->u.cls.mtbl){
    E_enventry me = iter->value;
    T_exp offset = T_IntConst((int)(unsigned long long)S_look(offset_entry->u.off.local_offtbl, S_link(S_Symbol("0295"), S_Symbol(me->u.meth.md->id))));
    T_exp addr = offset->u.CONST.i ? T_Binop(T_plus, T_Temp(t), offset) : T_Temp(t);

    S_symbol name = S_link(cls_name, S_Symbol(me->u.meth.md->id));
    if(S_look(method_map, name)){
      // do map
      name = S_look(method_map, name);
    }
    seqBufPush(Tr_Nx(
      T_Move(
        T_Mem(addr, T_int),
        T_Name(Temp_namedlabel(S_name(name)))
      )
    ));
  }

  ret = SequenceFromBuffer();
  seqBufClear();
  return Tr_Ex(
    T_Eseq(
      unNx(ret),
      T_Temp(t)
    )
  );
}

Tr_exp Tr_NotExp(Tr_exp exp){
  Cx tmp = unCx(exp);
  return Tr_Cx(tmp->falses, tmp->trues, tmp->stm);
}

Tr_exp Tr_MinusExp(Tr_exp exp){
  return Tr_Ex(T_Binop(T_minus, T_IntConst(0), unEx(exp)));
}

Tr_exp Tr_EscExp(Tr_exp stm, Tr_exp exp){
  return Tr_Ex(T_Eseq(unNx(stm), unEx(exp)));
}

Tr_exp Tr_Getint(){
  return Tr_Ex(T_ExtCall(String("getint"), NULL, T_int));
}

Tr_exp Tr_Getfloat(){
  return Tr_Ex(T_ExtCall(String("getfloat"), NULL, T_float));
}

Tr_exp Tr_Getch(){
  return Tr_Ex(T_ExtCall(String("getch"), NULL, T_int));
}

Tr_exp Tr_Getarray(Tr_exp exp){
  return Tr_Ex(T_ExtCall(String("getarray"), T_ExpList(unEx(exp), NULL), T_int));
}

Tr_exp Tr_Getfarray(Tr_exp exp){
  return Tr_Ex(T_ExtCall(String("getfarray"), T_ExpList(unEx(exp), NULL), T_int));
}

// interface for insert vtbl
Tr_exp Tr_intInit(Temp_temp t, int val){
  return Tr_Nx(T_Move(T_Temp(t), T_IntConst(val)));
}

Tr_exp Tr_floatInit(Temp_temp t, float val){
  return Tr_Nx(T_Move(T_Temp(t), T_FloatConst(val)));
}

Tr_exp Tr_intArrInit(Temp_temp t, Tr_expList init){
  return Tr_ArrayInit(Tr_Ex(T_Temp(t)), init, T_int);
}

Tr_exp Tr_floatArrInit(Temp_temp t, Tr_expList init){
  return Tr_ArrayInit(Tr_Ex(T_Temp(t)), init, T_float);
}

// locate an obj to a temp
// especially for escExp

Tr_exp locate_obj_temp(Tr_exp* obj){
  // obj type has been guaranteed outside
  T_exp obj_rep = unEx(*obj);
  if(obj_rep->kind == T_TEMP)return *obj;
  Temp_temp t = Temp_newtemp(T_int);
  *obj = Tr_Ex(
    T_Eseq(
      T_Move(T_Temp(t), obj_rep),
      T_Temp(t)
    )
  );
  return Tr_Ex(T_Temp(t));
}

T_exp smart_cast(T_exp exp, T_type type){
  if(exp->type == type)return exp;
  else if(exp->kind == T_CONST)return exp->type == T_int ? T_FloatConst(exp->u.CONST.i) : T_IntConst(exp->u.CONST.f);
  return T_Cast(exp, type);
}