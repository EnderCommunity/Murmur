
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

        sprintf(fnlPth, "%s%s%s", rootPth, (tmpCon) ? "" : PATH_SLASH, pth);

    }

    return fnlPth;

}