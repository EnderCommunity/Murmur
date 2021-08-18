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

/**
 *  ref_statement
 *      : return <SYMBOL>
 *      ;
**/

int isRefStt(int typ, char *val){

    return (typ == LEXER_SYMBOL &&
        strcmp(val, "ref") == 0
    );

}

void crtRefStt(int linId){ //Create a ref_statement

    isrtPrsTrm("ref_statement", "", linId);

}
