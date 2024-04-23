%code top {
    #include "scanner.h"
    #include <stdio.h>
}

%code provides{
    void yyerror(const char *s);
}

%defines "parser.h"
%output "parser.c"
%define parse.error verbose
%start sesion

%token TK_IDENTIFICADOR TK_NUMERO 
%token TK_VAR "var"
%token TK_SALIR "salir"
%token TK_ASIG_SUM "+=" 
%token TK_ASIG_RES "-=" 
%token TK_ASIG_DIV "/=" 
%token TK_ASIG_MUL "*="

%right '=' "+=" "-=" "/=" "*="
%left '+' '-'
%left '*' '/'
%left '^'
%precedence NEG
%left '(' ')'

%%
    sesion: 
        %empty |
        sesion linea {printf("\n");}
        ;
    
    linea:
            error '\n'
        |   expresion '\n'                            {printf("Expresión\n");}                         
        |   "var" TK_IDENTIFICADOR '\n'               {printf("Define ID como variable\n");}               
        |   "var" TK_IDENTIFICADOR '=' expresion '\n' {printf("Define ID como variable con valor incial\n");} 
        |   "salir" '\n'                              
        |   '\n'                                      
        ;   

    expresion:
            aditiva                      
        |   TK_IDENTIFICADOR '=' expresion             {printf("Asignación\n");}  
        |   TK_IDENTIFICADOR "+="  expresion           {printf("Asignación con suma\n");} 
        |   TK_IDENTIFICADOR "-=" expresion            {printf("Asignación con resta\n");} 
        |   TK_IDENTIFICADOR "*=" expresion            {printf("Asignación con multiplicación\n");} 
        |   TK_IDENTIFICADOR "/=" expresion            {printf("Asignación con división\n");} 
        ;
    
    aditiva:
            termino                      
        |   expresion '+' termino                  {printf("Suma\n");}        
        |   expresion '-' termino                  {printf("Resta\n");}        
        ;
    
    termino:
            factor                       
        |   termino '*' factor                     {printf("Multiplicación\n");}           
        |   termino '/' factor                     {printf("División\n");} 
        ;
    
    factor:
            potencia                     
        |   '-' factor %prec NEG                   {printf("Cambio signo\n");} 
        ;
    
    potencia:
            primaria                     
        |   primaria '^' potencia                  {printf("Potenciación\n");} 
        ;
    
    primaria:
            TK_IDENTIFICADOR                       {printf("ID\n");}                
        |   TK_NUMERO                              {printf("Número\n");}    
        |   '(' expresion ')' {printf("Cierra paréntesis\n");}               
        |   TK_IDENTIFICADOR '(' expresion ')'     {printf("Función\n");}  //Ver tema de TK_IDENTIFICADOR y TK_FUNCION por el scanner
        ;
%%

void yyerror(const char *s){
	printf("%s\n", s);
}