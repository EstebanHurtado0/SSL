#include "calc.h"

registroSim *sym_table = NULL;

registroSim *ultimoRegistroEnLaTabla(){
    registroSim *registro_n;
  for(registro_n = sym_table; registro_n->next != NULL; registro_n = registro_n->next);

  return registro_n;

}


registroSim *putsym (char const *sym_name, int sym_type)
{
  registroSim *ptr =  malloc (sizeof (registroSim));
  ptr->name =  malloc (strlen (sym_name) + 1);
  strcpy (ptr->name,sym_name);
  ptr->type = sym_type;//si es funcion o variable


  ptr->next = NULL;

  if(sym_table == NULL){
    sym_table = ptr;
  }else{
    registroSim *ultimoRegistro= ultimoRegistroEnLaTabla();
    ultimoRegistro->next = ptr;
  }

  return ptr;
}


registroSim *getsym (char const *sym_name)
{
  registroSim *ptr = sym_table;

   for (ptr = sym_table; ptr != NULL; ptr = ptr->next){
        if (strcmp (ptr->name, sym_name) == 0)
            break;
        
   }

    return ptr;
}

struct init const arith_fncts[] = {
  { "sin",  sin  },
  { "cos",  cos  },
  { "tan",  tan  },
  { "asin", asin },
  { "acos", acos },
  { "atan", atan },
  { "sqrt", sqrt },
  { "log",   log  },
  { "", 0 },//esto es para hallar el ultimo
};


void init_table(void){
  for (int i = 0;strcmp(arith_fncts[i].fname, "") != 0 ; i++)
    {
      registroSim *ptr = putsym (arith_fncts[i].fname, TYP_FNCT);
      ptr->value.fnctptr = arith_fncts[i].fnct;
    }

      registroSim *ptr_e = putsym ("e", TYP_VAR);
      ptr_e->value.var = M_E;
      registroSim *ptr_pi = putsym ("pi", TYP_VAR);
      ptr_pi->value.var = M_PI;
}


double aplicarFuncion(registroSim * func, double val){
    return (func->value.fnctptr)(val);
}




