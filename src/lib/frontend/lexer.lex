%{

#include <stdlib.h>
#include "fdmjast.h"
#include "parser.h"

int c;
int line = 1;
int pos = 1;

%}


%s COMMENT1 COMMENT2


punctuation [()\[\]{}=,;.!]
id      [a-z_A-Z][a-z_A-Z0-9]*
num     [1-9][0-9]*|0|[1-9][0-9]*\.[0-9]*|0\.[0-9]*|[1-9][0-9]*\.|0\.|\.[0-9]*

%%
<INITIAL>"//" {
  pos += 2;
  BEGIN COMMENT1;
}
<INITIAL>"/*" {
  pos += 2;
  BEGIN COMMENT2;
}
<INITIAL>" "|\t {
  pos += 1;
}
<INITIAL>\n {
  line += 1;
  pos = 1;
}
<INITIAL>\r {}
<INITIAL>"public" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return PUBLIC;
}
<INITIAL>"int" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return INT;
}
<INITIAL>"main" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return MAIN;
}
<INITIAL>"float" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return FLOAT;
}
<INITIAL>"class" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return CLASS;
}
<INITIAL>"new" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return NEW;
}
<INITIAL>"if" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return IF;
}
<INITIAL>"else" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return ELSE;
}
<INITIAL>"while" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return WHILE;
}
<INITIAL>"continue" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return CONTINUE;
}
<INITIAL>"break" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return BREAK;
}
<INITIAL>"this" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return THIS;
}
<INITIAL>"extends" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return EXTENDS;
}
<INITIAL>"return" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return RETURN;
}
<INITIAL>"true" {
  yylval.exp = A_BoolConst(A_Pos(line, pos), 1);
  pos += yyleng;
  return BOOLTRUE;
}
<INITIAL>"false" {
  yylval.exp = A_BoolConst(A_Pos(line, pos), 0);
  pos += yyleng;
  return BOOLFALSE;
}

<INITIAL>"putnum" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return PUTNUM;
}
<INITIAL>"putch" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return PUTCH;
}
<INITIAL>"putarray" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return PUTARRAY;
}
<INITIAL>"starttime" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return STARTTIME;
}
<INITIAL>"stoptime" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return STOPTIME;
}
<INITIAL>"length" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return LENGTH;
}
<INITIAL>"getnum" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return GETNUM;
}
<INITIAL>"getch" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return GETCH;
}
<INITIAL>"getarray" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return GETARRAY;
}

<INITIAL>"+" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return ADD;
}
<INITIAL>"-" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return MINUS;
}
<INITIAL>"*" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return TIMES;
}
<INITIAL>"/" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return DIV;
}
<INITIAL>"||" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return OR;
}
<INITIAL>"&&" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return AND;
}
<INITIAL>"<=" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return LE;
}
<INITIAL>"<" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return LESS;
}
<INITIAL>">=" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return GE;
}
<INITIAL>">" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return GREATER;
}
<INITIAL>"==" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return EQ;
}
<INITIAL>"!=" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return NEQ;
}
<INITIAL>"!" {
  yylval.pos = A_Pos(line, pos);
  pos += yyleng;
  return NOT;
}
<INITIAL>{punctuation} {
  yylval.pos = A_Pos(line, pos);
  pos += 1;
  c = yytext[0];
  return c;
}
<INITIAL>{num} {
  yylval.exp = A_NumConst(A_Pos(line, pos), atof(yytext));
  pos += yyleng;
  return NUM;
}
<INITIAL>{id} {
  yylval.exp = A_IdExp(A_Pos(line, pos), String(yytext));
  pos += yyleng;
  return ID;
}
<INITIAL>. {
  printf("Illegal input \"%c\"\n", yytext[0]);
}
<COMMENT1>\n {
  line += 1;
  pos = 1;
  BEGIN INITIAL;
}
<COMMENT1>. {
  pos += 1;
}

<COMMENT2>"*/" {
  pos += 2;
  BEGIN INITIAL;
}
<COMMENT2>\n {
  line += 1;
  pos = 1;
}
<COMMENT2>. {
  pos += 1;
}

%% /* 3. programs */
void add_char(int c){
  unput(c);
}