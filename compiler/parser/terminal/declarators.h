/**
 *  function_declarator
 *      : func <SYMBOL>
 *      ;
**/

int isFncDcl(int typ, char *val){

    return (typ == LEXER_SYMBOL &&
        strcmp(val, WORD_STATEMENT_FUNCTION) == 0
    );

}

void crtFncDcl(int linId){ //Create a function_declarator

    isrtPrsTrm(PARSER_DECLARATORS_FUNCTION, "", linId);

}

/**
 *  variable_declarator
 *      : var <SYMBOL>
 *      ;
**/

int isVarDcl(int typ, char *val){

    return (typ == LEXER_SYMBOL &&
        strcmp(val, WORD_STATEMENT_VARIABLE) == 0
    );

}

void crtVarDcl(int linId){ //Create a variable_declarator

    isrtPrsTrm(PARSER_DECLARATORS_VARIABLE, "", linId);

}

/**
 *  group_declarator
 *      : group <SYMBOL>
 *      ;
**/

int isGrpDcl(int typ, char *val){

    return (typ == LEXER_SYMBOL &&
        strcmp(val, WORD_STATEMENT_GROUP) == 0
    );

}

void crtGrpDcl(int linId){ //Create a group_declarator

    isrtPrsTrm(PARSER_DECLARATORS_GROUP, "", linId);

}

/**
 *  class_declarator
 *      : class <SYMBOL>
 *      ;
**/

int isClsDcl(int typ, char *val){

    return (typ == LEXER_SYMBOL &&
        strcmp(val, WORD_STATEMENT_CLASS) == 0
    );

}

void crtClsDcl(int linId){ //Create a class_declarator

    isrtPrsTrm(PARSER_DECLARATORS_CLASS, "", linId);

}