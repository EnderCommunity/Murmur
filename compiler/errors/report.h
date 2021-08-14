#include <math.h>

FILE *rptFilPtr;

void opnRptFil(){

    char *tmpPth = malloc(sizeof(char)*(strlen(wrkstn.Path) + strlen(wrkstn.Name) + 6));

    sprintf(tmpPth, "%s%c%s.opf", wrkstn.Path, PATH_SLASH_TYP_CHAR, wrkstn.Name);

    rptFilPtr = fopen(tmpPth, "w"); //Create a new data file in "write mode"

    free(tmpPth);

}

void clsRptFil(){

    fclose(rptFilPtr);

}

//char *crt;

void srtRptSrc(char **src){

    int tmpIndx = getStrIndx(*src, "@"), siz = 1;
    char *tmp = malloc(sizeof(char)*siz);

    tmp[0] = '\0';

    if(tmpIndx == -1){

        siz += strlen(*src) + 5;
        tmp = realloc(tmp, sizeof(char)*siz);

        sprintf(tmp, "\n    %s", *src);

    }else{

        do{

            tmpIndx = getStrIndx(*src, "@");

            char *tmpStr = getStrPrt(*src, 0, ((tmpIndx == -1) ? strlen(*src) : tmpIndx), 0);

            siz += strlen(tmpStr) + 6;
            tmp = realloc(tmp, sizeof(char)*siz);

            sprintf(tmp, "%s\n    %s%c", tmp, tmpStr, (tmpIndx == -1) ? ' ' : '@');

            *src = getStrPrt(*src, tmpIndx + 1, strlen(*src), 0);

            /*siz += 4;

            sprintf(tmp, "%s\n    %s", tmp, tmpStr);

            free(tmpStr);*/

        }while(tmpIndx != -1);

    }
    
    *src = tmp;

}

void rpt(const int typ, int sct, char *msg, char *src){

    srtRptSrc(&src);

    fprintf(rptFilPtr, "[%s] %s%s\n", (typ == REPORT_CODE_WARNING) ? "Warning" : ((typ == REPORT_CODE_MESSAGE) ?  "Message" : "Error")
                             , msg
                             , src);

    if(typ == REPORT_CODE_ERROR){

        clsRptFil();

        //exit(-sct*100);

    }

}

/*
    rpt(REPORT_CODE_ERROR);
    rpt(REPORT_CODE_WARNING);
    rpt(REPORT_CODE_MESSAGE);

#define REPORT_SECTION_GENERAL 1
#define REPORT_SECTION_PREPROCESSOR 2
#define REPORT_SECTION_LEXER 3
#define REPORT_SECTION_PARSER 4
#define REPORT_SECTION_OPTIMISER 5
#define REPORT_SECTION_EVALUATOR 6
#define REPORT_SECTION_BUNDLER 7
#define REPORT_SECTION_C 8
#define REPORT_SECTION_RUNTIME 9

*/