#include <stdio.h>
#include <string.h>
#include "fdmjast.h"
#include "xml2ast.h"
#include "semant.h"
#include "canon.h"
#include "util.h"

#include "parser.h"

#include "assem.h"
#include "assemblock.h"
#include "bg.h"
#include "llvmgen.h"

#include "ssa.h"
#include "armgen.h"
#include "regalloc.h"

#include "print_src.h"
#include "print_ast.h"
#include "print_stm.h"
#include "print_irp.h"

A_prog root;

extern int yyparse();

static void print_to_ssa_file(string file_ssa, AS_instrList il) {
    freopen(file_ssa, "a", stdout);
    AS_printInstrList(stdout, il, Temp_name());
    fclose(stdout);
}

static void print_to_arm_file(string file_arm, AS_instrList il) {
    freopen(file_arm, "a", stdout);
    AS_printInstrList(stdout, il, Temp_name());
    fclose(stdout);
}

static void print_to_rpi_file(string file_rpi, AS_instrList il) {
    freopen(file_rpi, "a", stdout);
    AS_printInstrList(stdout, il, Temp_name());
    fclose(stdout);
}

static void run_llvm(string file_irp, string file_stm, string file_ins, string file_ssa) {
  // type checking & translate
  T_funcDeclList fdl = transA_Prog(stderr, root, 8);

  while (fdl) {
    freopen(file_irp, "a", stdout);
    fprintf(stdout, "------Original IR Tree------\n");
    printIRP_set(IRP_parentheses);
    printIRP_FuncDecl(stdout, fdl->head);
    fprintf(stdout, "\n\n");
    fflush(stdout);
    fclose(stdout);

    T_stm s = fdl->head->stm;
     // canonicalize
    T_stmList sl = C_linearize(s);
    
    freopen(file_stm, "a", stdout);
    fprintf(stdout, "-----------For function %s------------\n", fdl->head->name);
    fprintf(stdout, "------Linearized IR Tree------\n");
    printStm_StmList(stdout, sl, 0);
    fprintf(stdout, "\n\n");
    fflush(stdout);
    fclose(stdout);
    struct C_block b = C_basicBlocks(sl);
    freopen(file_stm, "a", stdout);
    fprintf(stdout, "------Basic Blocks------\n");
    for (C_stmListList sll = b.stmLists; sll; sll = sll->tail) {
      fprintf(stdout, "For Label=%s\n", S_name(sll->head->head->u.LABEL));
      printStm_StmList(stdout, sll->head, 0);
    }
    fprintf(stdout, "\n\n");
    fflush(stdout);
    fclose(stdout);

    sl = C_traceSchedule(b);
    freopen(file_stm, "a", stdout);
    fprintf(stdout, "------Canonical IR Tree------\n");
    printStm_StmList(stdout, sl, 0);
    fprintf(stdout, "\n\n");
    fflush(stdout);
    fclose(stdout);

    // llvm instruction selection
    // First making the head of the function, then the body, then the epilog
    b = C_basicBlocks(sl);
    AS_instrList prologil = llvmprolog(fdl->head->name, fdl->head->args, fdl->head->ret_type); //add the prolog of the function
    AS_blockList bodybl = NULL; //making an empty body

    // for each basic block we do the instruction selection
    for (C_stmListList sll = b.stmLists; sll; sll = sll->tail) {

      // the instruction selection function
      AS_instrList bil = llvmbody(sll->head);

      //making the list of AS instructions into a block of AS instructions
      AS_blockList bbl = AS_BlockList(AS_Block(bil), NULL);
      //putting the block into the list of blocks
      bodybl = AS_BlockSplice(bodybl, bbl);
    }

    //add the epilog of the function
    AS_instrList epilogil = llvmepilog(b.label);

    //make control flow graph (CFG) of the function
    G_nodeList bg = Create_bg(bodybl); // CFG

    freopen(file_ins, "a", stdout);
    fprintf(stdout, "\n------For function ----- %s\n\n", fdl->head->name); 
    fprintf(stdout, "------Basic Block Graph---------\n");
    Show_bg(stdout, bg);


    //put all the blocks into one AS list
    AS_instrList il = AS_traceSchedule(bodybl, prologil, epilogil, FALSE);

    printf("------~Final traced LLVM instructions ---------\n");
    AS_printInstrList(stdout, il, Temp_name());

    // body ins list
    AS_instrList bodyil = prologil->tail;
    if(bodyil == epilogil)bodyil = NULL;
    else {
      prologil->tail = NULL;
      AS_instrList i = bodyil;
      while(i->tail != epilogil)i = i->tail;
      i->tail = NULL;
    }

    // flow graph
    G_graph fg = FG_AssemFlowGraph(bodyil);
    freopen(file_ins, "a", stdout);
    fprintf(stdout, "------Flow Graph------\n");
    fflush(stdout);
    G_show(stdout, G_nodes(fg), (void*)FG_show);
    fprintf(stdout, "\n");
    fflush(stdout);
    fclose(stdout);

    // data flow analysis
    G_nodeList lg = Liveness(G_nodes(fg));
    freopen(file_ins, "a", stdout);
    fprintf(stdout, "/* ------Liveness Graph------*/\n");
    Show_Liveness(stdout, lg);
    fflush(stdout);
    fclose(stdout);

    // do ssa
    bg = Create_bg(instrList2BL(bodyil));
    AS_instrList bodyil_in_SSA = AS_instrList_to_SSA(bodyil, lg, bg);
    //print the AS_instrList to the ssa file`
    AS_instrList finalssa = AS_splice(AS_InstrList(prologil->head, bodyil_in_SSA), AS_InstrList(epilogil->head, NULL));
    print_to_ssa_file(file_ssa, finalssa);

    fdl = fdl->tail;
  }
}

int main(int argc, const char * argv[]) {
  if (argc != 2) {
    fprintf(stdout, "Usage: %s fmjFilename\n", argv[0]);
    return 1;
  }

  // output filename
  string file = checked_malloc(IR_MAXLEN);
  sprintf(file, "%s", argv[1]);
  string file_src = checked_malloc(IR_MAXLEN);
  sprintf(file_src, "%s.1.src", file);
  string file_ast = checked_malloc(IR_MAXLEN);
  sprintf(file_ast, "%s.2.ast", file);
  string file_irp = checked_malloc(IR_MAXLEN);
  sprintf(file_irp, "%s.3.irp", file);
  string file_stm = checked_malloc(IR_MAXLEN);
  sprintf(file_stm, "%s.4.stm", file);
  string file_ins = checked_malloc(IR_MAXLEN);
  sprintf(file_ins, "%s.5.ins", file);
  // string file_insxml = checked_malloc(IR_MAXLEN);
  // sprintf(file_insxml, "%s.6.ins", file);
  // string file_cfg= checked_malloc(IR_MAXLEN);
  // sprintf(file_cfg, "%s.7.cfg", file);
  string file_ssa= checked_malloc(IR_MAXLEN);
  sprintf(file_ssa, "%s.6.ssa", file);
  string file_arm= checked_malloc(IR_MAXLEN);
  sprintf(file_arm, "%s.7.arm", file);
  string file_rpi= checked_malloc(IR_MAXLEN);
  sprintf(file_rpi, "%s.8.s", file);

  // lex & parse
  yyparse();
  assert(root);

  // ast2src
  freopen(file_src, "w", stdout);
  printA_Prog(stdout, root);
  fflush(stdout);
  fclose(stdout);

  // ast2xml
  freopen(file_ast, "w", stdout);
  printX_Prog(stdout, root);
  fflush(stdout);
  fclose(stdout);

  // ################### FOR RUN-LLVM ARCH_SIZE = 8
  run_llvm(file_irp, file_stm, file_ins, file_ssa);
  
  // ################### FOR RUN-RPI ARCH_SIZE = 4
  // type checking & translate
  T_funcDeclList fdl = transA_Prog(stderr, root, 4);

  while (fdl) {
    T_stm s = fdl->head->stm;
     // canonicalize
    T_stmList sl = C_linearize(s);
    
    struct C_block b = C_basicBlocks(sl);

    sl = C_traceSchedule(b);

    // llvm instruction selection
    // First making the head of the function, then the body, then the epilog
    b = C_basicBlocks(sl);
    AS_instrList prologil = llvmprolog(fdl->head->name, fdl->head->args, fdl->head->ret_type); //add the prolog of the function
    AS_blockList bodybl = NULL; //making an empty body

    // for each basic block we do the instruction selection
    for (C_stmListList sll = b.stmLists; sll; sll = sll->tail) {

      // the instruction selection function
      AS_instrList bil = llvmbody(sll->head);

      //making the list of AS instructions into a block of AS instructions
      AS_blockList bbl = AS_BlockList(AS_Block(bil), NULL);
      //putting the block into the list of blocks
      bodybl = AS_BlockSplice(bodybl, bbl);
    }

    //add the epilog of the function
    AS_instrList epilogil = llvmepilog(b.label);

    //make control flow graph (CFG) of the function
    G_nodeList bg = Create_bg(bodybl); // CFG

    //put all the blocks into one AS list
    AS_instrList il = AS_traceSchedule(bodybl, prologil, epilogil, FALSE);

    // body ins list
    AS_instrList bodyil = prologil->tail;
    if(bodyil == epilogil)bodyil = NULL;
    else {
      prologil->tail = NULL;
      AS_instrList i = bodyil;
      while(i->tail != epilogil)i = i->tail;
      i->tail = NULL;
    }

    // flow graph
    G_graph fg = FG_AssemFlowGraph(bodyil);

    // data flow analysis
    G_nodeList lg = Liveness(G_nodes(fg));

    // do ssa
    bg = Create_bg(instrList2BL(bodyil));
    AS_instrList bodyil_in_SSA = AS_instrList_to_SSA(bodyil, lg, bg);
    //print the AS_instrList to the ssa file`
    AS_instrList finalssa = AS_splice(AS_InstrList(prologil->head, bodyil_in_SSA), AS_InstrList(epilogil->head, NULL));

    // llvm2arm
    AS_instrList arm_instrs = AS_instrList_to_arm(prologil->head, bg, FALSE);
    print_to_arm_file(file_arm, arm_instrs);

    G_nodeList arm_fg = G_nodes(FG_AssemFlowGraph(arm_instrs->tail));
    freopen(file_arm, "a", stdout);
    fprintf(stdout, "------Flow Graph------\n");
    fflush(stdout);
    G_show(stdout, arm_fg, (void*)FG_show);
    fprintf(stdout, "\n");
    fflush(stdout);
    fclose(stdout);

    G_nodeList live_arm = Liveness(arm_fg);
    freopen(file_arm, "a", stdout);
    fprintf(stdout, "/* ------Liveness Graph------*/\n");
    Show_Liveness(stdout, live_arm);
    fprintf(stdout, "\n");
    fflush(stdout);
    fclose(stdout);

    G_nodeList ig_local = Create_ig(live_arm);
    freopen(file_arm, "a", stdout);
    fprintf(stdout, "/* ------Interference Graph------*/\n");
    Show_ig(stdout, ig_local);
    fprintf(stdout, "\n\n");
    fflush(stdout);
    fclose(stdout);

    // regalloc
    AS_instrList rpi_instrs = regalloc(arm_instrs->tail, ig_local);
    print_to_rpi_file(file_rpi, AS_InstrList(arm_instrs->head, rpi_instrs));

    fdl = fdl->tail;
  }

  // print the runtime functions for the .ssa file
  freopen(file_ssa, "a", stdout);
  fprintf(stdout, "declare void @starttime()\n");
  fprintf(stdout, "declare void @stoptime()\n");
  fprintf(stdout, "declare i64* @malloc(i64)\n");
  fprintf(stdout, "declare void @putch(i64)\n");
  fprintf(stdout, "declare void @putint(i64)\n");
  fprintf(stdout, "declare void @putfloat(double)\n");
  fprintf(stdout, "declare i64 @getint()\n");
  fprintf(stdout, "declare float @getfloat()\n");
  fprintf(stdout, "declare i64* @getarray(i64)\n");
  fprintf(stdout, "declare i64 @getch(i64)\n");
  fprintf(stdout, "declare i64* @getfarray(i64)\n");
  fprintf(stdout, "declare void @putarray(i64, i64*)\n");
  fprintf(stdout, "declare void @putfarray(i64, i64*)\n");
  fclose(stdout);
  
  // print the runtime functions for the .rpi file
  freopen(file_rpi,"a",stdout);
  fprintf(stdout, ".global malloc\n");
  fprintf(stdout, ".global getint\n");
  fprintf(stdout, ".global getch\n");
  fprintf(stdout, ".global getfloat\n");
  fprintf(stdout, ".global getarray\n");
  fprintf(stdout, ".global getfarray\n");
  fprintf(stdout, ".global putint\n");
  fprintf(stdout, ".global putch\n");
  fprintf(stdout, ".global putfloat\n");
  fprintf(stdout, ".global putarray\n");
  fprintf(stdout, ".global putfarray\n");
  fprintf(stdout, ".global starttime\n");
  fprintf(stdout, ".global stoptime\n");
  fclose(stdout);

  return 0;
}
