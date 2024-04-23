%top{
    #include "tokens.h"
    #include <ctype.h>
}

%option header-file="scanner.h"
%option outfile="scanner.c"
%option nodefault

letra [[:alpha:]]
digito  [0-9]
identificador {letra}[{letra}{digito}]* 
entero {digito}+ 
exponente [eE][+-]?{entero}
fraccion  {entero}"."{entero}?|{entero}?"."{entero}
simbolos [+*/^=-]|"+="|"-="|"*="|"/="
funcion "sin"|"cos"|"tan"|"asin"|"acos"|"atan"|"log"|"sqrt" 
otrocaracter [^+*/^=\-[:space:]()]
noidentificador  {letra}|{otrocaracter}

%%
"var"|"salir"                {return TK_PALABRA_RESERVADA;}
{identificador}|{funcion}    {return TK_IDENTIFICADOR;}
{entero}                     | 
{entero}{exponente}          |
{fraccion}{exponente}?       {return TK_NUMERO;}
{simbolos}                   {return TK_OPERADOR;}
[()]                         {return TK_CARAC_PUNTUACION;}
{entero}{identificador}{digito}*     printf("Error léxico: constante inválida: %s\n", yytext);
{fraccion}({letra}|{fraccion})+         printf("Error léxico real inválido: %s\n", yytext);
{letra}({noidentificador})+    printf("Error léxico identificador inválido: %s\n", yytext);
" "                          ;
\n                           printf("Token: 'NL'\n");
{otrocaracter}({noidentificador})+      printf("Error lexico: cadena desconocida: %s\n", yytext);
.                            ;
