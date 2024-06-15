/*
 * print_ins.c - functions to print out instruction list in AS_instrList in xml format *
 */
#include <stdio.h>
#include "util.h"
#include "temp.h"
#include "assem.h"
#include "print_ins.h"

#define __PRINT_INS_DEBUG
#undef __PRINT_INS_DEBUG

static string getT_type(T_type type) {
  return type == T_int ? "T_int" : "T_float";
}

static void AS_format_xml_templist(string result, Temp_tempList tl, Temp_map m) {
  char ts[1024];
  if (!tl) {
    return ;
  }
  sprintf(ts, "<templist><temp><name>%s</name><type>%s</type></temp>", Temp_look(m, tl->head), getT_type(tl->head->type));
  strcat(result, ts);
  tl = tl->tail;
  AS_format_xml_templist(result, tl, m);
  strcat(result, "</templist>");
} 

static void AS_format_xml_labellist(string result, Temp_labelList ll) {
  char ts[1024];
  if (!ll) {
    return ;
  }
  sprintf(ts, "<labellist><label>%s</label>", Temp_labelstring(ll->head));
  strcat(result, ts);
  ll = ll->tail;
  AS_format_xml_labellist(result, ll);
  strcat(result, "</labellist>");
} 

static void AS_format_xml_inner(string result, string assem, Temp_tempList dst, Temp_tempList src, AS_targets jumps, Temp_map m) {
  char ts[1024];
  char *p;
  int i = 0;
  sprintf(ts, "\n<assem>%s</assem>\n", assem);
  strcat(result, ts);
  if (dst)  {
    strcat(result, "    <dst>");
    AS_format_xml_templist(result, dst, m);
    strcat(result, "</dst>\n");
  }
  if (src) {
    strcat(result, "    <src>");
    AS_format_xml_templist(result, src, m);
    strcat(result, "</src>\n");
  }
  if (jumps) {
    strcat(result, "    <jumps>");
    AS_format_xml_labellist(result, jumps->labels);
    strcat(result, "</jumps>");
  } 
}

static void AS_format_xml(string result, AS_instr as, Temp_map m) {
  char ts[1024];
  ts[0] = '\0';
  switch (as->kind) {
    case I_OPER:
      strcat(result, "<oper>");
      AS_format_xml_inner(result, as->u.OPER.assem, as->u.OPER.dst, as->u.OPER.src, as->u.OPER.jumps, m);
      strcat(result, "</oper>");
      break;
    case I_LABEL:
      strcat(result, "<label>");
      AS_format_xml_inner(result, as->u.LABEL.assem, NULL, NULL, NULL, m);
      sprintf(ts, "<temp_label>%s</temp_label>", Temp_labelstring(as->u.LABEL.label));
      strcat(result, ts);
      strcat(result, "</label>");
      break;
    case I_MOVE:
      strcat(result, "<move>");
      AS_format_xml_inner(result, as->u.MOVE.assem, as->u.MOVE.dst, as->u.MOVE.src, NULL, m);
      strcat(result, "</move>");
      break;
  }
#ifdef PRINT_INS_DEBUG
  fprintf(stderr, "AS_format_xml: %s\n", result);
#endif
  return ;  
}

void AS_print_xml(FILE *out,  AS_instrList il, Temp_map m) {
  char result[1024];
  result[0] = '\0';
  AS_instrList l= il;
  while (l) {
    AS_format_xml(result, l->head, m);
    fprintf(out, "%s\n", result);
    l = l->tail;
    result[0] = '\0';
  }
  return ;
}
