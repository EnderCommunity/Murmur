FILE *lexFilPtr;
int kepLop = 1;
int prsTknCurLin = 0; //The current line in the file

void setTknFilPtr(FILE *tmp){

    lexFilPtr = tmp;

}

void remTkn(M_Token tmp){ //Free allocated memory

    free(tmp.val);
    free(tmp.srcFil);

}

M_Token getTkn(){ //Get a token

    M_Token tmp; // A lexer token

    char *val = malloc(sizeof(char)*(MAX_LINE_LENGTH + 1));

    fgets(val, MAX_LINE_LENGTH, lexFilPtr);

    kepLop = !feof(lexFilPtr);

    if(kepLop){

        prsTknCurLin++;

        tmp = rtrLxrDat(val, prsTknCurLin);

    }

    free(val);

    return tmp;

}

M_Token lokAhd(){ //Look ahead!

    unsigned int curPos = ftell(lexFilPtr); //Save the current [position]

    M_Token tmp = getTkn(); //Get the token next to the current one

    if(!kepLop)
        tmp.__ahd_filEnd = 1;

    fseek(lexFilPtr, curPos, SEEK_SET); //Go back
    prsTknCurLin--;

    return tmp;

}

void skpNxt(){ //Skip the next token!

    remTkn(getTkn());//Remove the token

}

void nxtTkn(M_Token *tkn){

    remTkn(*tkn); //Remove the token

    *tkn = getTkn(); //get a new token

}