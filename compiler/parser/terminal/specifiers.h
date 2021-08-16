/**
 *  type_specifier
 *      : int <SYMBOL>
 *      | double <SYMBOL>
 *      | char <SYMBOL>
 *      | string <SYMBOL>
 *      | bool <SYMBOL>
 *      | file <SYMBOL>
 *      ;
**/

int isTypSpc(int typ, char *val){

    return (typ == LEXER_SYMBOL && (
        strcmp(val, "int") == 0 ||
        strcmp(val, "double") == 0 ||
        strcmp(val, "char") == 0 ||
        strcmp(val, "string") == 0 ||
        strcmp(val, "bool") == 0 ||
        strcmp(val, "file") == 0
    ));

}

void crtTypSpc(char *val){ //Create a type_specifier

    isrtPrsTrm("type_specifier", val);

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

void crtSttSpc(char *val){ //Create a state_specifier

    isrtPrsTrm("state_specifier", val);

}