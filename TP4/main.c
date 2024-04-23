#include "parser.h"
#include "calc.h"


int main(){
    init_table();
    yyparse();

    return 0;
}