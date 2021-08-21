/**
 *  type_specifier
 *      : void <SYMBOL>
 *      | int <SYMBOL>
 *      | double <SYMBOL>
 *      | char <SYMBOL>
 *      | string <SYMBOL>
 *      | bool <SYMBOL>
 *      | file <SYMBOL>
 *      | hex <SYMBOL>
 *      ;
**/

int isTypSpc(int typ, char *val){

    return (typ == LEXER_SYMBOL && (
        strcmp(val, "void") == 0 ||
        strcmp(val, "int") == 0 ||
        strcmp(val, "double") == 0 ||
        strcmp(val, "char") == 0 ||
        strcmp(val, "string") == 0 ||
        strcmp(val, "bool") == 0 ||
        strcmp(val, "file") == 0 ||
        strcmp(val, "hex") == 0
    ));

}

void crtTypSpc(char *val, int linId){ //Create a type_specifier

    isrtPrsTrm(PARSER_SPECIFIERS_TYPE, val, linId);

}

/**
 *  state_specifier
 *      : public <SYMBOL>
 *      | private <SYMBOL>
 *      ;
**/

int isSttSpc(int typ, char *val){

    return (typ == LEXER_SYMBOL && (
        strcmp(val, "public") == 0 ||
        strcmp(val, "private") == 0
    ));

}

void crtSttSpc(char *val, int linId){ //Create a state_specifier

    isrtPrsTrm(PARSER_SPECIFIERS_STATE, val, linId);

}