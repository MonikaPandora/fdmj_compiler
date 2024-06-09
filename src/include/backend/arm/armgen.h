#ifndef ARMGEN_H
#define ARMGEN_H

#include "assem.h"
#include "assemblock.h"
#include "util.h"
#include "graph.h"

// AS_instrList armprolog(AS_instrList il);
// AS_instrList armbody(AS_instrList il);
// AS_instrList armepilog(AS_instrList il);

AS_instrList AS_instrList_to_arm(AS_instr prologi, G_nodeList bg, bool save_all_callee);

#endif
