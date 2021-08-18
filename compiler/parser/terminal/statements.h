/**
 *  return_statement
 *      : return <SYMBOL>
 *      ;
**/

int isRtnStt(int typ, char *val){

    return (typ == LEXER_SYMBOL &&
        strcmp(val, "return") == 0
    );

}

void crtRtnStt(int linId){ //Create a return_statement

    isrtPrsTrm("return_statement", "", linId);

}