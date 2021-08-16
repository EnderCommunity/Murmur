/**
 *  assignment_operator
 *      : = <OPERATOR>
 *      ;
**/

int isAsiOpr(M_Token tkn){

    M_Token tmp = lokAhd(); //Get the token ahead

    //tmp.defVal3; //Is there whitespace after this token?

    int cnd = (tkn.typ == LEXER_OPERATOR &&
        strcmp(tkn.val, "=") == 0 &&
        ((!tmp.__ahd_filEnd) ? ( //If there is a token after this line, do more checks

            /**
             *  to make sure this is an assignment operator, make sure
             *  there's whitespace after the first token.
            **/
            (tkn.defVal3) ||

            /**
             *  if there isn't space, make sure no other operators are
             *  present after this one in the same line.
            **/
            (!(tmp.defVal3) && (
                tmp.typ != LEXER_OPERATOR || //THis token is not an operator
                tmp.defVal1 //This token is not in the same line
            ))
        ) : 1)
    );

    if(!tmp.__ahd_filEnd) //Not the end of the file
        remTkn(tmp); //Free the token

    return cnd;

}

void crtAsiOpr(int linId){ //Create an assignment_operator

    isrtPrsTrm("assignment_operator", "", linId);

}

/**
 *  comparison_operator
 *      : = <OPERATOR>
 *      & = <OPERATOR>
 *      ;
**/

int isCmpOpr(M_Token tkn){

    M_Token tmp = lokAhd(); //Get the token ahead

    int cnd = (tkn.typ == LEXER_OPERATOR &&
        strcmp(tkn.val, "=") == 0 &&
        ((!tmp.__ahd_filEnd) ? ( //If there is a token after this line, do more checks

            /**
             *  to make sure this is a comparison operator, make sure
             *  there's no whitespace after the first token.
            **/
            (!(tkn.defVal3)) &&

            /**
             *  also, compare the second operator!
            **/
            strcmp(tmp.val, "=") == 0
        ) : 0)
    );

    if(!tmp.__ahd_filEnd) //Not the end of the file
        remTkn(tmp); //Free the token

    if(cnd)
        skpNxt(); //Don't forget to skip the next token

    return cnd;

}

void crtCmpOpr(int linId){ //Create a comparison_operator

    isrtPrsTrm("comparison_operator", "", linId);

}
