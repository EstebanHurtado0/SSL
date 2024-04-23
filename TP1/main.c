#include "scanner.h"

int main()
{
    token tokenReconocido;
    inicializarTabla();
    do
    {
        tokenReconocido = scanner();
        imprimirResultado(tokenReconocido);
    } while (tokenReconocido != TK_FDT);

    return 0;
}