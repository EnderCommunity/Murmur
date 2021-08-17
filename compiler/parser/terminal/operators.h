/* Repetitive code */
int lokForTwoOprStk(M_Token tkn, char *fstOpr, char *sndOpr){ //Look for two operators that are next to each other with no whitespace in between

    M_Token tmp = lokAhd(); //Get the token ahead

    int cnd = (tkn.typ == LEXER_OPERATOR &&
        strcmp(tkn.val, fstOpr) == 0 &&
        ((!tmp.__ahd_filEnd) ? ( //If there is a token after this line, do more checks

            /**
             *  to make sure this is the desired sequence, make sure
             *  there's no whitespace after the first token.
            **/
            (!(tkn.defVal3)) &&

            /**
             *  also, compare the second operator!
            **/
            strcmp(tmp.val, sndOpr) == 0
        ) : 0)
    );

    if(!tmp.__ahd_filEnd) //Not the end of the file
        remTkn(tmp); //Free the token

    if(cnd)
        skpNxt(); //Don't forget to skip the next token

    return cnd;

}

int lokForOneOpr(M_Token tkn, char *opr){ //Look for an operator

    return (tkn.typ == LEXER_OPERATOR &&
        strcmp(tkn.val, opr) == 0 
    );;

}


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

    /*M_Token tmp = lokAhd(); //Get the token ahead

    int cnd = (tkn.typ == LEXER_OPERATOR &&
        strcmp(tkn.val, "=") == 0 &&
        ((!tmp.__ahd_filEnd) ? ( //If there is a token after this line, do more checks

            /**
             *  to make sure this is a comparison operator, make sure
             *  there's no whitespace after the first token.
            **\/
            (!(tkn.defVal3)) &&

            /**
             *  also, compare the second operator!
            **\/
            strcmp(tmp.val, "=") == 0
        ) : 0)
    );

    if(!tmp.__ahd_filEnd) //Not the end of the file
        remTkn(tmp); //Free the token

    if(cnd)
        skpNxt(); //Don't forget to skip the next token
    */

    return lokForTwoOprStk(tkn, "=", "=");

}

void crtCmpOpr(int linId){ //Create a comparison_operator

    isrtPrsTrm("comparison_operator", "", linId);

}

/**
 *  negative_comparison_operator
 *      : ! <OPERATOR>
 *      & = <OPERATOR>
 *      ;
**/

int isNegCmpOpr(M_Token tkn){

    /*M_Token tmp = lokAhd(); //Get the token ahead

    int cnd = (tkn.typ == LEXER_OPERATOR &&
        strcmp(tkn.val, "!") == 0 &&
        ((!tmp.__ahd_filEnd) ? ( //If there is a token after this line, do more checks

            /**
             *  to make sure this is a negative comparison operator, make sure
             *  there's no whitespace after the first token.
            **\/
            (!(tkn.defVal3)) &&

            /**
             *  also, compare the second operator!
            **\/
            strcmp(tmp.val, "=") == 0
        ) : 0)
    );

    if(!tmp.__ahd_filEnd) //Not the end of the file
        remTkn(tmp); //Free the token

    if(cnd)
        skpNxt(); //Don't forget to skip the next token
    */

    return lokForTwoOprStk(tkn, "!", "=");

}

void crtNegCmpOpr(int linId){ //Create a negative_comparison_operator

    isrtPrsTrm("negative_comparison_operator", "", linId);

}

/**
 *  greater_equal_comparison_operator
 *      : > <OPERATOR>
 *      & = <OPERATOR>
 *      ;
**/

int isGrtEqlCmpOpr(M_Token tkn){

    return lokForTwoOprStk(tkn, ">", "=");

}

void crtGrtEqlCmpOpr(int linId){ //Create a greater_equal_comparison_operator

    isrtPrsTrm("greater_equal_comparison_operator", "", linId);

}

/**
 *  smaller_equal_comparison_operator
 *      : < <OPERATOR>
 *      & = <OPERATOR>
 *      ;
**/

int isSmlEqlCmpOpr(M_Token tkn){

    return lokForTwoOprStk(tkn, "<", "=");

}

void crtSmlEqlCmpOpr(int linId){ //Create a smaller_equal_comparison_operator

    isrtPrsTrm("smaller_equal_comparison_operator", "", linId);

}

/**
 *  greater_comparison_operator
 *      : > <OPERATOR>
 *      ;
**/

int isGrtCmpOpr(M_Token tkn){

    return lokForOneOpr(tkn, ">");

}

void crtGrtCmpOpr(int linId){ //Create a greater_comparison_operator

    isrtPrsTrm("greater_comparison_operator", "", linId);

}

/**
 *  smaller_comparison_operator
 *      : < <OPERATOR>
 *      ;
**/

int isSmlCmpOpr(M_Token tkn){

    return lokForOneOpr(tkn, "<");

}

void crtSmlCmpOpr(int linId){ //Create a smaller_comparison_operator

    isrtPrsTrm("smaller_comparison_operator", "", linId);

}
