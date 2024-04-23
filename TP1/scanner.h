#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

void inicializarTabla(void);

typedef enum
{
    INICIAL = 0,
    POSIBLEHEXA = 1,
    IDENTIFICADOR = 2,
    ENTERODECIMAL = 3,
    ENTEROHEXADECIMAL = 4,
    ERRORGEN = 5,
    ERROREMF = 6,
    FDT = 7,
    PARAR = 99 // ENTERO MAL FORMADO
} estado;

typedef enum
{
    LETRAS_HASTA_A_F = 0,
    LETRAS_RESTANTES_MENOS_LA_X = 1,
    LETRA_X = 2,
    DIGITO_MENOS_0 = 3,
    DIGITO_0 = 4,
    ESPACIO = 5,
    FIN_DE_TEXTO = 6,
    OTRO_CARACTER = 7
} caracter;

typedef enum
{
    TK_IDENTIFICADOR,
    TK_ENTERODECIMAL,
    TK_ENTEROHEXADECIMAL,
    TK_ERRORGEN,
    TK_ERROREMF,
    TK_FDT
} token;

extern char lexema[200];

bool parar(estado estado_a);
bool esAceptor(estado estado_a);

caracter reconocerCaracter(int carac);

token reconocerToken(estado estado_a);

void imprimirResultado(token token_a);

token scanner(void);

#endif // ARCHIVO_H_INCLUDED