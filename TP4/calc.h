#ifndef CALC_H
#define CALC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"


#define TYP_VAR 0
#define TYP_FNCT 1


typedef double (*func_t) (double);


typedef struct registroSim
{
  char *name;
  int type;   
  union
  {
    double var;    
    func_t fnctptr;
  } value;
  struct registroSim *next;
} registroSim;


extern registroSim *sym_table;
extern int yysemerrs;


registroSim *putsym (char const *, int);


registroSim *getsym (char const *);

void init_table(void);

struct init
{
  char const *fname;
  double (*fnct) (double);
};



double aplicarFuncion(registroSim *, double );


void actualizarVariable(const char*, double);
#endif
