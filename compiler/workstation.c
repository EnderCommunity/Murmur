struct workstation {
    char *Path;
    char *Name;
};

struct workstation wrkstn;

void setupWrkstn(char *filPth){ //Setup the workstation

    //Get the workstation path
    int indx = getLstStrIndx(filPth, PATH_SLASH);

    wrkstn.Path = getStrPrt(filPth, 0, indx, 0);

    //Get the file name
    //wrkstn.Name = newStr(MAX_FILE_NAME_LENGTH);
    wrkstn.Name = getStrPrt(filPth, indx + 1, strlen(filPth), 0);
    wrkstn.Name = getStrPrt(wrkstn.Name, 0, getLstStrIndx(wrkstn.Name, ".") - 1, 0);

}

void endWrkstn(){ //End the workstation
    //
}