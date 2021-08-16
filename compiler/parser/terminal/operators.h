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
