# Trabajo Práctico Nº 1

## Un escáner elemental

### Tabla de Transición

Se desarrolló un escáner basado en la siguiente tabla de transición (también en el archivo tabla_SSL.xlsx):

|                                       |         |            |  [g-z][G-Z] - {xX}  |      |         |     |           |     |      |
| ------------------------------------- | ------- | ---------- | ------------------- | ---- | ------- | --- | --------- | --- | ---- |
|             **Comentario**            | **Estados** | **[a-f][A-F]** | **C - {(a-f) U (A-F)}** | **[xX]** | **D - {0}** |  **0**  | **EN_BLANCO** | **fdt** | **OTRO** |
| INICIAL                               |    0-   |      2     |          2          |  2   |    3    |  1  |     99    |  7  |  5   |
| Posible hex                           |    1+   |      6     |          6          |  4   |    3    |  3  |     99    |  7  |  6   |
| Reconociendo identificador            |    2+   |      2     |          2          |  2   |    2    |  2  |     99    |  7  |  5   |
| Reconociendo entero decimal           |    3+   |      6     |          6          |  6   |    3    |  3  |     99    |  7  |  99  |
| Reconociendo entero hexadecimal       |    4+   |      4     |          6          |  6   |    4    |  4  |     99    |  7  |  99  |
| Reconociendo error general            |    5    |      5     |          5          |  5   |    5    |  5  |     99    |  7  |  5   |
| Reconociendo error entero mal formado |    6    |      6     |          6          |  6   |    6    |  6  |     99    |  7  |  6   |
| FDT reconocido                        |    7+   |      7     |          7          |  7   |    7    |  7  |     99    |  7  |  7   |

### Tokens

El lenguaje a reconocer tiene los siguientes tokens:
- **Identificador:** comienzan con una letra y sigue con letras y dígitos.
- **Entero:** solo dígitos decimales.
- **Hexadecimal:** Comienza con un cero seguido de una equis, y luego puede seguir dígitos hexadecimales.

A tener en cuenta:
- Las letras siempre pueden ser mayúsculas o minúsculas, tanto en identificadores como en hexadecimales.
- 0: es un entero válido.
- 0x ó 0X: son hexadecimales válidos.

### Notas de implementación:
- Deberá tener un token que represente el fin de archivo.
- Si bien en un escáner real lo habitual es manejar los errores en lugar de devolverlos, en esta 
implementación devolveremos como tokens los siguientes tipos de errores:
 - **Error general:** una cadena formada por caracteres que no pertenecen a nuestro alfabeto.
 - **Entero mal formado:** una cadena que comienza con dígitos, y es seguida por dígitos o letras.

### Contenido del repositorio
- _tabla_SSL.xlsx_: Documentación de la TT
- _main.c_: Fuente para probar el escáner
- _scanner.c_: Definiciones del escáner
- _scanner.h_: Declaraciones del escáner

### Compilador
Para esté trabajo práctico se utilizó el siguiente compilador:
- [GCC 13.2.1](https://gcc.gnu.org/onlinedocs/gcc-13.2.0/gcc/)
- Standard C: [C23 (2023)](https://open-std.org/JTC1/SC22/WG14/www/docs/n3096.pdf)


