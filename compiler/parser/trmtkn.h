typedef struct {

    char *val; // The component line value

    int srcLin; // The source lin of the token from the `.lixc` file 
    char *nam; // The component name
    char *cnt; // The component content;

    int __prevLinPtr; // The pointer of the previous line
    int __ahd_filEnd; // Did you reach the file end?
    int __alwLopTwc; // Allow this token to be processed twice

} T_Comp; // A terminal component

int kepLopTrm = 1, curTrmZon = 0;
FILE *trmCmpFilPtr = NULL;

void rdTrmCmpFil(char *pth){

    trmCmpFilPtr = fopen(pth, "r");
    free(pth);

    if(prsFilPtr == NULL){

        exit(-100);

    }

}

void clsTrmCmpFil(){ //Close the parser file

    fclose(trmCmpFilPtr);

}

T_Comp getTrmCmp(){ //Get a terminal component

    T_Comp tmp;

    tmp.val = malloc(sizeof(char)*(MAX_LINE_LENGTH + 1));

    tmp.__prevLinPtr = ftell(trmCmpFilPtr);
    tmp.__ahd_filEnd = 0;
    tmp.__alwLopTwc = 0;

    fgets(tmp.val, MAX_LINE_LENGTH, trmCmpFilPtr);

    kepLopTrm = !feof(trmCmpFilPtr);

    if(kepLopTrm){

        if(tmp.val[strlen(tmp.val) - 1] == '\n')
            tmp.val[strlen(tmp.val) - 1] = '\0'; //Remove the new line character (\n), and replace it with a line end character (\0)!
        
        char *tmpStr = getStrSec(tmp.val, "<", ">");

        tmp.srcLin = atoi(tmpStr);

        free(tmpStr);

        tmp.nam = getStrPrt(tmp.val, 0, getStrIndx(tmp.val, "("), 0);
        tmp.cnt = getStrPrt(tmp.val, getStrIndx(tmp.val, "(") + 1, getStrIndx(tmp.val, ")"), 0);

        if(strcmp(tmp.nam, PARSER_OPERATORS_ZONE) == 0)
            (strcmp(tmp.cnt, PARSER_GENERAL_START) == 0) ? curTrmZon++ : curTrmZon--;

    }

    free(tmp.val);

    return tmp;

}

T_Comp remTrmCmp(T_Comp cmp){ //Remove terminal component

    free(cmp.nam);
    free(cmp.cnt);

}

T_Comp lokAhdTrm(){ //Look ahead!

    unsigned int curPos = ftell(trmCmpFilPtr); //Save the current [position]

    T_Comp tmp = getTrmCmp(); //Get the token next to the current one

    if(!kepLop)
        tmp.__ahd_filEnd = 1;

    fseek(trmCmpFilPtr, curPos, SEEK_SET); //Go back

    return tmp;

}

T_Comp cpyCmp(T_Comp cmp){ //Skip the next token!

    T_Comp tmp;

    tmp.srcLin = cmp.srcLin;
    tmp.__ahd_filEnd = cmp.__ahd_filEnd;

    tmp.nam = malloc(sizeof(char)*(strlen(cmp.nam) + 1));
    tmp.cnt = malloc(sizeof(char)*(strlen(cmp.cnt) + 1));

    strcpy(tmp.nam, cmp.nam);
    strcpy(tmp.cnt, cmp.cnt);

    return tmp;

}

void skpNxtCmp(){ //Skip the next token!

    remTrmCmp(getTrmCmp());//Remove the token

}

int nxtTknCmp(T_Comp *cmp){

    if(!(*cmp).__alwLopTwc){

        T_Comp tmp = cpyCmp(*cmp);

        remTrmCmp(*cmp); //Remove the token

        *cmp = getTrmCmp(); //get a new token

        if(kepLopTrm)
            remTrmCmp(tmp);
        else
            *cmp = tmp;

    }else
        (*cmp).__alwLopTwc = 0;

    return kepLopTrm;

}

int prvTknCmp(T_Comp *cmp){

    unsigned int tmp = cmp->__prevLinPtr;

    fseek(trmCmpFilPtr, tmp, SEEK_SET); //Go back
    remTrmCmp(*cmp); //Remove the token

    *cmp = getTrmCmp(); //get a new token

    fseek(trmCmpFilPtr, tmp, SEEK_SET); //Go back

    return kepLopTrm;

}

int prcCmpTwc(T_Comp *cmp){

    (*cmp).__alwLopTwc = 1;

}