#ifndef UTIL_H
#define UTIL_H

#include <assert.h>

typedef char *string;
typedef char bool;

#define TRUE 1
#define FALSE 0
#define IR_MAXLEN 200

void *checked_malloc(int);
string String(char *);

typedef struct U_boolList_ *U_boolList;
struct U_boolList_ {
  bool head;
  U_boolList tail;
};
U_boolList U_BoolList(bool head, U_boolList tail);

#define _for_in_table(iter, tbl) \
    for(binder iter = tbl->top ? TAB_getBinder(tbl, tbl->top) : NULL; iter; iter = TAB_getBinder(tbl, iter->prevtop))

#define DEBUG
#undef DEBUG


#ifdef DEBUG
#define INFO(message, ...) \
    fprintf(stderr, message, ##__VA_ARGS__)

#define ASSERT(condition) \
if(!(condition)){ \
  fprintf(stderr, "%s, %d: assert failed\n", __FILE__, __LINE__); \
  fflush(stderr); \
  exit(-1); \
}
#else
#define INFO(message, ...) ((void)0)

#define ASSERT(condition) ((void)0)
#endif

#endif
