/* 1. declarations */

/* included code */
%{

#include <stdio.h>
#include "fdmjast.h"

extern int yylex(); 
void yyerror(char*);
void myerror(char*);
int  yywrap();

extern void add_char();

void check_semi(char check, A_pos pos);
void check_parentheses(char check, A_pos pos);

extern A_prog root;

%}

/* yylval */
%union {
  A_pos pos;
  A_type type;
  A_prog prog;
  A_mainMethod mainMethod;
  A_varDeclList varDeclList;
  A_varDecl varDecl;
  A_stmList stmList;
  A_stm stm;
  A_expList expList;
  A_exp exp;
  A_classDeclList classDeclList;
  A_classDecl classDecl;
  A_methodDeclList methodDeclList;
  A_methodDecl methodDecl;
  A_formalList formalList;
  A_formal formal;
  char check;
}

/* termianl symbols */
%token<pos> PUBLIC INT MAIN FLOAT CLASS NEW IF ELSE WHILE CONTINUE BREAK THIS EXTENDS RETURN
%token<pos> PUTNUM PUTCH PUTARRAY STARTTIME STOPTIME LENGTH GETNUM GETCH GETARRAY
%token<pos> ADD MINUS TIMES DIV OR AND LE LESS GE GREATER EQ NEQ NOT
%token<pos> '(' ')' '[' ']' '{' '}' '=' ',' ';' '.'
%token<exp> ID NUM BOOLTRUE BOOLFALSE

/* non-termianl symbols */
%type<prog> PROG
%type<mainMethod> MAINMETHOD
%type<type> TYPE
%type<varDeclList> VARDECLLIST
%type<varDecl> VARDECL
%type<stmList> STMLIST
%type<stm> STM
%type<expList> EXPLIST
%type<expList> EXPREST
%type<exp> EXP
%type<classDeclList> CLASSDECLLIST
%type<classDecl> CLASSDECL
%type<methodDeclList> METHODDECLLIST
%type<methodDecl> METHODDECL
%type<formalList> FORMALLIST
%type<formalList> FORMALREST
%type<expList> CONSTLIST
%type<expList> CONSTREST
%type<exp> CONST

%type<check> CHECK_SEMI
%type<check> CHECK_PARENT

/* start symbol */
%start PROG

/* precedence */
%left OR 
%left AND
%left EQ NEQ
%left LESS LE GREATER GE
%left ADD MINUS
%left TIMES DIV
%right UMINUS NOT
%left '.' '[' ']' '(' ')'
%left LOWER_THAN_ELSE
%left ELSE

%% /* 2. rules */
PROG: MAINMETHOD CLASSDECLLIST {
  root = A_Prog(A_Pos($1->pos->line, $1->pos->pos), $1, $2);
  $$ = root;
} ;

MAINMETHOD: PUBLIC INT MAIN CHECK_PARENT '{' VARDECLLIST STMLIST '}' {
  check_parentheses($4, $1);
  yyerrok;
  $$ = A_MainMethod($1, $6, $7);
} ;

VARDECLLIST: /* empty */{
  $$ = NULL;
} | VARDECL VARDECLLIST {
  $$ = A_VarDeclList($1, $2);
} ;

CHECK_SEMI : ';' {
  $$ = 0;
} | error '}' {
  add_char('}');
  $$ = 1;
} | error ';' {
  $$ = 1;
} ;

VARDECL: CLASS ID ID CHECK_SEMI {
  check_semi($4, $3->pos);
  yyerrok;
  $$ = A_VarDecl($1, A_Type($1, A_idType, String($2->u.v)), String($3->u.v), NULL);
} | INT ID CHECK_SEMI {
  check_semi($3, $2->pos);
  yyerrok;
  $$ = A_VarDecl($1, A_Type($1, A_intType, NULL), String($2->u.v), NULL);
} | INT ID '=' CONST CHECK_SEMI {
  check_semi($5, $4->pos);
  yyerrok;
  $$ = A_VarDecl($1, A_Type($1, A_intType, NULL), String($2->u.v), A_ExpList($4, NULL));
} | INT '[' ']' ID CHECK_SEMI {
  check_semi($5, $4->pos);
  yyerrok;
  $$ = A_VarDecl($1, A_Type($1, A_intArrType, NULL), String($4->u.v), NULL);
} | INT '[' ']' ID '=' '{' CONSTLIST '}' CHECK_SEMI {
  check_semi($9, $8);
  yyerrok;
  $$ = A_VarDecl($1, A_Type($1, A_intArrType, NULL), String($4->u.v), $7);
} | FLOAT '[' ']' ID CHECK_SEMI {
  check_semi($5, $4->pos);
  yyerrok;
  $$ = A_VarDecl($1, A_Type($1, A_floatArrType, NULL), String($4->u.v), NULL);
} | FLOAT '[' ']' ID '=' '{' CONSTLIST '}' CHECK_SEMI {
  check_semi($9, $8);
  yyerrok;
  $$ = A_VarDecl($1, A_Type($1, A_floatArrType, NULL), String($4->u.v), $7);
} | FLOAT ID CHECK_SEMI {
  check_semi($3, $2->pos);
  yyerrok;
  $$ = A_VarDecl($1, A_Type($1, A_floatType, NULL), String($2->u.v), NULL);
} | FLOAT ID '=' CONST CHECK_SEMI {
  check_semi($5, $4->pos);
  yyerrok;
  $$ = A_VarDecl($1, A_Type($1, A_floatType, NULL), String($2->u.v), A_ExpList($4, NULL));
} ;

CONST : NUM {
  $$ = $1;
} | MINUS NUM %prec UMINUS {
  $2->u.num = -$2->u.num;
  $2->pos->pos = $1->pos;
  $2->pos->line = $1->line;
  $$ = $2;
} ;

CONSTLIST : /* empty */ {
  $$ = NULL;
} | CONST CONSTREST {
  $$ = A_ExpList($1, $2);
} ;

CONSTREST : /* empty */ {
  $$ = NULL;
} | ',' CONST CONSTREST {
  $$ = A_ExpList($2, $3);
} ;

STMLIST : /* empty */ {
  $$ = NULL;
} | STM STMLIST {
  $$ = A_StmList($1, $2);
} ;

STM : '{' STMLIST '}' {
  $$ = A_NestedStm(A_Pos($1->line, $1->pos), $2);
} | IF '(' EXP ')' STM ELSE STM {
  $$ = A_IfStm(A_Pos($1->line, $1->pos), $3, $5, $7);
} | IF '(' EXP ')' STM %prec LOWER_THAN_ELSE {
  $$ = A_IfStm(A_Pos($1->line, $1->pos), $3, $5, NULL);
} | WHILE '(' EXP ')' STM {
  $$ = A_WhileStm(A_Pos($1->line, $1->pos), $3, $5);
} | WHILE '(' EXP ')' CHECK_SEMI {
  check_semi($5, $4);
  yyerrok;
  $$ = A_WhileStm(A_Pos($1->line, $1->pos), $3, NULL);
} | EXP '=' EXP CHECK_SEMI {
  check_semi($4, $3->pos);
  yyerrok;
  $$ = A_AssignStm(A_Pos($1->pos->line, $1->pos->pos), $1, $3);
} | EXP '[' ']' '=' '{' EXPLIST '}' CHECK_SEMI{
  check_semi($8, $7);
  yyerrok;
  $$ = A_ArrayInit(A_Pos($1->pos->line, $1->pos->pos), $1, $6);
} | EXP '.' ID '(' EXPLIST ')' CHECK_SEMI {
  check_semi($7, $6);
  yyerrok;
  $$ = A_CallStm(A_Pos($1->pos->line, $1->pos->pos), $1, String($3->u.v), $5);
} | CONTINUE CHECK_SEMI {
  check_semi($2, $1);
  yyerrok;
  $$ = A_Continue(A_Pos($1->line, $1->pos));
} | BREAK CHECK_SEMI {
  check_semi($2, $1);
  yyerrok;
  $$ = A_Break(A_Pos($1->line, $1->pos));
} | RETURN EXP CHECK_SEMI {
  check_semi($3, $1);
  yyerrok;
  $$ = A_Return(A_Pos($1->line, $1->pos), $2);
} | PUTNUM '(' EXP ')' CHECK_SEMI {
  check_semi($5, $4);
  yyerrok;
  $$ = A_Putnum($1, $3);
} | PUTCH '(' EXP ')' CHECK_SEMI {
  check_semi($5, $4);
  yyerrok;
  $$ = A_Putch($1, $3);
} | PUTARRAY '(' EXP ',' EXP ')' CHECK_SEMI {
  check_semi($7, $6);
  yyerrok;
  $$ = A_Putarray($1, $3, $5);
} | STARTTIME CHECK_PARENT CHECK_SEMI {
  check_parentheses($2, $1);
  check_semi($3, $1);
  yyerrok;
  $$ = A_Starttime($1);
} | STOPTIME CHECK_PARENT CHECK_SEMI {
  check_parentheses($2, $1);
  check_semi($3, $1);
  yyerrok;
  $$ = A_Stoptime($1);
} ;

CHECK_PARENT : '(' ')' {
  $$ = 0;
} | error ';' {
  $$ = 1;
  add_char(';');
} | error '{' {
  $$ = 1;
  add_char('{');
};

EXP : NUM {
  $$ = $1;
} | BOOLTRUE {
  $$ = $1;
} | BOOLFALSE {
  $$ = $1;
} | LENGTH '(' EXP ')' {
  $$ = A_LengthExp($1, $3);
} | GETNUM CHECK_PARENT {
  check_parentheses($2, $1);
  yyerrok;
  $$ = A_Getnum($1);
} | GETCH CHECK_PARENT {
  check_parentheses($2, $1);
  yyerrok;
  $$ = A_Getch($1);
} | GETARRAY '(' EXP ')' {
  $$ = A_Getarray($1, $3);
} | ID {
  $$ = $1;
} | THIS {
  $$ = A_ThisExp($1);
} | NEW INT '[' EXP ']' {
  $$ = A_NewIntArrExp($1, $4);
} | NEW FLOAT '[' EXP ']' {
  $$ = A_NewFloatArrExp($1, $4);
} | NEW ID CHECK_PARENT {
  check_parentheses($3, $1);
  yyerrok;
  $$ = A_NewObjExp($1, String($2->u.v));
} | EXP ADD EXP {
  $$ = A_OpExp(A_Pos($1->pos->line, $1->pos->pos), $1, A_plus, $3);
} | EXP MINUS EXP {
  $$ = A_OpExp(A_Pos($1->pos->line, $1->pos->pos), $1, A_minus, $3);
} | EXP TIMES EXP {
  $$ = A_OpExp(A_Pos($1->pos->line, $1->pos->pos), $1, A_times, $3);
} | EXP DIV EXP {
  $$ = A_OpExp(A_Pos($1->pos->line, $1->pos->pos), $1, A_div, $3);
} | EXP OR EXP {
  $$ = A_OpExp(A_Pos($1->pos->line, $1->pos->pos), $1, A_or, $3);
} | EXP AND EXP {
  $$ = A_OpExp(A_Pos($1->pos->line, $1->pos->pos), $1, A_and, $3);
} | EXP LESS EXP {
  $$ = A_OpExp(A_Pos($1->pos->line, $1->pos->pos), $1, A_less, $3);
} | EXP LE EXP {
  $$ = A_OpExp(A_Pos($1->pos->line, $1->pos->pos), $1, A_le, $3);
} | EXP GREATER EXP {
  $$ = A_OpExp(A_Pos($1->pos->line, $1->pos->pos), $1, A_greater, $3);
} | EXP GE EXP {
  $$ = A_OpExp(A_Pos($1->pos->line, $1->pos->pos), $1, A_ge, $3);
} | EXP EQ EXP {
  $$ = A_OpExp(A_Pos($1->pos->line, $1->pos->pos), $1, A_eq, $3);
} | EXP NEQ EXP {
  $$ = A_OpExp(A_Pos($1->pos->line, $1->pos->pos), $1, A_ne, $3);
} | NOT EXP {
  $$ = A_NotExp($1, $2);
} | MINUS EXP %prec UMINUS {
  $$ = A_MinusExp($1, $2);
} | '(' EXP ')' {
  $2->pos = $1;
  $$ = $2;
} | '(' '{' STMLIST '}' EXP ')' {
  $$ = A_EscExp($1, $3, $5);
} | EXP '.' ID {
  $$ = A_ClassVarExp(A_Pos($1->pos->line, $1->pos->pos), $1, String($3->u.v));
} | EXP '.' ID '(' EXPLIST ')' {
  $$ = A_CallExp(A_Pos($1->pos->line, $1->pos->pos), $1, String($3->u.v), $5);
} | EXP '[' EXP ']' {
  $$ = A_ArrayExp(A_Pos($1->pos->line, $1->pos->pos), $1, $3);
} ;

EXPLIST : /* empty */ {
  $$ = NULL;
} | EXP EXPREST {
  $$ = A_ExpList($1, $2);
} ;

EXPREST : /* empty */ {
  $$ = NULL;
} | ',' EXP EXPREST {
  $$ = A_ExpList($2, $3);
} ;

CLASSDECLLIST : /* empty */ {
  $$ = NULL;
} | CLASSDECL CLASSDECLLIST {
  $$ = A_ClassDeclList($1, $2);
} ;

CLASSDECL : PUBLIC CLASS ID '{' VARDECLLIST METHODDECLLIST '}' {
  $$ = A_ClassDecl($1, String($3->u.v), NULL, $5, $6);
} | PUBLIC CLASS ID EXTENDS ID '{' VARDECLLIST METHODDECLLIST '}' {
  $$ = A_ClassDecl($1, String($3->u.v), String($5->u.v), $7, $8);
} ;

METHODDECLLIST : /* empty */ {
  $$ = NULL;
} | METHODDECL METHODDECLLIST {
  $$ = A_MethodDeclList($1, $2);
} ;

METHODDECL : PUBLIC TYPE ID '(' FORMALLIST ')' '{' VARDECLLIST STMLIST '}' {
  $$ = A_MethodDecl($1, $2, String($3->u.v), $5, $8, $9);
} ;

TYPE : CLASS ID {
  $$ = A_Type($1, A_idType, String($2->u.v));
} | INT {
  $$ = A_Type($1, A_intType, NULL);
} | FLOAT {
  $$ = A_Type($1, A_floatType, NULL);
} | INT '[' ']' {
  $$ = A_Type($1, A_intArrType, NULL);
} | FLOAT '[' ']' {
  $$ = A_Type($1, A_floatArrType, NULL);
} ;


FORMALLIST : /* empty */ {
  $$ = NULL;
} | TYPE ID FORMALREST {
  $$ = A_FormalList(A_Formal(A_Pos($1->pos->line, $1->pos->pos), $1, String($2->u.v)), $3);
} | error ')' {
  add_char(')');
  fprintf(stderr, "Near line_%d: formal varible without type specified\n", $2->line);
  yyerrok;
  $$ = NULL;
} ;

FORMALREST : /* empty */ {
  $$ = NULL;
} | ',' TYPE ID FORMALREST {
  $$ = A_FormalList(A_Formal(A_Pos($2->pos->line, $2->pos->pos), $2, String($3->u.v)), $4);
} | ',' error ')' {
  add_char(')');
  fprintf(stderr, "Near line_%d: formal varible without type specified\n", $1->line);
  yyerrok;
  $$ = NULL;
};

%% /* 3. programs */
void yyerror(char *s) {
  fprintf(stderr, "%s\n",s);
}

void check_semi(char check, A_pos pos){
  if(check){
    fprintf(stderr, "Line_%d: \';\' expected\n", pos->line);
  }
}

void check_parentheses(char check, A_pos pos){
  if(check){
    fprintf(stderr, "Line_%d: missing or unpaired parentheses\n", pos->line);
  }
}


int yywrap() {
  return(1);
}