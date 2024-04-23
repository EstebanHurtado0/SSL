# Trabajo Práctico Nº 3

## Reconocedor Flex y Bison

### Propósito

En base a la gramática Sintáctica de la calculadora y la implementación de la gramática léxica hecha en el **TP2** se armó un programa que usando la herramientas `flex` y `bison` reconoce el lenguaje de la calculadora.

En este **TP** queremos reconocer la sintaxis sin hacer realmente los cálculos ni reconocer los posibles errores semánticos.

### Pruebas Realizadas
#### Entrada
```
var a
var b = 2.3
a = 3 + b*2
b^3
sin(pi/2)
a = b += 1
(2+3) * -a
13.25
12a3
a#2.4
2.3.4a2.3
@@#;@
2 * * 3
a
salir
```
#### Salida
```
Define ID como variable

Número
Define ID como variable con valor inicial

Número
ID
Número
Multplicación
Suma
Asignación
Expresión

ID
Número
Potenciación
Expresión

ID
Número
División
Función
Expresión

Número
Asignación con suma
Asignación
Expresión

Número
Número
Suma
Cierra paréntesis
ID
Cambio Signo
Multplicación
Expresión

Número
Expresión

Error léxico: constante inválida: 12a3

Error léxico: identificador inválido: a#2.4

Error léxico REAL inválido: 2.3.4a2.3
Error léxico: cadena desconocida: @@#;@

Número
syntax error, unexpected '*', expecting NUM or ID or '-' or '('

ID
Expresión
```

### Contenido del repositorio
- _main.c_: Fuente para probar el escáner
- _scanner.l_: Definiciones de `flex`
- _parser.y_: Definiciones de `bison`

### Compilador
Para esté trabajo práctico se utilizó el siguiente compilador:
- [GCC 13.2.1](https://gcc.gnu.org/onlinedocs/gcc-13.2.0/gcc/)
- Standard C: [C23 (2023)](https://open-std.org/JTC1/SC22/WG14/www/docs/n3096.pdf)