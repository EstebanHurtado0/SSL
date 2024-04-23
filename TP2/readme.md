# Trabajo Práctico Nº 2

## Reconocedor Flex

### Propósito

En base a la gramática léxica de la calculadora, se armó un programa que la reconozca usando la herramienta `flex`. Se tuvo en cuenta que los tokens devueltos no son directamente los documentados, sino que se puede abrir en más para una mejor implementación, por ejemplo con un token para cada palabra reservada, carácter de puntuación u operador.

### Pruebas Realizadas
#### Entrada
```
a
var a
var b = 2.3
var a
a = 3 + b*2
b^3
e
sin(pi/2)
a = b += 1
a
b
(2+3) * -a
13.25
12a3
a#2.4
2.3.4a2.3
@@#;@
a + 2
a = z + 2
a
2 * * 3
salir
```
#### Salida
```
Token: Identificador	lexema: a
Token: 'NL'
Token: var
Token: Identificador	lexema: a
Token: 'NL'
Token: var
Token: Identificador	lexema: b
Token: '='
Token: nro	lexema: 2.3
Token: 'NL'
Token: var
Token: Identificador	lexema: a
Token: 'NL'
Token: Identificador	lexema: a
Token: '='
Token: nro	lexema: 3
Token: '+'
Token: Identificador	lexema: b
Token: '*'
Token: nro	lexema: 2
Token: 'NL'
Token: Identificador	lexema: b
Token: '^'
Token: nro	lexema: 3
Token: 'NL'
Token: Identificador	lexema: e
Token: 'NL'
Token: Identificador	lexema: sin
Token: '('
Token: Identificador	lexema: pi
Token: '/'
Token: nro	lexema: 2
Token: ')'
Token: 'NL'
Token: Identificador	lexema: a
Token: '='
Token: Identificador	lexema: b
Token: +=
Token: nro	lexema: 1
Token: 'NL'
Token: Identificador	lexema: a
Token: 'NL'
Token: Identificador	lexema: b
Token: 'NL'
Token: '('
Token: nro	lexema: 2
Token: '+'
Token: nro	lexema: 3
Token: ')'
Token: '*'
Token: '-'
Token: Identificador	lexema: a
Token: 'NL'
Token: nro	lexema: 13.25
Token: 'NL'
Error léxico: constante inválida: 12a3Token: 'NL'
Error léxico: identificador inválido: a#2.4Token: 'NL'
Error léxico REAL inválido: 2.3.4a2.3
Token: 'NL'
Error léxico: cadena desconocida: @@#;@Token: 'NL'
Token: Identificador	lexema: a
Token: '+'
Token: nro	lexema: 2
Token: 'NL'
Token: Identificador	lexema: a
Token: '='
Token: Identificador	lexema: z
Token: '+'
Token: nro	lexema: 2
Token: 'NL'
Token: Identificador	lexema: a
Token: 'NL'
Token: nro	lexema: 2
Token: '*'
Token: '*'
Token: nro	lexema: 3
Token: 'NL'
Token: salir
Token: 'NL'
Token: Fin de Archivo
```

### Contenido del repositorio
- _main.c_: Fuente para probar el escáner
- _scanner.l_: Definiciones del `flex`
- _tokens.h_: tokens a utilzar

### Compilador
Para esté trabajo práctico se utilizó el siguiente compilador:
- [GCC 13.2.1](https://gcc.gnu.org/onlinedocs/gcc-13.2.0/gcc/)
- Standard C: [C23 (2023)](https://open-std.org/JTC1/SC22/WG14/www/docs/n3096.pdf)