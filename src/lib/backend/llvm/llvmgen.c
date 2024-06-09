#include "util.h"
#include "temp.h"
#include "llvmgen.h"

#define LLVMGEN_DEBUG
#undef LLVMGEN_DEBUG

static AS_instrList iList = NULL, last = NULL; //These are for collecting the AS instructions into a list (i.e., iList). 
                                               //last is the last instruction in ilist
static void emit(AS_instr inst) {
  if (last) {
    last = last->tail = AS_InstrList(inst, NULL); //add the instruction to the (nonempty) ilist to the end
  } else {
    last = iList = AS_InstrList(inst, NULL); //if this is the first instruction, make it the head of the list
  }
}

static Temp_tempList TL(Temp_temp t, Temp_tempList tl) {
  return Temp_TempList(t, tl);
}

static Temp_tempList TLS(Temp_tempList a, Temp_tempList b) {
  return Temp_TempListSplice(a, b);
}

static Temp_labelList LL(Temp_label l, Temp_labelList ll) {
  return Temp_LabelList(l, ll);
}

/* ********************************************************/
/* YOU ARE TO IMPLEMENT THE FOLLOWING FUNCTION FOR HW9_10 */
/* ********************************************************/
static Temp_temp munchExp(T_exp e, Temp_temp move_ret) {
  if(!e)return NULL;
  switch(e->kind) {
    case T_BINOP: {
      INFO("[Exp] binop\n");
      Temp_temp ret = move_ret ? move_ret : Temp_newtemp(e->type);

      string buf = (string)checked_malloc(IR_MAXLEN);
      string op = NULL;
      string type = ret->type == T_int ? "i64" : "double";
      switch(e->u.BINOP.op) {
        case T_plus: op = ret->type == T_int ? "add" : "fadd"; break;
        case T_minus: op = ret->type == T_int ? "sub" : "fsub"; break;
        case T_mul: op = ret->type == T_int ? "mul" : "fmul"; break;
        case T_div: op = ret->type == T_int ? "sdiv" : "fdiv"; break;
        default: ASSERT(0);
      }

      if(e->u.BINOP.left->kind != T_CONST && e->u.BINOP.right->kind != T_CONST){
        Temp_temp lt = munchExp(e->u.BINOP.left, NULL);
        Temp_temp rt = munchExp(e->u.BINOP.right, NULL);
        sprintf(buf, "%%`d0 = %s %s %%`s0, %%`s1", op, type);
        emit(AS_Oper(buf, TL(ret, NULL), TL(lt, TL(rt, NULL)), NULL));
      }
      else if(e->u.BINOP.left->kind != T_CONST){
        // right operand is a const
        Temp_temp lt = munchExp(e->u.BINOP.left, NULL);
        if(e->u.BINOP.right->type == T_int)sprintf(buf, "%%`d0 = %s %s %%`s0, %d", op, type, e->u.BINOP.right->u.CONST.i);
        else sprintf(buf, "%%`d0 = %s %s %%`s0, %f", op, type, e->u.BINOP.right->u.CONST.f);
        emit(AS_Oper(buf, TL(ret, NULL), TL(lt, NULL), NULL));
      }
      else if(e->u.BINOP.right->kind != T_CONST){
        // left operand is a const
        Temp_temp rt = munchExp(e->u.BINOP.right, NULL);
        if(e->u.BINOP.left->type == T_int)sprintf(buf, "%%`d0 = %s %s %d, %%`s0", op, type, e->u.BINOP.left->u.CONST.i);
        else sprintf(buf, "%%`d0 = %s %s %f, %%`s0", op, type, e->u.BINOP.left->u.CONST.f);
        emit(AS_Oper(buf, TL(ret, NULL), TL(rt, NULL), NULL));
      }
      else {
        // both are consts
        // compute result at compile time
        // this does optimize for (f)div and (f)mul
        if(e->type == T_int)sprintf(buf, "%%`d0 = add %d, 0", e->u.BINOP.left->u.CONST.i + e->u.BINOP.right->u.CONST.i);
        else sprintf(buf, "%%`d0 = fadd %f, 0", e->u.BINOP.left->u.CONST.f + e->u.BINOP.right->u.CONST.f);
        emit(AS_Oper(buf, TL(ret, NULL), NULL, NULL));
      }
      
      return ret;
    }
    case T_MEM: {
      INFO("[Exp] mem\n");
      Temp_temp ret = move_ret ? move_ret : Temp_newtemp(e->type);
      Temp_temp loc = munchExp(e->u.MEM, NULL);
      Temp_temp ptr = Temp_newtemp(T_int);
      
      emit(AS_Oper("\%`d0 = inttoptr i64 \%`s0 to i64*", TL(ptr, NULL), TL(loc, NULL), NULL));
      if(ret->type == T_int)emit(AS_Oper("\%`d0 = load i64, i64* \%`s0, align 8", TL(ret, NULL), TL(ptr, NULL), NULL));
      else emit(AS_Oper("\%`d0 = load double, i64* \%`s0, align 8", TL(ret, NULL), TL(ptr, NULL), NULL));
      return ret;
    }
    case T_TEMP: {
      INFO("[Exp] temp\n");
      if(move_ret){
        if(move_ret->type == T_int)emit(AS_Move("\%`d0 = add i64 \%`s0, 0", TL(move_ret, NULL), TL(e->u.TEMP, NULL)));
        else emit(AS_Move("\%`d0 = fadd double \%`s0, 0.0", TL(move_ret, NULL), TL(e->u.TEMP, NULL)));
        return move_ret;
      }
      return e->u.TEMP;
    }
    case T_ESEQ: INFO("linearization error!\n"); ASSERT(0);
    case T_NAME: {
      INFO("[Exp] name\n");
      string buf = (string)checked_malloc(IR_MAXLEN);
      sprintf(buf, "%%`d0 = ptrtoint i64* @%s to i64", Temp_labelstring(e->u.NAME));
      Temp_temp ret = move_ret ? move_ret : Temp_newtemp(T_int);
      emit(AS_Oper(buf, TL(ret, NULL), NULL, NULL));
      return ret;
    }
    case T_CONST: {
      INFO("[Exp] const\n");
      Temp_temp ret = move_ret ? move_ret : Temp_newtemp(e->type);
      string buf = (string)checked_malloc(IR_MAXLEN);
      if(ret->type == T_int)sprintf(buf, "%%`d0 = add i64 %d, 0", e->u.CONST.i);
      else sprintf(buf, "%%`d0 = fadd double %f, 0.0", e->u.CONST.f);
      emit(AS_Oper(buf, TL(ret, NULL), NULL, NULL));
      return ret;
    }
    case T_CALL: {
      INFO("[Exp] call\n");
      Temp_temp func = munchExp(e->u.CALL.obj, NULL);
      Temp_temp func_ptr = Temp_newtemp(T_int);
      emit(AS_Oper("\%`d0 = inttoptr i64 \%`s0 to i64*", TL(func_ptr, NULL), TL(func, NULL), NULL));

      T_expList exps = e->u.CALL.args;
      Temp_temp ret = move_ret ? move_ret : Temp_newtemp(T_int);
      string buf = (string)checked_malloc(IR_MAXLEN);
      if(e->type == T_int)sprintf(buf, "%%`d0 = call i64 %%`s0(i64 %%`s1");
      else sprintf(buf, "%%`d0 = call double %%`s0(i64 %%`s1");

      ASSERT(exps);
      Temp_tempList args = TL(munchExp(exps->head, NULL), NULL);
      Temp_tempList it = args;
      exps = exps->tail;
      int count = 2;
      while(exps){
        sprintf(buf + strlen(buf), ", %s %%`s%d", exps->head->type == T_int ? "i64" : "double", count++);
        it = it->tail = TL(munchExp(exps->head, NULL), NULL);
        exps = exps->tail;
      }
      sprintf(buf + strlen(buf), ")");

      emit(AS_Oper(buf, TL(ret, NULL), TL(func_ptr, args), NULL));
      return ret;
    }
    case T_ExtCALL: {
      INFO("[Exp] extcall\n");
      if(!strcmp(e->u.ExtCALL.extfun, "malloc")) {
        Temp_temp ret = move_ret ? move_ret : Temp_newtemp(T_int);
        Temp_temp tmp = Temp_newtemp(T_int);
        if(e->u.ExtCALL.args->head->kind != T_CONST)
          emit(AS_Oper("\%`d0 = call i64* @malloc(i64 \%`s0)", TL(tmp, NULL), TL(munchExp(e->u.ExtCALL.args->head, NULL), NULL), NULL));
        else{
          string format = (string)checked_malloc(IR_MAXLEN);
          sprintf(format, "%%`d0 = call i64* @malloc(i64 %d)", e->u.ExtCALL.args->head->u.CONST.i);
          emit(AS_Oper(format, TL(tmp, NULL), NULL, NULL));
        }
        emit(AS_Oper("\%`d0 = ptrtoint i64* \%`s0 to i64", TL(ret, NULL), TL(tmp, NULL), NULL));
        return ret;
      }
      else if(!strcmp(e->u.ExtCALL.extfun, "starttime")){
        emit(AS_Oper("call void @starttime()", NULL, NULL, NULL));
        return NULL;
      }
      else if(!strcmp(e->u.ExtCALL.extfun, "stoptime")){
        emit(AS_Oper("call void @stoptime()", NULL, NULL, NULL));
        return NULL;
      }
      else if(!strcmp(e->u.ExtCALL.extfun, "putint")){
        if(e->u.ExtCALL.args->head->kind != T_CONST)
          emit(AS_Oper("call void @putint(i64 \%`s0)", NULL, TL(munchExp(e->u.ExtCALL.args->head, NULL), NULL), NULL));
        else {
          string format = (string)checked_malloc(IR_MAXLEN);
          sprintf(format, "call void @putint(i64 %d)", e->u.ExtCALL.args->head->u.CONST.i);
          emit(AS_Oper(format, NULL, NULL, NULL));
        }
        return NULL;
      }
      else if(!strcmp(e->u.ExtCALL.extfun, "putfloat")){
        if(e->u.ExtCALL.args->head->kind != T_CONST)
          emit(AS_Oper("call void @putfloat(double \%`s0)", NULL, TL(munchExp(e->u.ExtCALL.args->head, NULL), NULL), NULL));
        else {
          string format = (string)checked_malloc(IR_MAXLEN);
          sprintf(format, "call void @putfloat(i64 %f)", e->u.ExtCALL.args->head->u.CONST.f);
          emit(AS_Oper(format, NULL, NULL, NULL));
        }
        return NULL;
      }
      else if(!strcmp(e->u.ExtCALL.extfun, "putch")){
        if(e->u.ExtCALL.args->head->kind != T_CONST)
          emit(AS_Oper("call void @putch(i64 \%`s0)", NULL, TL(munchExp(e->u.ExtCALL.args->head, NULL), NULL), NULL));
        else {
          string format = (string)checked_malloc(IR_MAXLEN);
          sprintf(format, "call void @putch(i64 %d)", e->u.ExtCALL.args->head->u.CONST.i);
          emit(AS_Oper(format, NULL, NULL, NULL));
        }
        return NULL;
      }
      else if(!strcmp(e->u.ExtCALL.extfun, "getint")){
        Temp_temp ret = move_ret ? move_ret : Temp_newtemp(T_int);
        emit(AS_Oper("\%`d0 = call i64 @getint()", TL(ret, NULL), NULL, NULL));
        return ret;
      }
      else if(!strcmp(e->u.ExtCALL.extfun, "getfloat")){
        Temp_temp ret = move_ret ? move_ret : Temp_newtemp(T_float);
        emit(AS_Oper("\%`d0 = call double @getfloat()", TL(ret, NULL), NULL, NULL));
        return ret;
      }
      else if(!strcmp(e->u.ExtCALL.extfun, "getch")){
        Temp_temp ret = move_ret ? move_ret : Temp_newtemp(T_int);
        emit(AS_Oper("\%`d0 = call i64 @getch()", TL(ret, NULL), NULL, NULL));
        return ret;
      }
      else if(!strcmp(e->u.ExtCALL.extfun, "putarray")){
        Temp_temp loc_val = munchExp(e->u.ExtCALL.args->tail->head, NULL);
        Temp_temp ptr = Temp_newtemp(T_int);
        emit(AS_Oper("\%`d0 = inttoptr i64 \%`s0 to i64*", TL(ptr, NULL), TL(loc_val, NULL), NULL));

        if(e->u.ExtCALL.args->head->kind != T_CONST){
          Temp_temp pos = munchExp(e->u.ExtCALL.args->head, NULL);
          emit(AS_Oper("call void @putarray(i64 \%`s0, i64* \%`s1)", NULL, TL(pos, TL(ptr, NULL)), NULL));
        }
        else {
          string format = (string)checked_malloc(IR_MAXLEN);
          sprintf(format, "call void @putarray(i64 %d, i64* %%`s0)", e->u.ExtCALL.args->head->u.CONST.i);
          emit(AS_Oper(format, NULL, TL(ptr, NULL), NULL));
        }

        return NULL;
      }
      else if(!strcmp(e->u.ExtCALL.extfun, "getarray")){
        Temp_temp ret = move_ret ? move_ret : Temp_newtemp(T_int);
        Temp_temp ptr = Temp_newtemp(T_int);
        emit(AS_Oper("\%`d0 = inttoptr i64 \%`s0 to i64*", TL(ptr, NULL), TL(munchExp(e->u.ExtCALL.args->head, NULL), NULL), NULL));
        emit(AS_Oper("\%`d0 = call i64 @getarray(i64* \%`s0)", TL(ret, NULL), TL(ptr, NULL), NULL));
        return ret;
      }
      else if(!strcmp(e->u.ExtCALL.extfun, "getfarray")){
        Temp_temp ret = move_ret ? move_ret : Temp_newtemp(T_int);
        Temp_temp ptr = Temp_newtemp(T_int);
        emit(AS_Oper("\%`d0 = inttoptr i64 \%`s0 to i64*", TL(ptr, NULL), TL(munchExp(e->u.ExtCALL.args->head, NULL), NULL), NULL));
        emit(AS_Oper("\%`d0 = call i64 @getfarray(i64* \%`s0)", TL(ret, NULL), TL(ptr, NULL), NULL));
        return ret;
      }
    }
    case T_CAST: {
      INFO("[Exp] cast\n");
      Temp_temp ret = move_ret ? move_ret : Temp_newtemp(e->type);
      if(e->type == T_int)
        emit(AS_Oper("\%`d0 = fptosi double \%`s0 to i64", TL(ret, NULL), TL(munchExp(e->u.CAST, NULL), NULL), NULL));
      else
        emit(AS_Oper("\%`d0 = sitofp i64 \%`s0 to double", TL(ret, NULL), TL(munchExp(e->u.CAST, NULL), NULL), NULL));
      return ret;
    }
    default: ASSERT(0);
  }
}

static void munchMove(T_stm s) {
  ASSERT(s->kind == T_MOVE);
  T_exp dst = s->u.MOVE.dst;
  switch(dst->kind) {
    case T_MEM: {
      INFO("[Move] dst is mem\n");
      Temp_temp addr = munchExp(dst->u.MEM, NULL);
      ASSERT(addr->type == T_int);
      Temp_temp t = Temp_newtemp(T_int);
      emit(AS_Oper("\%`d0 = inttoptr i64 \%`s0 to i64*", TL(t, NULL), TL(addr, NULL), NULL));

      if(s->u.MOVE.src->kind != T_CONST){
        // not directly const, need to fetch by a temp
        Temp_temp src = munchExp(s->u.MOVE.src, NULL);
        if(src->type == T_int)emit(AS_Oper("store i64 \%`s0, i64* \%`d0, align 8", TL(t, NULL), TL(src, NULL), NULL));
        else emit(AS_Oper("store double \%`s0, i64* \%`d0, align 8", TL(t, NULL), TL(src, NULL), NULL));
      }
      else {
        // specially for const
        string assem = (string)checked_malloc(IR_MAXLEN);
        if(s->u.MOVE.src->type == T_int)sprintf(assem, "store i64 %d, i64* %%`d0, align 8", s->u.MOVE.src->u.CONST.i);
        else sprintf(assem, "store double %f, i64* %%`d0, align 8", s->u.MOVE.src->u.CONST.f);
        emit(AS_Oper(assem, TL(t, NULL), NULL, NULL));
      }
    } break;
    case T_TEMP: {
      INFO("[Move] dst is temp\n");
      Temp_temp src = munchExp(s->u.MOVE.src, dst->u.TEMP);

      // if(dst->type == T_int)emit(AS_Move("\%`d0 = add i64 \%`s0, 0", TL(dst->u.TEMP, NULL), TL(src, NULL)));
      // else emit(AS_Move("\%`d0 = fadd double \%`s0, 0.0", TL(dst->u.TEMP, NULL), TL(src, NULL)));
    } break;
    default: ASSERT(0);
  }
}

static void munchStm(T_stm s) {
  if(!s)return;
  switch(s->kind) {
    case T_SEQ: INFO("linearization error!\n"); ASSERT(0);
    case T_LABEL: {
      INFO("[Stm] label\n");
      string rd = checked_malloc(IR_MAXLEN);
      sprintf(rd, "%s:", Temp_labelstring(s->u.LABEL));
      emit(AS_Label(rd, s->u.LABEL)); 
    } break;
    case T_JUMP: {
      INFO("[Stm] jump\n");
       emit(AS_Oper("br label \%`j0", NULL, NULL, AS_Targets(LL(s->u.JUMP.jump, NULL))));
    } break;
    case T_CJUMP: {
      INFO("[Stm] cjump\n");
      Temp_temp tb = Temp_newtemp(T_int);

      string rd = checked_malloc(IR_MAXLEN);
      T_type tp = s->u.CJUMP.left->type;
      string op = NULL;
      switch(s->u.CJUMP.op) {
        case T_eq: op = tp == T_int ? "eq" : "oeq"; break;
        case T_ne: op = tp == T_int ? "ne" : "one"; break;
        case T_lt: op = tp == T_int ? "slt" : "olt"; break;
        case T_gt: op = tp == T_int ? "sgt" : "ogt"; break;
        case T_le: op = tp == T_int ? "sle" : "ole"; break;
        case T_ge: op = tp == T_int ? "sge" : "oge"; break;
        default: ASSERT(0);
      }

      if(s->u.CJUMP.left->kind != T_CONST && s->u.CJUMP.right->kind != T_CONST){
        Temp_temp ll = munchExp(s->u.CJUMP.left, NULL);
        Temp_temp rl = munchExp(s->u.CJUMP.right, NULL);
        string format = tp == T_int ? "%%`d0 = icmp %s i64 %%`s0, %%`s1" : "%%`d0 = fcmp %s double %%`s0, %%`s1";
        sprintf(rd, format, op);
        emit(AS_Oper(rd, TL(tb, NULL), TL(ll, TL(rl, NULL)), NULL));
        emit(AS_Oper("br i1 \%`s0, label \%`j0, label \%`j1", NULL, TL(tb, NULL), AS_Targets(LL(s->u.CJUMP.t, LL(s->u.CJUMP.f, NULL)))));
      }
      else if(s->u.CJUMP.left->kind != T_CONST) {
        // right is a const
        Temp_temp ll = munchExp(s->u.CJUMP.left, NULL);
        string format = tp == T_int ? "%%`d0 = icmp %s i64 %%`s0, %d" : "%%`d0 = fcmp %s double %%`s0, %f";
        if(tp == T_int)sprintf(rd, format, op, s->u.CJUMP.right->u.CONST.i);
        else sprintf(rd, format, op, s->u.CJUMP.right->u.CONST.f);
        emit(AS_Oper(rd, TL(tb, NULL), TL(ll, NULL), NULL));
        emit(AS_Oper("br i1 \%`s0, label \%`j0, label \%`j1", NULL, TL(tb, NULL), AS_Targets(LL(s->u.CJUMP.t, LL(s->u.CJUMP.f, NULL)))));
      }
      else if(s->u.CJUMP.right->kind != T_CONST){
        // left is a const
        Temp_temp rl = munchExp(s->u.CJUMP.left, NULL);
        string format = tp == T_int ? "%%`d0 = icmp %s i64 %d, %%`s0" : "%%`d0 = fcmp %s double %f, %%`s0";
        if(tp == T_int)sprintf(rd, format, op, s->u.CJUMP.left->u.CONST.i);
        else sprintf(rd, format, op, s->u.CJUMP.left->u.CONST.f);
        emit(AS_Oper(rd, TL(tb, NULL), TL(rl, NULL), NULL));
        emit(AS_Oper("br i1 \%`s0, label \%`j0, label \%`j1", NULL, TL(tb, NULL), AS_Targets(LL(s->u.CJUMP.t, LL(s->u.CJUMP.f, NULL)))));
      }
      else {
        // both are consts
        // compute condition at compile time
        // using jump instead of cjump
        bool cnd = FALSE;
        switch(s->u.CJUMP.op) {
        case T_eq: cnd = tp == T_int ? s->u.CJUMP.left->u.CONST.i == s->u.CJUMP.right->u.CONST.i : s->u.CJUMP.left->u.CONST.f == s->u.CJUMP.right->u.CONST.f; break;
        case T_ne: cnd = tp == T_int ? s->u.CJUMP.left->u.CONST.i != s->u.CJUMP.right->u.CONST.i : s->u.CJUMP.left->u.CONST.f != s->u.CJUMP.right->u.CONST.f; break;
        case T_lt: cnd = tp == T_int ? s->u.CJUMP.left->u.CONST.i < s->u.CJUMP.right->u.CONST.i : s->u.CJUMP.left->u.CONST.f < s->u.CJUMP.right->u.CONST.f; break;
        case T_gt: cnd = tp == T_int ? s->u.CJUMP.left->u.CONST.i > s->u.CJUMP.right->u.CONST.i : s->u.CJUMP.left->u.CONST.f > s->u.CJUMP.right->u.CONST.f; break;
        case T_le: cnd = tp == T_int ? s->u.CJUMP.left->u.CONST.i <= s->u.CJUMP.right->u.CONST.i : s->u.CJUMP.left->u.CONST.f <= s->u.CJUMP.right->u.CONST.f; break;
        case T_ge: cnd = tp == T_int ? s->u.CJUMP.left->u.CONST.i >= s->u.CJUMP.right->u.CONST.i : s->u.CJUMP.left->u.CONST.f >= s->u.CJUMP.right->u.CONST.f; break;
        default: ASSERT(0);
        }
        if(cnd)emit(AS_Oper("br label \%`j0", NULL, NULL, AS_Targets(LL(s->u.CJUMP.t, NULL))));
        else emit(AS_Oper("br label \%`j0", NULL, NULL, AS_Targets(LL(s->u.CJUMP.f, NULL))));
      }

    } break;
    case T_MOVE: {
      INFO("[Stm] move\n");
      munchMove(s);
    } break;
    case T_EXP: {
      INFO("[Stm] exp\n");
      munchExp(s->u.EXP, NULL);
    } break;
    case T_RETURN: {
      INFO("[Stm] return\n");
      if(s->u.EXP->kind != T_CONST){
        Temp_temp ret = munchExp(s->u.EXP, NULL);
        if(ret->type == T_int)emit(AS_Oper("ret i64 \%`s0", NULL, TL(ret, NULL), NULL));
        else emit(AS_Oper("ret double \%`s0", NULL, TL(ret, NULL), NULL));
      }
      else {
        string assem = (string)checked_malloc(IR_MAXLEN);
        if(s->u.EXP->type == T_int)sprintf(assem, "ret i64 %d", s->u.EXP->u.CONST.i);
        else sprintf(assem, "ret double %f", s->u.EXP->u.CONST.f);
        emit(AS_Oper(assem, NULL, NULL, NULL));
      }
    } break;
    default: ASSERT(0);
  }
}

AS_instrList llvmbody(T_stmList stmList) {
  if (!stmList) return NULL;
  iList = last = NULL;


  // **The following is to make up an example of the instruction selection result.  
  //   You are supposed to implement this function. When you are done, remove the following code
  //   Follow the instruction from the class and the book!

  // Temp_label l = Temp_newlabel();
  // string rd=checked_malloc(IR_MAXLEN); sprintf(rd, "%s:", Temp_labelstring(l));
  // emit(AS_Label(rd,l)); 
  // emit(AS_Oper("\%`d0 = add i64 \%`s0, \%`s1", TL(Temp_newtemp(T_int), NULL), TL(Temp_newtemp(T_int), TL(Temp_newtemp(T_int), NULL)), NULL));
  // emit(AS_Oper("br label \%`j0", NULL, NULL, AS_Targets(LL(l, NULL))));

  /***** The above is to be removed! *****/

  while(stmList) {
    munchStm(stmList->head);
    stmList = stmList->tail;
  }

  return iList;
}
/* ********************************************************/
/* YOU ARE TO IMPLEMENT THE ABOVE FUNCTION FOR HW9_10 */
/* ********************************************************/

/* The following are some auxiliary functions to be used by the main */
// This function is to make the beginning of the function that jumps to the beginning label (lbeg) 
// of a block (in case the lbeg is NOT at the beginning of the block).
AS_instrList llvmbodybeg(Temp_label lbeg) {
  if (!lbeg) return NULL;
  iList = last = NULL;
  Temp_label lstart = Temp_newlabel();
  string ir = (string) checked_malloc(IR_MAXLEN);
  sprintf(ir, "%s:", Temp_labelstring(lstart));
  emit(AS_Label(ir, lstart));
  ir = (string) checked_malloc(IR_MAXLEN);
  sprintf(ir, "br label %%`j0");
  emit(AS_Oper(ir, NULL, NULL, AS_Targets(LL(lbeg, NULL))));
  return iList;
}

// This function is to make the prolog of the function that takes the method name and the arguments
// WE ARE MISSING THE RETURN TYPE in tigherirp.h. YOU NEED TO ADD IT!
AS_instrList llvmprolog(string methodname, Temp_tempList args, T_type rettype) {
#ifdef LLVMGEN_DEBUG
  fprintf(stderr, "llvmprolog: methodname=%s, rettype=%d\n", methodname, rettype);
#endif
  if (!methodname) return NULL;
  iList = last = NULL;
  string ir = (string) checked_malloc(IR_MAXLEN);
  if (rettype == T_int)
    sprintf(ir, "define i64 @%s(", methodname);
  else if (rettype == T_float)
    sprintf(ir, "define double @%s(", methodname);
#ifdef LLVMGEN_DEBUG
    fprintf(stderr, "llvmprolog: ir=%s\n", ir);
#endif
  if (args) {
    int i = 0;
    for (Temp_tempList arg = args; arg; arg = arg->tail, i += 1) {
      if (i!=0) sprintf(ir+strlen(ir), ", "); 
      if (arg->head->type == T_int) {
        sprintf(ir+strlen(ir), "i64 %%`s%d", i);
#ifdef LLVMGEN_DEBUG
        fprintf(stderr, "%d, llvmprolog: ir=%s\n", i, ir);
#endif  
      }
      else if (arg->head->type == T_float) {
#ifdef LLVMGEN_DEBUG
        fprintf(stderr, "%d, llvmprolog: ir=%s\n", i, ir);
#endif
        sprintf(ir+strlen(ir), "double %%`s%d", i);
      }
#ifdef LLVMGEN_DEBUG
      fprintf(stderr, "llvmprolog args: arg=%s\n", ir);
#endif
    }
  }
  sprintf(ir+strlen(ir), ") {");
#ifdef LLVMGEN_DEBUG
  fprintf(stderr, "llvmprolog final: ir=%s\n", ir);
#endif
  emit(AS_Oper(ir, NULL, args, NULL));
  return iList;
}

// This function is to make the epilog of the function that jumps to the end label (lend) of a block
AS_instrList llvmepilog(Temp_label lend) {
  if (!lend) return NULL;
  iList = last = NULL;
  // string ir = (string) checked_malloc(IR_MAXLEN);
  // sprintf(ir, "%s:", Temp_labelstring(lend));
  // emit(AS_Label(ir, lend));
  // emit(AS_Oper("ret i64 -1", NULL, NULL, NULL));
  emit(AS_Oper("}", NULL, NULL, NULL));
  return iList;
}