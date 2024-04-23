%top{
    #include <ctype.h>
    #include "parser.h"
    #include <strings.h>
}

%{
    char mensaje[50];
%}

%option header-file="scanner.h"
%option outfile="scanner.c"
%option nodefault

letra [[:alpha:]]
digito  [0-9]
identificador {letra}[{letra}{digito}]* 
entero {digito}+ 
exponente [eE][+-]?{entero}
fraccion  {entero}"."{entero}?|{entero}?"."{entero}
simbolos [+*/^=-]
funcion "sin"|"cos"|"tan"|"asin"|"acos"|"atan"|"log"|"sqrt" 
otrocaracter [^+*/^=\-[:space:]()]
noidentificador {letra}|{otrocaracter}

%%
"var"                        {return TK_VAR;}
"salir"                      {return TK_SALIR;}
{identificador}|{funcion}    {return TK_IDENTIFICADOR;}
{entero}                     | 
{entero}{exponente}          |
{fraccion}{exponente}?       {return TK_NUMERO;}
{simbolos}                   {return yytext[0];}
"+="                         {return TK_ASIG_SUM;}
"-="                         {return TK_ASIG_RES;}
"*="                         {return TK_ASIG_MUL;}
"/="                         {return TK_ASIG_DIV;}
[()]                         {return yytext[0];}
{entero}{identificador}{digito}*     { 
                                        sprintf(mensaje, "Error léxico: constante inválida: %s", yytext);
                                        yyerror(mensaje);
                                    }
{fraccion}({letra}|{fraccion})+     { 
                                        sprintf(mensaje, "Error léxico: constante inválida: %s", yytext);
                                        yyerror(mensaje);
                                    }
{letra}({noidentificador})+         { 
                                        sprintf(mensaje, "Error léxico: constante inválida: %s", yytext);
                                        yyerror(mensaje);
                                    }
" "                                 ;
\n                                  {return yytext[0];}
{otrocaracter}({noidentificador})+  { 
                                        sprintf(mensaje, "Error léxico: constante inválida: %s", yytext);
                                        yyerror(mensaje);
                                    }
.                                   ;
