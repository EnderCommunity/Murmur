typedef struct {
    char *src;
    int lin;
    int col;
} Inf_Token;

Inf_Token getLxrInfTkn(int srcLin){

    Inf_Token tmp;

    unsigned int prvPos = ftell(lexFilPtr); //Save the current [position]

    fseek(lexFilPtr, lexFilFstPos, SEEK_SET); //Go to the start

    int linNum = 1;
    char *lin = malloc(sizeof(char)*(
        MAX_LINE_LENGTH +
        1
    ));

    for(char c = fgetc(lexFilPtr); c != EOF; c = fgetc(lexFilPtr)){

        if(c == '\n')
            linNum++;

        if(linNum == srcLin){

            fgets(lin, MAX_LINE_LENGTH, lexFilPtr);

            break;

        }

    }

    M_Token tmpM = rtrLxrDat(lin, srcLin);

    free(lin);

    tmp.src = malloc(sizeof(char)*(strlen(tmpM.srcFil) + 1));
    strcpy(tmp.src, tmpM.srcFil);
    tmp.lin = tmpM.srcLin;
    tmp.col = tmpM.srcCol;

    remTkn(tmpM);

    fseek(lexFilPtr, prvPos, SEEK_SET); //Go back

    return tmp;

}

void delLxrInfTkn(Inf_Token tmp){

    free(tmp.src);

}