/**
 *  type_specifier
 *      : void <SYMBOL>
 *      | int <SYMBOL>
 *      | double <SYMBOL>
 *      | float <SYMBOL>
 *      | char <SYMBOL>
 *      | string <SYMBOL>
 *      | bool <SYMBOL>
 *      | file <SYMBOL>
 *      | hex <SYMBOL>
 *      ;
**/

int isTypSpc(M_Token tkn){

    M_Token tmp = lokAhd(); //Get the token ahead

    char *val;
    int isElv = 0, cndEsc = 1;

    if(tkn.typ == LEXER_OPERATOR && tkn.val[0] == '^' && tmp.typ == LEXER_SYMBOL){

        val = tmp.val;
        isElv = 1;

    }else if(tkn.typ == LEXER_SYMBOL){

        val = tkn.val;

    }else
        cndEsc = 0;
    
    int cnd =  (cndEsc && (
        strcmp(val, "void") == 0 ||
        strcmp(val, "int") == 0 ||
        strcmp(val, "double") == 0 ||
        strcmp(val, "float") == 0 ||
        strcmp(val, "char") == 0 ||
        strcmp(val, "string") == 0 ||
        strcmp(val, "bool") == 0 ||
        strcmp(val, "file") == 0 ||
        strcmp(val, "hex") == 0
    ));

    if(!tmp.__ahd_filEnd) //Not the end of the file
        remTkn(tmp); //Free the token

    return cnd;

}

void crtTypSpc(M_Token tkn){ //Create a type_specifier

    char *tmpStr;

    if(tkn.typ == LEXER_OPERATOR){

        M_Token tmp = lokAhd(); //Get the token ahead

        tmpStr = malloc(sizeof(char)*(strlen(tmp.val) + 2));

        sprintf(tmpStr, "^%s", tmp.val);

        remTkn(tmp); //Free the token

        skpNxt(); //Don't forget to skip the next token

    }else{

        tmpStr = malloc(sizeof(char)*(strlen(tkn.val) + 1));
        sprintf(tmpStr, "%s", tkn.val);

    }

    M_Token tmp = lokAhd(); //Get the token ahead

    if(tmp.typ == LEXER_OPERATOR && tmp.val[0] == '['){

        remTkn(tmp);
        skpNxt();
        int q = 1;

        tmp = lokAhd();

        while(!tmp.__ahd_filEnd && tmp.typ == LEXER_OPERATOR && tmp.val[0] == ','){

            q++;

            remTkn(tmp);
            skpNxt();
            tmp = lokAhd();

        }

        if(!(tmp.typ == LEXER_OPERATOR && tmp.val[0] == ']')){

            Inf_Token tmpInf = getLxrInfTkn(tmp.srcLin);

            rpt(REPORT_CODE_ERROR, //This is an error
            REPORT_SECTION_PARSER, //The error was detected by the preprocessor
            MSG_PRS_TRM_SPC_ARRAYDEFFNOTCLOSED, //This is the custom error message (check /compiler/errors/messages.h)
            tmpInf.src, //The source of this error
            tmpInf.lin, //The line of this error
            tmpInf.col); //The column the error occurs

            delLxrInfTkn(tmpInf);

        }

        remTkn(tmp);
        skpNxt();

        int len = numLen(q) + 2;
        tmpStr = realloc(tmpStr, sizeof(char)*(strlen(tmpStr) + len + 1));
        char *tmpStr2 = malloc(sizeof(char)*(strlen(tmpStr) + len + 1));

        sprintf(tmpStr2, "%s[%d]", tmpStr, q);

        strcpy(tmpStr, tmpStr2);
        free(tmpStr2);

    }else
        remTkn(tmp);

    isrtPrsTrm(PARSER_SPECIFIERS_TYPE, tmpStr, tkn.__srcLin);

    free(tmpStr);

}

/**
 *  state_specifier
 *      : public <SYMBOL>
 *      | private <SYMBOL>
 *      ;
**/

int isSttSpc(int typ, char *val){

    return (typ == LEXER_SYMBOL && (
        strcmp(val, WORD_STATE_PUBLIC) == 0 ||
        strcmp(val, WORD_STATE_PRIVATE) == 0
    ));

}

void crtSttSpc(char *val, int linId){ //Create a state_specifier

    isrtPrsTrm(PARSER_SPECIFIERS_STATE, val, linId);

}