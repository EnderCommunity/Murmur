struct workstation {
    char *Path;
    char *Name;
};

struct workstation wrkstn;

void setupWrkstn(char *filPth){ //Setup the workstation

    //Debug [done - fixed]
    /*int test = getLstStrIndx("...hehehehehe, hi!", "he"),
        test2 = getStrIndx("...hehehehehe, hi!", "he");
    printf("\n%d, `%c`", test, "...hehehehehe, hi!"[test]);
    printf("\n%d, `%c`", test2, "...hehehehehe, hi!"[test2]);*/
    //getStrPrt(filPth, 0, test, 0);


    //Get the workstation path
    //printf("1");
    int indx = getLstStrIndx(filPth, PATH_SLASH);

    //printf("2");
    wrkstn.Path = getStrPrt(filPth, 0, indx, 0);

    //Get the file name
    //wrkstn.Name = newStr(MAX_FILE_NAME_LENGTH);
    //wrkstn.Name = getStrPrt(filPth, indx + 1, strlen(filPth), 0);
    //wrkstn.Name = getStrPrt(wrkstn.Name, 0, getLstStrIndx(wrkstn.Name, ".") - 1, 0);
    //printf("3");
    wrkstn.Name = getStrPrt(filPth, indx, strlen(filPth), 0);
    //printf("4");
    wrkstn.Name = getStrPrt(wrkstn.Name, 0, getLstStrIndx(wrkstn.Name, "."), 0);

}

void endWrkstn(){ //End the workstation
    //
}