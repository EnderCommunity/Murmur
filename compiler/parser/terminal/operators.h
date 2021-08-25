/* Repetitive code */
int lokForOneOpr(M_Token tkn, char opr){ //Look for an operator

    return (tkn.typ == LEXER_OPERATOR &&
        tkn.val[0] == opr
    );

}


/**
 *  comparison_operator
 *      : = <OPERATOR>
 *      & = <OPERATOR>
 *      | ! <OPERATOR>
 *      & = <OPERATOR>
 *      | > <OPERATOR>
 *      & = <OPERATOR>
 *      | < <OPERATOR>
 *      & = <OPERATOR>
 *      | > <OPERATOR>
 *      | < <OPERATOR>
 *      ;
**/

int isCmpOpr(M_Token tkn){

    M_Token tmp = lokAhd(); //Get the token ahead

    int subCnd = ((
                    tkn.val[0] == '>' ||
                    tkn.val[0] == '<'
                ) && !(
                    !tkn.defVal3 && !tmp.__ahd_filEnd
                )
            )
        , cnd = (tkn.typ == LEXER_OPERATOR && ((
            tkn.val[0] == '=' ||
            tkn.val[0] == '!' ||
            tkn.val[0] == '>' ||
            tkn.val[0] == '<'
        ) ? (

                /**
                 *  to make sure this is a comparison operator, make sure
                 *  there's no whitespace after the first token.
                **/
                ((!tkn.defVal3 && !tmp.__ahd_filEnd) ? ( //If there is a token after this line, do more checks

                    /**
                     *  also, compare the second operator!
                    **/
                    tmp.val[0] == '='
                ) : (
                    tkn.val[0] == '>' ||
                    tkn.val[0] == '<'
                ))
            ) : (
                (!tkn.defVal3) &&
                (!tmp.__ahd_filEnd) &&
                ((tkn.val[0] == '|') ?
                    (
                        tmp.val[0] == '|'
                    ) : (
                        tkn.val[0] == '&'
                    )
                )
            )
        )
    );

    if(!tmp.__ahd_filEnd) //Not the end of the file
        remTkn(tmp); //Free the token

    if(cnd && !subCnd)
        skpNxt(); //Don't forget to skip the next token

    return cnd;

}

void crtCmpOpr(char *val, int linId){ //Create a comparison_operator

    isrtPrsTrm(PARSER_OPERATORS_COMPARISON, val, linId);

}

/**
 *  end_operator
 *      : ; <OPERATOR>
 *      ;
**/

int isEndOpr(M_Token tkn){

    return lokForOneOpr(tkn, ';');

}

void crtEndOpr(int linId){ //Create a end_operator

    isrtPrsTrm(PARSER_OPERATORS_END, "", linId);

}

/**
 *  maths_operator
 *      : + <OPERATOR>
 *      | - <OPERATOR>
 *      | / <OPERATOR>
 *      | % <OPERATOR>
 *      | * <OPERATOR>
 *      ;
**/

int isMthOpr(M_Token tkn){

    return (tkn.typ == LEXER_OPERATOR && (
        tkn.val[0] == '+' ||
        tkn.val[0] == '-' ||
        tkn.val[0] == '/' ||
        tkn.val[0] == '%' ||
        tkn.val[0] == '*'
        )
    );

}

void crtMthOpr(char *val, int linId){ //Create a addition_operator

    isrtPrsTrm(PARSER_OPERATORS_MATHS, val, linId);

}

/**
 *  assignment_operator
 *      : = <OPERATOR>
 *      | + <OPERATOR>
 *      & = <OPERATOR>
 *      | - <OPERATOR>
 *      & = <OPERATOR>
 *      | / <OPERATOR>
 *      & = <OPERATOR>
 *      | % <OPERATOR>
 *      & = <OPERATOR>
 *      | * <OPERATOR>
 *      & = <OPERATOR>
 *      ;
**/

int isAsiOpr(M_Token tkn){

    M_Token tmp = lokAhd(); //Get the token ahead

    int subCnd = tkn.val[0] == '=',
        cnd = (tkn.typ == LEXER_OPERATOR && (
                subCnd || //If this is an equal, then there's
                                             //no need to check the next token
                (
                    isMthOpr(tkn) &&
                    ((!tmp.__ahd_filEnd) ? ( //If there is a token after this line, do more checks

                        /**
                         *  to make sure this is an assignment operator, make sure
                         *  there's no whitespace after the first token.
                        **/
                        (!(tkn.defVal3)) &&

                        /**
                         *  also, compare the second operator!
                        **/
                        tmp.val[0] == '='
                    ) : 1)
                )
            )
    );

    if(!tmp.__ahd_filEnd) //Not the end of the file
        remTkn(tmp); //Free the token

    if(cnd && !subCnd)
        skpNxt(); //Don't forget to skip the next token

    return cnd;

}

void crtAsiOpr(char *val, int linId){ //Create a assignment_operator

    isrtPrsTrm(PARSER_OPERATORS_ASSIGNMENT, val, linId);

}

/**
 *  zone_operator
 *      : { <OPERATOR>
 *      | } <OPERATOR>
 *      ;
**/

int isZonOpr(M_Token tkn){

    return (tkn.typ == LEXER_OPERATOR && (
            tkn.val[0] == '{' ||
            tkn.val[0] == '}'
        )
    );

}

void crtZonOpr(char *val, int linId){ //Create a zone_operator

    isrtPrsTrm(PARSER_OPERATORS_ZONE, (val[0] == '{') ? PARSER_GENERAL_START : PARSER_GENERAL_END, linId);

}


/**
 *  array_operator
 *      : [ <OPERATOR>
 *      | ] <OPERATOR>
 *      ;
**/

int isArrOpr(M_Token tkn){

    return (tkn.typ == LEXER_OPERATOR && (
            tkn.val[0] == '[' ||
            tkn.val[0] == ']'
        )
    );

}

void crtArrOpr(char *val, int linId){ //Create an array_operator

    isrtPrsTrm(PARSER_OPERATORS_ARRAY, (val[0] == '[') ? PARSER_GENERAL_START : PARSER_GENERAL_END, linId);

}

/**
 *  assignment_short_operator
 *      : + <OPERATOR>
 *      & + <OPERATOR>
 *      | - <OPERATOR>
 *      & - <OPERATOR>
 *      | ! <OPERATOR>
 *      & ! <OPERATOR>
 *      ;
**/

int isAsiShrOpr(M_Token tkn){


    M_Token tmp = lokAhd(); //Get the token ahead

    int cnd = (tkn.typ == LEXER_OPERATOR &&
                !tkn.defVal3 && //There is no whitespace after the first token!
                !tmp.__ahd_filEnd && ( //There is a token after this one!
                    (
                        tkn.val[0] == '+' &&
                        tmp.val[0] == '+'
                    ) || (
                        tkn.val[0] == '-' &&
                        tmp.val[0] == '-'
                    ) || (
                        tkn.val[0] == '!' &&
                        tmp.val[0] == '!'
                    )
                )
    );

    if(!tmp.__ahd_filEnd) //Not the end of the file
        remTkn(tmp); //Free the token

    if(cnd)
        skpNxt(); //Don't forget to skip the next token

    return cnd;

}

void crtAsiShrOpr(char *val, int linId){ //Create a assignment_short_operator

    isrtPrsTrm(PARSER_OPERATORS_ASSIGNMENT_SHORT, val, linId);

}


/**
 *  state_operator
 *      : : <OPERATOR>
 *      & : <OPERATOR>
 *      ;
**/

int isSttOpr(M_Token tkn){


    M_Token tmp = lokAhd(); //Get the token ahead

    int cnd = (tkn.typ == LEXER_OPERATOR &&
                !tkn.defVal3 && //There is no whitespace after the first token!
                !tmp.__ahd_filEnd && ( //There is a token after this one!
                    tkn.val[0] == ':' &&
                    tmp.val[0] == ':'
                )
    );

    if(!tmp.__ahd_filEnd) //Not the end of the file
        remTkn(tmp); //Free the token

    if(cnd)
        skpNxt(); //Don't forget to skip the next token

    return cnd;

}

void crtSttOpr(int linId){ //Create a state_operator

    isrtPrsTrm(PARSER_OPERATORS_STATE, "", linId);

}

/**
 *  info_operator
 *      : : <OPERATOR>
 *      ;
**/

int isInfOpr(M_Token tkn){

    return lokForOneOpr(tkn, ':');

}

void crtInfOpr(int linId){ //Create an info_operator

    isrtPrsTrm(PARSER_OPERATORS_INFO, "", linId);

}

/**
 *  negative_operator
 *      : < <OPERATOR>
 *      ;
**/

int isNgtOpr(M_Token tkn){

    return lokForOneOpr(tkn, '!');

}

void crtNgtOpr(int linId){ //Create a negative_operator

    isrtPrsTrm(PARSER_OPERATORS_NEGATIVE, "", linId);

}

/**
 *  parentheses_operator
 *      : ( <OPERATOR>
 *      | ) <OPERATOR>
 *      ;
**/

int isPrnOpr(M_Token tkn){

    return (tkn.typ == LEXER_OPERATOR &&
        tkn.val[0] == '(' ||
        tkn.val[0] == ')'
    );

}

void crtPrnOpr(char *val, int linId){ //Create a parentheses_operator

    isrtPrsTrm(PARSER_OPERATORS_PARENTHESES, (val[0] == '(') ? PARSER_GENERAL_START : PARSER_GENERAL_END, linId);

}

/**
 *  separation_operator
 *      : , <OPERATOR>
 *      ;
**/

int isSprOpr(M_Token tkn){

    return lokForOneOpr(tkn, ',');

}

void crtSprOpr(int linId){ //Create a separation_operator

    isrtPrsTrm(PARSER_OPERATORS_SEPARATION, "", linId);

}

/**
 *  dot_operator
 *      : . <OPERATOR>
 *      ;
**/

int isDotOpr(M_Token tkn){

    return lokForOneOpr(tkn, '.');

}

void crtDotOpr(int linId){ //Create a dot_operator

    isrtPrsTrm(PARSER_OPERATORS_DOT, "", linId);

}