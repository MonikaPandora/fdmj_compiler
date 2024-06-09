#ifndef SEMANT_H
#define SEMANT_H

#include <stdio.h>
#include <stdlib.h>
#include "env.h"
#include "fdmjast.h"
#include "translate.h"
#include "tigerirp.h"
#include "util.h"

struct expty_{
  Tr_exp tr;
  Ty_ty ty;
};

typedef struct expty_* expty;

T_funcDeclList transA_Prog(FILE *out, A_prog p, int arch_size);

static T_funcDecl transA_MainMethod(FILE* out, A_mainMethod main);

static T_funcDeclList transA_Classes(FILE* out, A_classDeclList cdl);

static T_funcDecl transA_ClassMethod(FILE* out, A_methodDecl md);

static Tr_exp transA_StmList(FILE* out, A_stmList sl);

static Tr_exp transA_Stm(FILE* out, A_stm stm);

static Tr_exp transA_VarDecList(FILE *out, A_varDeclList vars, S_table venv);

static expty transA_Exp(FILE *out, A_exp exp, int* has_location);

static Tr_expList transA_ExpList(FILE* out, A_expList exps);

#endif