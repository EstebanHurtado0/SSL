#include<stdio.h>
#include"scanner.h"

int main(){
    token TOKEN;

    do{
        TOKEN = yylex();
        printf("Token: ");
        switch (TOKEN)
        {
        case TK_IDENTIFICADOR:
            printf("Identificador    lexema: %s\n", yytext);
            break;
        case TK_NUMERO:
            printf("nro    lexema: %s\n", yytext);
            break;
        case TK_CARAC_PUNTUACION:
            printf("'%s'\n", yytext);
            break;
        case TK_OPERADOR:
            printf("'%s'\n", yytext);
            break;
        case TK_FUNCION:
            printf("Funcion    lexema: %s\n", yytext);
            break;
        case TK_PALABRA_RESERVADA:
            printf("%s\n", yytext);
            break;
        }

    }while(TOKEN != FDT);

    printf("Token: Fin de Archivo\n");

    return 0;
}
