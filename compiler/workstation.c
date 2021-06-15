struct workstation {
    char *Path;
    char *Name;
};

struct workstation wrkstn;

void setupWrkstn(char *filPth){ //Setup the workstation

    //Get the index of the the last slash
    int indx = getLstStrIndx(filPth, PATH_SLASH);

    //Get the workstation path
    wrkstn.Path = getStrPrt(filPth, 0, indx + 1, 0);

    //The workstation name should follow the file name
    wrkstn.Name = getStrPrt(filPth, indx + 1, strlen(filPth), 0);
    wrkstn.Name = getStrPrt(wrkstn.Name, 0, getLstStrIndx(wrkstn.Name, "."), 0);

}

void endWrkstn(){ //End the workstation
    //
}