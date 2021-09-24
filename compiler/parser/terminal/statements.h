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

    isrtPrsTrm(PARSER_STATEMENTS_RETURN, "", linId);

}

/**
 *  this_statement
 *      : this <SYMBOL>
 *      ;
**/

int isThsStt(int typ, char *val){

    return (typ == LEXER_SYMBOL &&
        strcmp(val, "this") == 0
    );

}

void crtThsStt(int linId){ //Create a this_statement

    isrtPrsTrm(PARSER_STATEMENTS_THIS, "", linId);

}

/**
 *  ref_statement
 *      : refer <SYMBOL>
 *      ;
**/

int isRefStt(int typ, char *val){

    return (typ == LEXER_SYMBOL &&
        strcmp(val, "refer") == 0
    );

}

void crtRefStt(int linId){ //Create a ref_statement

    isrtPrsTrm(PARSER_STATEMENTS_REF, "", linId);

}

/**
 *  delete_statement
 *      : delete <SYMBOL>
 *      ;
**/

int isDelStt(int typ, char *val){

    return (typ == LEXER_SYMBOL &&
        strcmp(val, "delete") == 0
    );

}

void crtDelStt(int linId){ //Create a delete_statement

    isrtPrsTrm(PARSER_STATEMENTS_DELETE, "", linId);

}

/**
 *  setsize_statement
 *      : setsize <SYMBOL>
 *      ;
**/

int isSetSizStt(int typ, char *val){

    return (typ == LEXER_SYMBOL &&
        strcmp(val, "setsize") == 0
    );

}

void crtSetSizStt(int linId){ //Create a setsize_statement

    isrtPrsTrm(PARSER_STATEMENTS_SETSIZE, "", linId);

}

/**
 *  if_statement
 *      : if <SYMBOL>
 *      ;
**/

int isIfStt(int typ, char *val){

    return (typ == LEXER_SYMBOL &&
        strcmp(val, "if") == 0
    );

}

void crtIfStt(int linId){ //Create a if_statement

    isrtPrsTrm(PARSER_STATEMENTS_IF, "", linId);

}

/**
 *  else_statement
 *      : else <SYMBOL>
 *      ;
**/

int isElsStt(int typ, char *val){

    return (typ == LEXER_SYMBOL &&
        strcmp(val, "else") == 0
    );

}

void crtElsStt(int linId){ //Create a else_statement

    isrtPrsTrm(PARSER_STATEMENTS_ELSE, "", linId);

}
