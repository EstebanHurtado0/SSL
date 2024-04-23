#include "scanner.h"

char lexema[200];

static int tabla_transicion[8][8];

void inicializarTabla(void)
{
    tabla_transicion[0][0] = 2;
    tabla_transicion[0][1] = 2;
    tabla_transicion[0][2] = 2;
    tabla_transicion[0][3] = 3;
    tabla_transicion[0][4] = 1;
    tabla_transicion[0][5] = 99;
    tabla_transicion[0][6] = 7;
    tabla_transicion[0][7] = 5;

    tabla_transicion[1][0] = 6;
    tabla_transicion[1][1] = 6;
    tabla_transicion[1][2] = 4;
    tabla_transicion[1][3] = 3;
    tabla_transicion[1][4] = 3;
    tabla_transicion[1][5] = 99;
    tabla_transicion[1][6] = 7;
    tabla_transicion[1][7] = 6;

    tabla_transicion[2][0] = 2;
    tabla_transicion[2][1] = 2;
    tabla_transicion[2][2] = 2;
    tabla_transicion[2][3] = 2;
    tabla_transicion[2][4] = 2;
    tabla_transicion[2][5] = 99;
    tabla_transicion[2][6] = 7;
    tabla_transicion[2][7] = 5;

    tabla_transicion[3][0] = 6;
    tabla_transicion[3][1] = 6;
    tabla_transicion[3][2] = 6;
    tabla_transicion[3][3] = 3;
    tabla_transicion[3][4] = 3;
    tabla_transicion[3][5] = 99;
    tabla_transicion[3][6] = 7;
    tabla_transicion[3][7] = 99;

    tabla_transicion[4][0] = 4;
    tabla_transicion[4][1] = 6;
    tabla_transicion[4][2] = 6;
    tabla_transicion[4][3] = 4;
    tabla_transicion[4][4] = 4;
    tabla_transicion[4][5] = 99;
    tabla_transicion[4][6] = 7;
    tabla_transicion[4][7] = 99;

    tabla_transicion[5][0] = 5;
    tabla_transicion[5][1] = 5;
    tabla_transicion[5][2] = 5;
    tabla_transicion[5][3] = 5;
    tabla_transicion[5][4] = 5;
    tabla_transicion[5][5] = 99;
    tabla_transicion[5][6] = 7;
    tabla_transicion[5][7] = 5;

    tabla_transicion[6][0] = 6;
    tabla_transicion[6][1] = 6;
    tabla_transicion[6][2] = 6;
    tabla_transicion[6][3] = 6;
    tabla_transicion[6][4] = 6;
    tabla_transicion[6][5] = 99;
    tabla_transicion[6][6] = 7;
    tabla_transicion[6][7] = 6;

    tabla_transicion[7][0] = 7;
    tabla_transicion[7][1] = 7;
    tabla_transicion[7][2] = 7;
    tabla_transicion[7][3] = 7;
    tabla_transicion[7][4] = 7;
    tabla_transicion[7][5] = 99;
    tabla_transicion[7][6] = 7;
    tabla_transicion[7][7] = 7;
}

bool parar(estado estado_a)
{
    return (estado_a == FDT || estado_a == PARAR);
}

bool esAceptor(estado estado_a)
{
    return (estado_a == IDENTIFICADOR || 
            estado_a == POSIBLEHEXA ||
            estado_a == ENTERODECIMAL || 
            estado_a == ENTEROHEXADECIMAL || 
            estado_a == FDT);
}

bool esError(estado estado_a) {
    return (estado_a == ERRORGEN || estado_a == ERROREMF);
}

caracter reconocerCaracter(int carac)
{

    if (tolower(carac) == 'x')
    {
        return LETRA_X;
    }
    else if (carac == '0')
    {
        return DIGITO_0;
    }
    else if (isalpha(carac) && isxdigit(carac)) // letras de la 'a' a la 'f'
    {
        return LETRAS_HASTA_A_F;
    }
    else if (isdigit(carac))
    {
        return DIGITO_MENOS_0;
    }
    else  if (isalpha(carac)) // resto de letras menos la x
    {
        return LETRAS_RESTANTES_MENOS_LA_X;
    }
    else if (isspace(carac))
    {
        return ESPACIO;
    }
    else if (carac == EOF)
    {
        return FIN_DE_TEXTO;
    }
    else if (ispunct(carac)) return OTRO_CARACTER;
}

token reconocerToken(estado estado_a)
{

    switch (estado_a)
    {
    case IDENTIFICADOR:
        return TK_IDENTIFICADOR;
    case ENTERODECIMAL:
        return TK_ENTERODECIMAL;
    case ENTEROHEXADECIMAL:
        return TK_ENTEROHEXADECIMAL;
    case ERRORGEN:
        return TK_ERRORGEN;
    case ERROREMF:
        return TK_ERROREMF;
    case FDT:
        return TK_FDT;
    case INICIAL:
        return TK_FDT;
    case POSIBLEHEXA:
        return TK_ENTERODECIMAL;
    default:
        return TK_ERRORGEN;
    }
}

void imprimirResultado(token token_a)
{

    switch (token_a)
    {
    case TK_IDENTIFICADOR:
        printf("Identificador '%s' \n", lexema);
        break;
    case TK_ENTERODECIMAL:
        printf("Entero Decimal '%s' \n", lexema);
        break;
    case TK_ENTEROHEXADECIMAL:
        printf("Entero Hexadecimal '%s' \n", lexema);
        break;
    case TK_ERRORGEN:
        printf("Error General '%s' \n", lexema);
        break;
    case TK_ERROREMF:
        printf("Error Entero Mal Formado '%s' \n", lexema);
        break;
    case TK_FDT:
        printf("Fin De Texto \n");
        break;
    }
}

token scanner(void)
{
    estado estado_a = INICIAL;
    estado estado_aux = INICIAL;
    caracter posibleCaracter;
    token posibleToken;
    int carac, i = 0;

    while (!parar(estado_a) || estado_aux == INICIAL)
    {

        carac = getchar();
        posibleCaracter = reconocerCaracter(carac);
        
        estado_a = tabla_transicion[estado_a][posibleCaracter];

        if ((esAceptor(estado_a) || esError(estado_a)) && i < 200)
        {
            lexema[i] = (char)carac;
            posibleToken = reconocerToken(estado_a);
            estado_aux = estado_a;
            i++;
        }

    }
    
    if (esAceptor(estado_aux) && posibleCaracter == OTRO_CARACTER)
    {
        ungetc(carac, stdin);
        lexema[i] = '\0';
    }
    else if (esAceptor(estado_aux) || esError(estado_aux)){
        lexema[i] = '\0';
    }

    return posibleToken;
}