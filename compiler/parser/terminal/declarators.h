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

void crtFncDcl(){ //Create a function_declarator

    isrtPrsTrm("function_declarator", "");

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

void crtGrpDcl(){ //Create a group_declarator

    isrtPrsTrm("group_declarator", "");

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

void crtClsDcl(){ //Create a class_declarator

    isrtPrsTrm("class_declarator", "");

}