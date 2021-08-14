typedef struct {
    FILE *ptr;
    FILE *strPtr;
    char *pth;
    int maxId;
} datCtr;

datCtr tmpDatCtr;

void crtDatFil(){

    tmpDatCtr.pth = malloc(sizeof(char)*(strlen(wrkstn.Path) + strlen(wrkstn.Name) + 6));

    sprintf(tmpDatCtr.pth, "%s%c%s.dat", wrkstn.Path, PATH_SLASH_TYP_CHAR, wrkstn.Name);

    tmpDatCtr.ptr = fopen(tmpDatCtr.pth, "w"); //Create a new data file in "write mode"
    fclose(tmpDatCtr.ptr);
    tmpDatCtr.ptr = fopen(tmpDatCtr.pth, "a+"); //Create a new data file in "write mode"

    tmpDatCtr.maxId = 0;

}

void freeDatFil(){

    free(tmpDatCtr.pth);

}

int savDat(char typ, char *dat){

    (tmpDatCtr.maxId)++;

    fprintf(tmpDatCtr.ptr, "%cx%06X %s\n", typ, tmpDatCtr.maxId, dat);

    return tmpDatCtr.maxId;

}

char *getDat(char typ, int id){

    char *lin = malloc(sizeof(char)*(MAX_LINE_LENGTH + 1));

    fseek(tmpDatCtr.ptr, 0, SEEK_SET); //Go to the start of the file!

    fgets(lin, MAX_LINE_LENGTH, tmpDatCtr.ptr);

    if(lin[strlen(lin) - 1] == '\n')
        lin[strlen(lin) - 1] = '\0';

    char *dat;
    int fnd = 0, wait = 1, keepLoop = 1;

    do{

        if(lin[0] == typ){

            char *tmp = getStrPrt(lin, 2, 8, 0);
            int tmpId = hexToInt(tmp);

            if(tmpId == id){

                fnd = 1;
                dat = getStrPrt(lin, 9, strlen(lin), 0);

            }

        }

        if(keepLoop){

            fgets(lin, MAX_LINE_LENGTH, tmpDatCtr.ptr);

            if(lin[strlen(lin) - 1] == '\n')
                lin[strlen(lin) - 1] = '\0';

            if(wait)
                keepLoop = !feof(tmpDatCtr.ptr);

            if(!wait)
                keepLoop = 0;

            if(!keepLoop && wait){
                keepLoop = 1;
                wait = 0;
            }

        }

    }while(!fnd && keepLoop);

    fseek(tmpDatCtr.ptr, 0, SEEK_END); //Go to the end of the file
    free(lin);

    return (fnd) ? dat : "\0";

}

void clsDatFil(){

    fprintf(tmpDatCtr.ptr, "#");
    fclose(tmpDatCtr.ptr);
    tmpDatCtr.ptr = NULL;

}

/*
000000      100          
^ Data ID   ^ Data type  ^ The data
*/