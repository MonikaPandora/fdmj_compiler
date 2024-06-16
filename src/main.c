#include <stdio.h>
#include <string.h>
#include <getopt.h>
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
#include "regalloc.h"

#include "print_src.h"
#include "print_ast.h"
#include "print_stm.h"
#include "print_irp.h"

A_prog root;

extern int yyparse();

// void usage(const char* progname) {
//     printf("Usage: %s -f [FMJFileName] [Option]\n", progname);
//     printf("Program Options:\n");
//     printf("  -f  --file     fmj source file\n");
//     printf("  -c  --compile  compiles each fmj source file in the test directory (and generates all the printout files\n");
//     printf("  -l  --llvm     compiles to llvm_ir and converts to SSA form(with arch_size=8)\n");
//     printf("  -r  --rpi      compiles to the RPi code after register allocation(with arch_size=4)\n");
//     printf("  -?  --help     this message\n");
// }


static void print_to_ssa_file(string file_ssa, AS_instrList il) {
    freopen(file_ssa, "a", stdout);
    AS_printInstrList(stdout, il, Temp_name());
    fclose(stdout);
}

int main(int argc, const char * argv[]) {
  if (argc != 2) {
    fprintf(stdout, "Usage: %s fmjFilename\n", argv[0]);
    return 1;
  }

  // struct option long_options[] = {
  //   {"threads", 1, 0, 't'},
  //   {"size", 1, 0, 's'},
  //   {"help", 0, 0, '?'},
  //   {0 ,0, 0, 0}
  // };

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

  return 0;
}
