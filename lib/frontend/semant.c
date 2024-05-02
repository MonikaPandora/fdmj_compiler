#include "semant.h"

#define STACK_SIZE 128

int SEM_ARCH_SIZE; // to be set by arch_size in transA_Prog
static S_table CENV;
static S_table VENV;
static S_table OFFSET_ENV;
static S_table CLASS_INIT_ENV;
static S_symbol ROOTCLASS;
static S_symbol cur_cls;
static S_symbol cur_mtd;

void* while_stack[STACK_SIZE];
int top = -1;

static expty Expty(Tr_exp tr, Ty_ty ty){
  expty p = checked_malloc(sizeof(*p));
  p->tr = tr;
  p->ty = ty;
  return p;
}

void transError(FILE *out, A_pos pos, string msg) {
  fprintf(out, "(line:%d col:%d) %s\n", pos->line, pos->pos, msg);
  fflush(out);
  exit(1);
}

void while_stack_push(Temp_label test, Temp_label end){
  while_stack[++top] = test;
  while_stack[++top] = end;
}

void while_stack_pop(){
  top -= 2;
}

Temp_label while_stack_get_test_label(){
  return while_stack[top - 1];
}

Temp_label while_stack_get_end_label(){
  return while_stack[top];
}

int while_stack_size(){
  ASSERT((top + 1) % 2 == 0);
  return (top + 1) / 2;
}

/* TODO: semant */
// simple helper functions

static bool abs_ty_eq(Ty_ty l_tp, Ty_ty r_tp){
  if(l_tp->kind != r_tp->kind)return FALSE;
  else if(l_tp->kind == Ty_array)return abs_ty_eq(l_tp->u.array, r_tp->u.array);
  else return l_tp->u.name == r_tp->u.name;
}

static bool ty_eq(Ty_ty l_tp, Ty_ty r_tp){
  // different types and one type is not num
  if (l_tp->kind != r_tp->kind && 
      ((l_tp->kind != Ty_int && l_tp->kind != Ty_float) || 
      (r_tp->kind != Ty_int && r_tp->kind != Ty_float)))
      return FALSE;
  
  // both array type but different elements type
  if (l_tp->kind == Ty_array && r_tp->kind == Ty_array && !abs_ty_eq(l_tp->u.array, r_tp->u.array))
      return FALSE;
  
  // both class type but of different class
  if(l_tp->kind == Ty_name && r_tp->kind == Ty_name && l_tp->u.name != r_tp->u.name){
    bool upcast = FALSE;

    S_symbol iter = r_tp->u.name;
    while(iter != ROOTCLASS){
      E_enventry ce = S_look(CENV, iter);
      iter = ce->u.cls.fa;
      if(iter == l_tp->u.name){
        upcast = TRUE;
        break;
      }
    }

    if(!upcast)return FALSE;
    INFO("%s upcast to %s\n", S_name(r_tp->u.name), S_name(l_tp->u.name));
  }

  return TRUE;
}

static Ty_ty a_type2ty(FILE* out, A_type t){
  Ty_ty tp;
  switch(t->t){
    case A_intType: tp = Ty_Int(); break;
    case A_floatType: tp = Ty_Float(); break;
    case A_intArrType: tp = Ty_Array(Ty_Int()); break;
    case A_floatArrType: tp = Ty_Array(Ty_Float()); break;
    case A_idType: tp = Ty_Name(S_Symbol(t->id)); break;
    default: transError(out, A_Pos(0, 0), "Parsing error, unknown A_type.");
  }
  return tp;
}

static bool same_signature(A_formalList a, A_formalList b){
  while(a && b){
    A_formal f1 = a->head, f2 = b->head;
    if(!f1 || !f2)return FALSE;
    if(f1->t->t != f2->t->t)break;
    if(f1->t->t == A_idType && S_Symbol(f1->t->id) != S_Symbol(f2->t->id))break;
    a = a->tail;
    b = b->tail;
  }
  return !a && !b;
}

typedef enum{
  NORMAL,
  LESS,
  MORE
}call_status;

static call_status check_call_matched(FILE* out, A_expList el, Ty_fieldList fl){
  // return true if matched
  // return false if need more paras
  int has_location;
  A_exp exp;
  while(el && fl){
    Ty_field f = fl->head;
    exp = el->head;
    expty tmp = transA_Exp(out, exp, &has_location);
    Ty_ty tp = tmp->ty;
    if(!ty_eq(f->ty, tp))transError(out, exp->pos, "Incompatible type to call.");
    el = el->tail;
    fl = fl->tail;
  }
  if(el)return MORE;
  if(fl)return LESS;
  return NORMAL;
}

static Ty_fieldList formalist_2_fieldlist(FILE* out, A_formalList fl){
  if(!fl)return NULL;
  Ty_fieldList fel = Ty_FieldList(NULL, NULL);
  Ty_fieldList iter = fel;

  while(fl){
    if(!fl->head)transError(out, A_Pos(0, 0), "Parsing error, invalid syntax tree.");
    iter->tail = Ty_FieldList(Ty_Field(S_Symbol(fl->head->id), a_type2ty(out, fl->head->t)), NULL);
    iter = iter->tail;
    fl = fl->tail;
  }
  return fel->tail;
}

inline static void inherit_offset(E_enventry coff, E_enventry poff){
  unsigned long long before = coff->u.off.local_size;
  _for_in_table(iter, coff->u.off.local_offtbl){
    iter->value += poff->u.off.local_size;
  }

  _for_in_table(iter, poff->u.off.local_offtbl){
    S_enter(coff->u.off.local_offtbl, iter->key, iter->value);
    coff->u.off.local_size += SEM_ARCH_SIZE;
  }
  ASSERT(coff->u.off.local_size == before + poff->u.off.local_size);
}

inline static void inherit_vars(FILE* out, S_table child_vtbl, S_table parent_vtbl){
  // check and inherit varibles from parent class
  // shallow copy
  ASSERT(child_vtbl);
  ASSERT(parent_vtbl);

  _for_in_table(iter, parent_vtbl){
    E_enventry pa_var_entry = iter->value;
    assert(pa_var_entry);
    A_varDecl pa_vd = pa_var_entry->u.var.vd;
    INFO("Try to inherit varible [%s].\n", pa_vd->v);
    E_enventry ven = S_look(child_vtbl, S_Symbol(pa_vd->v));
    if(ven)transError(out, ven->u.var.vd->pos, "Try to override varibles.");
    else S_enter(child_vtbl, S_Symbol(pa_vd->v), S_look(parent_vtbl, S_Symbol(pa_vd->v)));
    INFO("[%s] Inherited.\n", pa_vd->v);
  }
}

inline static void inherit_mtds(FILE* out, S_table child_mtbl, S_table parent_mtbl){
  // check and inherit methods from parent class
  // shallow copy
  ASSERT(child_mtbl);
  ASSERT(parent_mtbl);

  // E_enventry off = S_look(OFFSET_ENV, cur_cls);

  _for_in_table(iter, parent_mtbl){
    E_enventry pa_md_entry = iter->value;
    ASSERT(pa_md_entry);
    A_methodDecl pa_md = pa_md_entry->u.meth.md;
    ASSERT(pa_md);
    INFO("Try to inherit method [%s].\n", pa_md->id);
    E_enventry men = S_look(child_mtbl, S_Symbol(pa_md->id));
    if(men){
      if(!same_signature(men->u.meth.md->fl, pa_md->fl) || !abs_ty_eq(men->u.meth.ret, pa_md_entry->u.meth.ret)){
        transError(out, men->u.meth.md->pos, "Override method conflict.");
      }
    }
    else {
      S_enter(child_mtbl, S_Symbol(pa_md->id), pa_md_entry);
    }
    INFO("[%s] Inherited.\n", pa_md->id);
  }
}


// Detect circle inheritance
// Call helper to check vars and methods
static void check_inheritance(FILE* out, E_enventry startClassEntry){
  INFO("Checking inheritance for %s\n", startClassEntry->u.cls.cd->id);
  ASSERT(startClassEntry);
  ASSERT(startClassEntry->kind == E_classEntry);
  if(startClassEntry->u.cls.fa == ROOTCLASS){
    // add offset for methods
    E_enventry off = S_look(OFFSET_ENV, S_Symbol(startClassEntry->u.cls.cd->id));
    _for_in_table(iter, startClassEntry->u.cls.mtbl){
      E_enventry mtd_entry = iter->value;
      S_enter(off->u.off.local_offtbl, 
              iter->key,
              (void*)off->u.off.local_size);
      off->u.off.local_size += SEM_ARCH_SIZE;
    }

    startClassEntry->u.cls.status = E_transFill;
    return;
  }
  E_enventry parentEnrtry = S_look(CENV, startClassEntry->u.cls.fa);
  if(!parentEnrtry)transError(out, startClassEntry->u.cls.cd->pos, "Parent class not set.");
  if(parentEnrtry->u.cls.status == E_transFind)transError(out, parentEnrtry->u.cls.cd->pos, "Firstly detect circle inheritances.");
  else if(parentEnrtry->u.cls.status == E_transInit){
    startClassEntry->u.cls.status = E_transFind;
    check_inheritance(out, parentEnrtry);
  }
  ASSERT(parentEnrtry->u.cls.status == E_transFill);

  // inherit offset table from parent
  E_enventry off = S_look(OFFSET_ENV, S_Symbol(startClassEntry->u.cls.cd->id));
  inherit_offset(
    off,
    S_look(OFFSET_ENV, S_Symbol(parentEnrtry->u.cls.cd->id))
  );

  if(startClassEntry->u.cls.vtbl){
    INFO("[%s] Inheriting varibles from [%s].\n", startClassEntry->u.cls.cd->id, parentEnrtry->u.cls.cd->id); 
    inherit_vars(out, startClassEntry->u.cls.vtbl, parentEnrtry->u.cls.vtbl);
    INFO("[All inherited].\n");
  }
  if(startClassEntry->u.cls.mtbl){
    INFO("[%s] Inheriting methods from [%s].\n", startClassEntry->u.cls.cd->id, parentEnrtry->u.cls.cd->id); 
    inherit_mtds(out, startClassEntry->u.cls.mtbl, parentEnrtry->u.cls.mtbl);
    INFO("[All inherited].\n");
  }

  // add offset for local methods(that not inherit from parent)
  _for_in_table(iter, startClassEntry->u.cls.mtbl){
    if(!S_look(parentEnrtry->u.cls.mtbl, iter->key)){
      S_enter(off->u.off.local_offtbl, iter->key, (void*)off->u.off.local_size);
      off->u.off.local_size += SEM_ARCH_SIZE;
    }
  }

  startClassEntry->u.cls.status = E_transFill;
}

// Build method environment, with no check
// param[out] menv
static void build_menv(FILE* out, A_classDecl cls, S_table menv){
  A_methodDeclList mtds = cls->mdl;
  while(mtds){
    A_methodDecl md = mtds->head;

    if(md == NULL)transError(out, A_Pos(0, 0), "Invalid syntax tree.");
    E_enventry potential_md_entry = S_look(menv, S_Symbol(md->id));
    // if(potential_md_entry && same_signature(md->fl, potential_md_entry->u.meth.md->fl))transError(out, md->pos, "Method multiple declarations.");
    if(potential_md_entry && S_Symbol(md->id) == S_Symbol(potential_md_entry->u.meth.md->id))
      transError(out, md->pos, "Method multiple declarations.");

    Ty_ty tp = a_type2ty(out, md->t);
    S_enter(menv, S_Symbol(md->id), E_MethodEntry(md, S_Symbol(cls->id), tp, formalist_2_fieldlist(out, md->fl)));

    mtds = mtds->tail;
  }
}

// Build class environment and check all inheritance
static void build_cenv(FILE *out, A_classDeclList cdl){
  A_classDeclList cdl_ = cdl;
  INFO("Building class environment.\n");
  E_enventry entry = NULL;
  while(cdl){
    A_classDecl cd = cdl->head;
    cur_cls = S_Symbol(cd->id);

    // build a offset entry for this class
    S_enter(OFFSET_ENV, cur_cls, E_OffsetEntry(0, S_empty()));

    if(cd == NULL)transError(out, A_Pos(0, 0), "Invalid syntax tree.");
    if(S_look(CENV, S_Symbol(cd->id)))transError(out, cd->pos, "Class multiple declarations.");
    S_table venv = S_empty();
    S_table menv = S_empty();
    transA_VarDecList(out, cd->vdl, venv);

    build_menv(out, cd, menv);
    if(cd->parentID){
      entry = E_ClassEntry(cd, S_Symbol(cd->parentID), E_transInit, venv, menv);
    }
    else entry = E_ClassEntry(cd, ROOTCLASS, E_transInit, venv, menv);
    S_enter(CENV, S_Symbol(cd->id), entry);
    INFO("Built entry for class: %s\n", cd->id);

    cdl = cdl->tail;
  }
  INFO("Built class environment.\n");
  // checking for inheritance and build up private offset table
  cur_cls = cur_mtd = NULL;
  while(cdl_){
    entry = S_look(CENV, S_Symbol(cdl_->head->id));
    if(entry && entry->u.cls.status == E_transInit)check_inheritance(out, entry);
    cdl_ = cdl_->tail;
  }
}

static Temp_temp insert_vtbl(FILE* out, A_varDecl vd, S_table venv){
  Temp_temp ret = NULL;
  switch(vd->t->t){
    case A_intType: {
        INFO("[insert] int\n");
        if(cur_cls && cur_mtd == NULL){
          // for class varibles
          S_enter(venv, S_Symbol(vd->v), E_VarEntry(vd, Ty_Int(), NULL));
          E_enventry off = S_look(OFFSET_ENV, cur_cls);
          S_enter(off->u.off.local_offtbl, S_Symbol(vd->v), (void*)off->u.off.local_size);
          off->u.off.local_size += SEM_ARCH_SIZE;
        }
        else{
          // for method varibles
          ret = Temp_newtemp(T_int);
          S_enter(venv, S_Symbol(vd->v), E_VarEntry(vd, Ty_Int(), ret));
          if(vd->elist)seqBufPush(Tr_intInit(ret, vd->elist->head->u.num));
        }
      } break;
    case A_floatType: {
        INFO("[insert] float\n");
        if(cur_cls && cur_mtd == NULL){
          // for class varibles
          S_enter(venv, S_Symbol(vd->v), E_VarEntry(vd, Ty_Float(), NULL));
          E_enventry off = S_look(OFFSET_ENV, cur_cls);
          S_enter(off->u.off.local_offtbl, S_Symbol(vd->v), (void*)off->u.off.local_size);
          off->u.off.local_size += SEM_ARCH_SIZE;
        }
        else{
          // for method varibles
          ret = Temp_newtemp(T_float);
          S_enter(venv, S_Symbol(vd->v), E_VarEntry(vd, Ty_Float(), ret));
          if(vd->elist)seqBufPush(Tr_floatInit(ret, vd->elist->head->u.num));
        }
        
      }break;
    case A_intArrType: {
        INFO("[insert] intArr\n");
        if(cur_cls && cur_mtd == NULL){
          // for class varibles
          S_enter(venv, S_Symbol(vd->v), E_VarEntry(vd, Ty_Array(Ty_Int()), NULL));
          E_enventry off = S_look(OFFSET_ENV, cur_cls);
          S_enter(off->u.off.local_offtbl, S_Symbol(vd->v), (void*)off->u.off.local_size);
          off->u.off.local_size += SEM_ARCH_SIZE;
        }
        else {
          //for method varibles
          ret = Temp_newtemp(T_int);
          S_enter(venv, S_Symbol(vd->v), E_VarEntry(vd, Ty_Array(Ty_Int()), ret));
          if(vd->elist)seqBufPush(Tr_intArrInit(ret, transA_ExpList(out, vd->elist)));
        }
      }break;
    case A_floatArrType: {
        INFO("[insert] floatArr\n");
        if(cur_cls && cur_mtd == NULL){
          // for class varibles
          S_enter(venv, S_Symbol(vd->v), E_VarEntry(vd, Ty_Array(Ty_Float()), NULL));
          E_enventry off = S_look(OFFSET_ENV, cur_cls);
          S_enter(off->u.off.local_offtbl, S_Symbol(vd->v), (void*)off->u.off.local_size);
          off->u.off.local_size += SEM_ARCH_SIZE;
        }
        else {
          //for method varibles
          ret = Temp_newtemp(T_float);
          S_enter(venv, S_Symbol(vd->v), E_VarEntry(vd, Ty_Array(Ty_Float()), ret));
          if(vd->elist)seqBufPush(Tr_floatArrInit(ret, transA_ExpList(out, vd->elist)));
        }
      }break;
    case A_idType: {
        INFO("[insert] idType\n");
        if(cur_cls && cur_mtd == NULL){
          // for class varibles
          S_enter(venv, S_Symbol(vd->v), E_VarEntry(vd, Ty_Name(S_Symbol(vd->t->id)), NULL));
          E_enventry off = S_look(OFFSET_ENV, cur_cls);
          S_enter(off->u.off.local_offtbl, S_Symbol(vd->v), (void*)off->u.off.local_size);
          off->u.off.local_size += SEM_ARCH_SIZE;
        }
        else {
          // for method varibles
          S_enter(venv, S_Symbol(vd->v), E_VarEntry(vd, Ty_Name(S_Symbol(vd->t->id)), (ret = Temp_newtemp(T_int))));
        }
      }break;
    default: transError(out, vd->pos, "Detect a type that not supported.");
  }
  return ret;
}

// add varibles in the formalList for a method
static Temp_tempList venv_append_formallist(FILE* out, S_table venv, A_formalList fl){
  Temp_tempList head = Temp_TempList(this(), NULL);
  Temp_tempList it = head;
  while(fl){
    A_formal fd = fl->head;
    ASSERT(fd);
    if(S_look(venv, S_Symbol(fd->id)))transError(out, fd->pos, "Redeclared method formal variable.");
    A_varDecl tmp = A_VarDecl(fd->pos, fd->t, fd->id, NULL);
    Temp_temp t = insert_vtbl(out, tmp, venv);
    ASSERT(t);
    it->tail = Temp_TempList(t, NULL);
    it = it->tail;
    fl = fl->tail;
  }
  return head;
}

static Tr_exp transA_VarDecList(FILE *out, A_varDeclList vars, S_table venv){
  INFO("[VarDecList]\n");
  unsigned count = 0;
  while(vars){
    A_varDecl vd = vars->head;
    if(vd == NULL || vd->t == NULL)transError(out, A_Pos(0, 0), "Invalid syntax tree.");
    if(S_look(venv, S_Symbol(vd->v)))transError(out, vd->pos, "Varible multiple declarations.");
    // check for method varibles
    if(cur_mtd && vd->t->t == A_idType && !S_look(CENV, S_Symbol(vd->t->id)))transError(out, vd->pos, "Class undeclared.");

    insert_vtbl(out, vd, venv);
    vars = vars->tail;
  }
  INFO("[VarDecList] Over\n");
  // building for class varibles
  if(cur_cls && cur_mtd == NULL)return NULL;
  
  // building for method varibles
  Tr_exp ret = SequenceFromBuffer();
  seqBufClear();
  return ret;

}

static Tr_expList transA_ExpList(FILE* out, A_expList exps){
  Tr_expList ret = NULL;
  Tr_expList it = NULL;
  int has_location;
  expty tmp = NULL;
  while(exps){
    A_exp e = exps->head;
    if(!ret){
      tmp = transA_Exp(out, e, &has_location);
      it = ret = Tr_ExpList(tmp->tr, NULL);
    }
    else{
      tmp = transA_Exp(out, e, &has_location);
      it->tail = Tr_ExpList(tmp->tr, NULL);
      it = it->tail;
    }
    exps = exps->tail;
  }
  return ret;
}

static expty transA_Exp(FILE *out, A_exp exp, int* has_location){
  if(exp == NULL)transError(out, A_Pos(0, 0), "Invalid syntax tree.");
  switch(exp->kind){
    case A_opExp: {
      INFO("[Exp] opExp\n");
      expty left = transA_Exp(out, exp->u.op.left, has_location);
      Ty_ty l_tp = left->ty;
      if(l_tp->kind != Ty_int && l_tp->kind != Ty_float)transError(out, exp->pos, "Binary operations should only be implemented on type int/float.");
      expty right = transA_Exp(out, exp->u.op.right, has_location);
      Ty_ty r_tp = right->ty;
      if(r_tp->kind != Ty_int && r_tp->kind != Ty_float)transError(out, exp->pos, "Binary operations should only be implemented on type int/float.");
      
      *has_location = 0;
      // if(l_tp->kind == Ty_float)return l_tp;
      // else return r_tp;
      Tr_exp tr = Tr_OpExp(exp->u.op.oper, left->tr, right->tr);
      if(l_tp->kind == Ty_float)return Expty(tr, l_tp);
      else return Expty(tr, r_tp);
    }
    case A_arrayExp: {
      INFO("[Exp] arrayExp\n");
      expty arr_ret = transA_Exp(out, exp->u.array_pos.arr, has_location);
      Ty_ty tp = arr_ret->ty;
      if(tp->kind != Ty_array)transError(out, exp->pos, "Indexing on a non-array varible.");
      // if(*has_location == 0)transError(out, exp->pos, "Indexing on an array with no location.");
      expty pos_ret = transA_Exp(out, exp->u.array_pos.arr_pos, has_location);
      tp = pos_ret->ty;
      if(tp->kind != Ty_int && tp->kind != Ty_float)transError(out, exp->pos, "Index should have type of int/float.");

      *has_location = 1;
      if(arr_ret->ty->u.array->kind == Ty_int)
        return Expty(Tr_ArrayExp(arr_ret->tr, pos_ret->tr, T_int), arr_ret->ty->u.array);
      return Expty(Tr_ArrayExp(arr_ret->tr, pos_ret->tr, T_float), arr_ret->ty->u.array);
    }
    case A_callExp: {
      INFO("[Exp] callExp\n");
      expty tp = transA_Exp(out, exp->u.call.obj, has_location);
      Ty_ty exp_tp = tp->ty;
      if(exp_tp->kind != Ty_name)transError(out, exp->pos, "Try to call function from non-class type.");
      E_enventry ce = S_look(CENV, exp_tp->u.name);
      ASSERT(ce);
      E_enventry me = S_look(ce->u.cls.mtbl, S_Symbol(exp->u.call.fun));
      if(!me)transError(out, exp->pos, "Method undeclared.");
      call_status status = check_call_matched(out, exp->u.call.el, me->u.meth.fl);
      if(status == LESS)transError(out, exp->pos, "Need more parameters to call.");
      if(status == MORE)transError(out, exp->pos, "Too many varibles to call.");

      // translation
      T_type mtd_ret_ty = T_int;
      if(me->u.meth.md->t->t == A_floatType)mtd_ret_ty = T_float;
      Tr_exp thiz = locate_obj_temp(&tp->tr);
      INFO("[callExp] retrived obj temp %p\n", thiz);

      *has_location = 0;

      E_enventry off_en = S_look(OFFSET_ENV, exp_tp->u.name);

      return Expty(
        Tr_CallExp(me->u.meth.md->id, tp->tr, thiz, transA_ExpList(out, exp->u.call.el), mtd_ret_ty,
                  (unsigned long long)S_look(off_en->u.off.local_offtbl, S_Symbol(exp->u.call.fun))),
        me->u.meth.ret
      );
    }
    case A_classVarExp: {
      INFO("[Exp] classVarExp\n");
      expty ret = transA_Exp(out, exp->u.classvar.obj, has_location);
      Ty_ty tp = ret->ty;
      if(tp->kind != Ty_name)transError(out, exp->pos, "Try to reference varible from non-class type.");
      E_enventry ce = S_look(CENV, tp->u.name);
      E_enventry ve = S_look(ce->u.cls.vtbl, S_Symbol(exp->u.classvar.var));
      if(!ve)transError(out, exp->pos, "Class varible not declared.");
      *has_location = 1;

      // translation
      E_enventry off_en = S_look(OFFSET_ENV, tp->u.name);
      unsigned long long offset = (unsigned long long)S_look(off_en->u.off.local_offtbl, S_Symbol(exp->u.classvar.var));
      T_type type = T_int;
      if(ve->u.var.ty->kind == Ty_float)type = T_float;
      return Expty(
        Tr_ClassVarExp(ret->tr, offset, type),
        ve->u.var.ty
      );
    }
    case A_boolConst: {
      INFO("[Exp] boolConst\n");
      *has_location = 0;
      return Expty(Tr_BoolConst(exp->u.b), Ty_Int());
    }
    case A_numConst: {
      INFO("[Exp] numConst\n");
      *has_location = 0;
      // if(exp->u.num == (int)exp->u.num)return Ty_Int();
      // else return Ty_Float();
      if(exp->u.num == (int)exp->u.num)return Expty(Tr_NumConst(exp->u.num, T_int), Ty_Int());
      return Expty(Tr_NumConst(exp->u.num, T_float), Ty_Float());
    }
    case A_idExp: {
      INFO("[Exp] idExp\n");
      E_enventry entry = S_look(VENV, S_Symbol(exp->u.v));
      if(!entry)transError(out, exp->pos, "Varible not defined.");
      *has_location = 1;
      return Expty(Tr_IdExp(entry->u.var.tmp), entry->u.var.ty);
    }
    case A_thisExp: {
      INFO("[Exp] thisExp\n");
      if(!cur_cls)transError(out, exp->pos, "Keyword this can not occur in main method.");
      *has_location = 0;
      return Expty(
        Tr_ThisExp(this()),
        Ty_Name(cur_cls)
      );
    }
    case A_lengthExp: {
      INFO("[Exp] lengthExp\n");
      expty ret = transA_Exp(out, exp->u.e, has_location);
      Ty_ty tp = ret->ty;
      if(tp->kind != Ty_array)transError(out, exp->pos, "Try to get length of a non-array type.");
      *has_location = 0;
      return Expty(Tr_LengthExp(ret->tr), Ty_Int());
    }
    case A_newIntArrExp: {
      INFO("[Exp] newIntArrExp\n");
      expty ret = transA_Exp(out, exp->u.e, has_location);
      Ty_ty tp = ret->ty;
      if(tp->kind != Ty_int && tp->kind != Ty_float)transError(out, exp->pos, "Array size should be type of int/float.");
      *has_location = 0;
      return Expty(Tr_NewArrExp(ret->tr), Ty_Array(Ty_Int()));
    }
    case A_newFloatArrExp: {
      INFO("[Exp] newFloatArrExp\n");
      expty ret = transA_Exp(out, exp->u.e, has_location);
      Ty_ty tp = ret->ty;
      if(tp->kind != Ty_int && tp->kind != Ty_float)transError(out, exp->pos, "Array size should be type of int/float.");
      *has_location = 0;
      return Expty(Tr_NewArrExp(ret->tr), Ty_Array(Ty_Float()));
    }
    case A_newObjExp: {
      INFO("[Exp] newObjExp\n");
      E_enventry ce = S_look(CENV, S_Symbol(exp->u.v));
      if(!ce)transError(out, exp->pos, "Class not declared.");
      *has_location = 0;

      E_enventry off_en = S_look(OFFSET_ENV, S_Symbol(exp->u.v));
      return Expty(
        Tr_NewObjExp(S_Symbol(exp->u.v), off_en, ce),
        Ty_Name(S_Symbol(exp->u.v))
      );
    }
    case A_notExp: {
      INFO("[Exp] notExp\n");
      expty ret = transA_Exp(out, exp->u.e, has_location);
      Ty_ty tp = ret->ty;
      if(tp->kind != Ty_int && tp->kind != Ty_float)transError(out, exp->pos, "\'!\' should operate on type of int/float.");
      *has_location = 0;
      return Expty(Tr_NotExp(ret->tr), Ty_Int());
    }
    case A_minusExp: {
      INFO("[Exp] minusExp\n");
      expty ret = transA_Exp(out, exp->u.e, has_location);
      Ty_ty tp = ret->ty;
      if(tp->kind != Ty_int && tp->kind != Ty_float)transError(out, exp->pos, "Unary minus should operate on type of int/float.");
      *has_location = 0;
      return Expty(Tr_MinusExp(ret->tr), ret->ty);
    }
    case A_escExp: {
      INFO("[Exp] escExp\n");
      Tr_exp stm = transA_StmList(out, exp->u.escExp.ns);
      expty ret = transA_Exp(out, exp->u.escExp.exp, has_location);
      return Expty(Tr_EscExp(stm, ret->tr), ret->ty);
    }
    case A_getnum: {
      INFO("[Exp] getnum\n");
      *has_location = 0;
      return Expty(Tr_Getfloat(), Ty_Float());
    }
    case A_getch: {
      INFO("[Exp] getch\n");
      *has_location = 0;
      // return Ty_Int();
      return Expty(Tr_Getch(), Ty_Int());
    }
    case A_getarray: {
      INFO("[Exp] getarray\n");
      expty ret = transA_Exp(out, exp->u.e, has_location);
      Ty_ty tp = ret->ty;
      if(tp->kind != Ty_array)transError(out, exp->pos, "Can not getarray on non-array type.");
      *has_location = 0;
      // return Ty_Int();
      if(tp->u.array->kind == Ty_int)return Expty(Tr_Getarray(ret->tr), Ty_Int());
      return Expty(Tr_Getfarray(ret->tr), Ty_Int());
    }
    default: transError(out, exp->pos, "Invalid or unsupported exp type.");
  }
}

static Tr_expList transA_ConstList(FILE *out, A_expList exps){
  INFO("[transA_ConstList]\n");
  if(exps == NULL)return NULL;
  int has_location;
  expty ret = transA_Exp(out, exps->head, &has_location);
  Ty_ty tp = ret->ty;
  if(tp->kind != Ty_int && tp->kind != Ty_float){
    transError(out, exps->head->pos, "Array initialization with incompatible types.");
  }
  return Tr_ExpList(ret->tr, transA_ConstList(out, exps->tail));
}

static Tr_exp transA_Stm(FILE* out, A_stm stm){
  if(stm == NULL)return NULL;
  int has_location = 0;
  switch(stm->kind){
    case A_nestedStm: {
      INFO("[Stm] nestedStm\n");
      return transA_StmList(out, stm->u.ns);
    } 
    case A_ifStm: {
        INFO("[Stm] ifStm\n");
        expty ret = transA_Exp(out, stm->u.if_stat.e, &has_location);
        Ty_ty tp = ret->ty;
        if(tp->kind != Ty_int && tp->kind != Ty_float)transError(out, stm->pos, "Expected int or float in condition.");
        return Tr_IfStm(ret->tr, transA_Stm(out, stm->u.if_stat.s1), transA_Stm(out, stm->u.if_stat.s2));
    }
    case A_whileStm: {
        INFO("[Stm] whileStm\n");
        expty ret = transA_Exp(out, stm->u.while_stat.e, &has_location);
        Ty_ty tp = ret->ty;
        if(tp->kind != Ty_int && tp->kind != Ty_float)transError(out, stm->pos, "Expected int or float in condition.");

        Temp_label test = Temp_newlabel();
        Temp_label end = Temp_newlabel();
        while_stack_push(test, end);
        Tr_exp loop = transA_Stm(out, stm->u.while_stat.s);
        while_stack_pop();
        
        return Tr_WhileStm(ret->tr, loop, test, end);
    }
    case A_assignStm: {
      INFO("[Stm] assignStm\n");
      expty left = transA_Exp(out, stm->u.assign.arr, &has_location);
      Ty_ty l_tp = left->ty;
      if(has_location == 0)transError(out, stm->pos, "Left exp of assignment has no location.");

      expty right = transA_Exp(out, stm->u.assign.value, &has_location);
      Ty_ty r_tp = right->ty;
      if (l_tp->kind != r_tp->kind && 
          ((l_tp->kind != Ty_int && l_tp->kind != Ty_float) || 
          (r_tp->kind != Ty_int && r_tp->kind != Ty_float)))
          transError(out, stm->pos, "Assignment between incompatible types.");
      else if (l_tp->kind == Ty_array && r_tp->kind == Ty_array && l_tp->u.array != r_tp->u.array)
          transError(out, stm->pos, "Attempt to convert between arrays.");
      return Tr_AssignStm(left->tr, right->tr);
    }
    case A_arrayInit: {
      INFO("[Stm] arrayInit\n");
      expty ret = transA_Exp(out, stm->u.array_init.arr, &has_location);
      Ty_ty l_tp = ret->ty;
      if(l_tp->kind != Ty_array)transError(out, stm->pos, "Left expression should be an array.");
      if(has_location == 0)transError(out, stm->pos, "Left exp of arrayInit has no location.");
      
      T_type type = T_int;
      if(l_tp->u.array->kind == Ty_float)type = T_float;
      return Tr_ArrayInit(ret->tr, transA_ExpList(out, stm->u.array_init.init_values), type);
    }
    case A_callStm: {
      INFO("[stm] call\n");
      expty tp = transA_Exp(out, stm->u.call_stat.obj, &has_location);
      Ty_ty exp_tp = tp->ty;
      if(exp_tp->kind != Ty_name)transError(out, stm->pos, "Try to call function from non-class type.");

      // checks
      E_enventry ce = S_look(CENV, exp_tp->u.name);
      ASSERT(ce);
      E_enventry me = S_look(ce->u.cls.mtbl, S_Symbol(stm->u.call_stat.fun));
      if(!me)transError(out, stm->pos, "Method undeclared.");
      call_status status = check_call_matched(out, stm->u.call_stat.el, me->u.meth.fl);
      if(status == LESS)transError(out, stm->pos, "Need more parameters to call.");
      if(status == MORE)transError(out, stm->pos, "Too many varibles to call.");

      // translation
      T_type mtd_ret_ty = T_int;
      if(me->u.meth.md->t->t == A_floatType)mtd_ret_ty = T_float;

      Tr_exp thiz = locate_obj_temp(&tp->tr);
      E_enventry off_en = S_look(OFFSET_ENV, exp_tp->u.name);
      return Tr_CallStm(me->u.meth.md->id, tp->tr, thiz, 
                        transA_ExpList(out, stm->u.call_stat.el), mtd_ret_ty, 
                        (unsigned long long)S_look(off_en->u.off.local_offtbl, S_Symbol(stm->u.call_stat.fun)));
    }
    case A_continue: {
      INFO("[Stm] continue\n");
      if(!while_stack_size())transError(out, stm->pos, "Keyword continue must be inside while.");
      return Tr_Continue(while_stack_get_test_label());
    }
    case A_break: {
      INFO("[Stm] break\n");
      if(!while_stack_size())transError(out, stm->pos, "Keyword break must be inside while.");
      return Tr_Break(while_stack_get_end_label());
    }
    case A_return: {
      INFO("[Stm] return\n");
      expty ret = transA_Exp(out, stm->u.e, &has_location);
      Ty_ty tp = ret->ty;
      if(!cur_cls && tp->kind != Ty_int && tp->kind != Ty_float)transError(out, stm->pos, "Return type of main method should be int/float.");
      if(cur_cls){
        E_enventry ce = S_look(CENV, cur_cls);
        E_enventry me = S_look(ce->u.cls.mtbl, cur_mtd);
        if(!ty_eq(me->u.meth.ret, tp))transError(out, stm->pos, "Incompatible return type.");
      }
      T_type type = T_int;
      if(cur_cls){
        // translating class method
        ASSERT(cur_mtd);
        E_enventry ce = S_look(CENV, cur_cls);
        E_enventry me = S_look(ce->u.cls.mtbl, cur_mtd);
        if(me->u.meth.ret->kind == T_float)type = T_float;
      }
      return Tr_Return(ret->tr, type);
    }
    case A_putnum: 
    case A_putch: {
      INFO("[Stm] putnum/putch\n");
      expty ret = transA_Exp(out, stm->u.e, &has_location);
      Ty_ty tp = ret->ty;
      if(tp->kind != Ty_int && tp->kind != Ty_float)transError(out, stm->pos, "Expression in a putnum/putch statement should be type int/float.");

      Tr_exp ret_exp = NULL;
      if(stm->kind == A_putch){
        ret_exp = Tr_Putch(ret->tr);
      }
      else if(tp->kind == Ty_int)ret_exp = Tr_Putint(ret->tr);
      else ret_exp = Tr_Putfloat(ret->tr);

      return ret_exp;
    }
    case A_putarray: {
      INFO("[Stm] putarray\n");
      expty length_ret = transA_Exp(out, stm->u.putarray.e1, &has_location);
      Ty_ty tp = length_ret->ty;
      if(tp->kind != Ty_int && tp->kind != Ty_float)transError(out, stm->pos, "Expression 1 in a putarray statement should be type int/float.");
      expty arr_ret = transA_Exp(out, stm->u.putarray.e2, &has_location);
      tp = arr_ret->ty;
      if(tp->kind != Ty_array)transError(out, stm->pos, "Expression 2 in a putarray statement should be array type.");

      return Tr_Putarray(length_ret->tr, arr_ret->tr);
    }
    case A_starttime: {
      return Tr_Starttime();
    }
    case A_stoptime: {
      return Tr_Stoptime();
    }
    default: transError(out, stm->pos, "Detect a statement type that not supported.");
  }
  ASSERT(0);
}

static Tr_exp transA_StmList(FILE* out, A_stmList sl){
  INFO("[StmList]\n");
  if(sl == NULL)return NULL;
  if(sl->tail == NULL)return transA_Stm(out, sl->head);
  Tr_exp stm = transA_Stm(out, sl->head);
  if(sl->tail->tail){
    // more than two stms
    Tr_exp rest = transA_StmList(out, sl->tail);
    return Tr_StmList(stm, rest);
  }
  // only two stms
  Tr_exp last = transA_Stm(out, sl->tail->head);
  return Tr_StmList(stm, last);
}

static T_funcDecl transA_MainMethod(FILE* out, A_mainMethod main){
  if(main == NULL)return NULL;
  Temp_resettemp();
  INFO("[MainMethod]\n");
  Tr_exp vdl = transA_VarDecList(out, main->vdl, VENV);
  INFO("[MainMethod] VarDecList translated\n");
  Tr_exp sl = transA_StmList(out, main->sl);
  INFO("[MainMethod] StmList translated\n");
  return Tr_MainMethod(vdl, sl);
}

inline static void init_preprocess(FILE* out, A_prog p){
  CENV = S_empty();
  VENV = S_empty();
  OFFSET_ENV = S_empty();
  CLASS_INIT_ENV = S_empty();

  ROOTCLASS = S_Symbol("0713_ROOT");
  cur_cls = NULL;
  cur_mtd = NULL;
}

static T_funcDecl transA_ClassMethod(FILE* out, A_methodDecl mtd){
  ASSERT(mtd);
  S_beginScope(VENV);
  Temp_resettemp();
  Temp_tempList parameters = venv_append_formallist(out, VENV, mtd->fl);
  Tr_exp vals = transA_VarDecList(out, mtd->vdl, VENV);
  Tr_exp stms = transA_StmList(out, mtd->sl);
  S_endScope(VENV);
  return Tr_ClassMethod(
    S_name(S_link(cur_cls, S_Symbol(mtd->id))),
    parameters,
    vals,
    stms
  );
}

static T_funcDeclList transA_Classes(FILE* out, A_classDeclList cdl){
  if(!cdl)return NULL;
  // build class environment
  build_cenv(out, cdl);

  T_funcDeclList ret = NULL;
  T_funcDeclList it = NULL;
  _for_in_table(iter, CENV){
    E_enventry cls = iter->value;
    cur_cls = iter->key;
    // check class varibles of type Ty_name
    _for_in_table(var, cls->u.cls.vtbl){
      E_enventry ve = var->value;
      if(ve->u.var.ty->kind == Ty_name && !S_look(CENV, S_Symbol(ve->u.var.vd->t->id))){
        // record a class member before but the class undeclared
        transError(out, ve->u.var.vd->pos, "Undeclared class.");
      }
    }
    // check methods
    _for_in_table(mtds, cls->u.cls.mtbl){
      E_enventry me = mtds->value;
      cur_mtd = mtds->key;
      ASSERT(cur_mtd == S_Symbol(me->u.meth.md->id));
      INFO("Translating method %s of %s\n", me->u.meth.md->id, S_name(cur_cls));
      T_funcDecl cls_mtd = transA_ClassMethod(out, me->u.meth.md);
      if(ret == NULL)it = ret = Tr_FuncDeclList(cls_mtd, NULL);
      else it->tail = Tr_FuncDeclList(cls_mtd, NULL), it = it->tail;
    }
  }
  return ret;
}

T_funcDeclList transA_Prog(FILE *out, A_prog p, int arch_size) {
  // transError(out, A_Pos(0,0), "TODO: translate during semant! See Tiger Book for designing details:)");
  SEM_ARCH_SIZE = arch_size;
  init_preprocess(out, p);
  T_funcDeclList cls = transA_Classes(out, p->cdl);
  INFO("[Prog] classes translated: %p\n", cls);
  cur_cls = NULL;
  cur_mtd = S_Symbol("0713Mainmethod");
  T_funcDecl main = transA_MainMethod(out, p->m);
  INFO("[Prog] main method translated: %p\n", main);
  if(main == NULL)transError(out, p->pos, "Main method not found.");
  return Tr_FuncDeclList(main, cls);
}