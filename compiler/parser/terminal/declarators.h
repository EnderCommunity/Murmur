/**
 *  function_declarator
 *      : function <SYMBOL>
 *      ;
**/

int isFncDcl(int typ, char *val){

    return (typ == LEXER_SYMBOL &&
        strcmp(val, "function") == 0
    );

}

void crtFncDcl(int linId){ //Create a function_declarator

    isrtPrsTrm(PARSER_DECLARATORS_FUNCTION, "", linId);

}

/**
 *  group_declarator
 *      : group <SYMBOL>
 *      ;
**/

int isGrpDcl(int typ, char *val){

    return (typ == LEXER_SYMBOL &&
        strcmp(val, "group") == 0
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
        strcmp(val, "class") == 0
    );

}

void crtClsDcl(int linId){ //Create a class_declarator

    isrtPrsTrm(PARSER_DECLARATORS_CLASS, "", linId);

}