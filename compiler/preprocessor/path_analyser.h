#include <unistd.h>

char *pthAnl(char *rootPth, char *pth){

    int len = strlen(pth), shdLnk = -1;

    for(int i = 0; i < len; i++){ //Make the path more consistant with the system

        if(PATH_SLASH_TYP_CHAR == '\\' && pth[i] == '/')
            pth[i] = '\\';

        if(PATH_SLASH_TYP_CHAR == '/' && pth[i] == '\\')
            pth[i] = '/';

    }

    for(int i = 0; i < len; i++){

        if(!isspace(pth[i])) {

            if(pth[i] != '/' || pth[i] != '\\'){ //This path is pointing to the drive root!

                shdLnk = i;

            }

            break;

        }

    }

    char *fnlPth;

    if(shdLnk == -1){

        fnlPth = malloc(sizeof(char)*(len + 1));

        strcpy(fnlPth, pth);

    }else{

        int tmpLen = strlen(rootPth), tmpCon = (rootPth[tmpLen - 1] == '/' || rootPth[tmpLen - 1] == '\\');

        fnlPth = malloc(sizeof(char)*(len - shdLnk + ((tmpCon) ? tmpLen : tmpLen + 1) + 1));

        sprintf(fnlPth, (tmpCon) ? "%s%s" : "%s/%s", rootPth, pth);

    }

    //printf("\n%s", fnlPth);

    return fnlPth;

    /*if(access(fnlPth, F_OK) == 0){

        return fnlPth;

    }else{

        char *tmpMsg = malloc(sizeof(char)*(65 + strlen(fnlPth) + 1));

        sprintf(tmpMsg, "There was an attempt to access the file <%s>, which does not exist!", fnlPth);

        writeLogLine("Preprocessor", 0, tmpMsg, 0, 0, 0);

        free(tmpMsg);

        exit(-1); //File does not exist!

    }*/

}