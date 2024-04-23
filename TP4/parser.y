%code top {
    #include "scanner.h"
    #include "calc.h"
}

%code provides{
    void yyerror(const char *s);
    int validarInicializacion(const char* identificador, double val);
}
%code {
    char error_text[300];
}

%defines "parser.h"
%output "parser.c"
%define parse.error verbose
%start sesion

%union {
    double dval;
    char *sval;
}

%token<sval> TK_IDENTIFICADOR 
%token<dval> TK_NUMERO 
%token<sval> TK_FUNCION
%token TK_VAR "var"
%token TK_SALIR "salir"
%token TK_ASIG_SUM "+=" 
%token TK_ASIG_RES "-=" 
%token TK_ASIG_DIV "/=" 
%token TK_ASIG_MUL "*="

%type <dval> aditiva
%type <dval> termino
%type <dval> factor
%type <dval> potencia
%type <dval> primaria
%type <dval> linea
%type <dval> expresion

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
           expresion '\n'                            { printf("> %lf\n", $1); }                         
        |  "var" TK_IDENTIFICADOR '\n'                { if(validarInicializacion($2, 0)) printf("> %s: %d\n", $2, 0);}
        |  "var" TK_IDENTIFICADOR '=' expresion  '\n' {if(!validarInicializacion($2, $4)) YYERROR; else printf("> %s: %lf\n", $2, $4);} 
        |  "salir" '\n'                               {YYABORT;}     
        |   error '\n'                              {}
        |  '\n'                                     {} 
        ;   
    

    expresion:
            aditiva                      
        |   TK_IDENTIFICADOR '=' expresion             {$$ = $3; if(getsym($1)!=NULL){
                                                                    getsym($1)->value.var = $3;
                                                                } else {
                                                                    sprintf(error_text,"> La variable %s no existe", $1); 
                                                                    yyerror(error_text);
                                                                }}  

        |   TK_IDENTIFICADOR "+="  expresion           {if(getsym($1)!=NULL){
                                                            getsym($1)->value.var += $3;
                                                            $$ = getsym($1)->value.var;
                                                        } else {
                                                           sprintf(error_text, "> La variable %s no existe", $1);
                                                           yyerror(error_text);YYERROR;
                                                        }} 
        |   TK_IDENTIFICADOR "-=" expresion            {if(getsym($1)!=NULL){
                                                            getsym($1)->value.var -= $3;
                                                            $$ = getsym($1)->value.var;
                                                        } else{
                                                            sprintf(error_text, "> La variable %s no existe", $1); 
                                                            yyerror(error_text );
                                                            YYERROR;
                                                        }}  
        |   TK_IDENTIFICADOR "*=" expresion            {if(getsym($1)!=NULL){
                                                            getsym($1)->value.var *= $3;
                                                            $$ = getsym($1)->value.var;
                                                        } else {
                                                            sprintf(error_text, "> La variable %s no existe", $1); 
                                                            yyerror(error_text );
                                                            YYERROR;
                                                        }} 
        |   TK_IDENTIFICADOR "/=" expresion            {if(getsym($1)!=NULL){
                                                            getsym($1)->value.var /= $3;
                                                            $$ = getsym($1)->value.var;
                                                        } else {
                                                            sprintf(error_text, "> La variable %s no existe", $1); 
                                                            yyerror(error_text );
                                                            YYERROR;
                                                        }} 
        ;
    
    aditiva:
            termino                      
        |   expresion '+' termino                  {$$ = $1 + $3;}        
        |   expresion '-' termino                  {$$ = $1 - $3;}        
        ;
    
    termino:
            factor                       
        |   termino '*' factor                     {$$ = $1 * $3;}           
        |   termino '/' factor                     {$$ = $1 / $3;} 
        ;
    
    factor:
            potencia                     
        |   '-' factor %prec NEG                   {$$ = -$2;} 
        ;
    
    potencia:
            primaria                                
        |   primaria '^' potencia                  {$$ = pow($1, $3);} 
        ;
    
    primaria:
            TK_IDENTIFICADOR                       {if(getsym($1)!=NULL) {
                                                        $$ = getsym($1)->value.var;
                                                    } else {
                                                        sprintf(error_text, "> Error: ID %s no declarado", $1);
                                                        yyerror(error_text);  
                                                        YYERROR;  
                                                    } }                
        |   TK_NUMERO                              {$$ = $1;}    
        |   '(' expresion ')'                      {$$ = $2;}               
        |   TK_FUNCION '(' expresion ')'     { struct registroSim* regSym = getsym($1);
                                                if(regSym != NULL){
                                                    $$ = aplicarFuncion(regSym, $3);
                                                }else{
                                                    sprintf(error_text, "> Error: ID %s no declarado", $1); 
                                                    yyerror(error_text);
                                                    YYERROR;
                                              }} 
        ;
%%

void yyerror(const char *s){
	printf("%s\n", s);
}


int validarInicializacion(const char* identificador, double val){

   if(getsym(identificador) != NULL){
      yyerror("> Error, identificador ya declarado como variable");
      return 0;
   }
   else{
        //lo agrego en el diccionario
        registroSim* registro_sem = putsym(identificador,TYP_VAR);
        registro_sem->value.var = val;
        return 1;
   }
   
}
