FileInfo* chkForCom(FileInfo *curFile){

    /* BAD CODE!

    if(SUPPORT_MULTI_LINEAR_COMMENTS && waitForComm)
        writeLogLine("Preprocessor", 0, "Looking for the end of the multi-linear comment that has been detected!", 0, 0, 0);
    else if(SUPPORT_LINEAR_COMMENTS && SUPPORT_MULTI_LINEAR_COMMENTS)
        writeLogLine("Preprocessor", 0, "Checking for comments...", 1, curFile->currLine, curFile->currCol);

    int indx;

    if(SUPPORT_MULTI_LINEAR_COMMENTS && !waitForComm && inStrRng(curFile->currLineCon, "/*")){ //Not working!

        indx = getStrIndx(curFile->currLineCon, "/*");

        writeLogLine("Preprocessor", 0, "A multi-linear comment has been detected!", 1, curFile->currLine, curFile->currCol + indx);

        if(indx == 0){

            //Start a loop to find the end of this comment!
            indx = getStrIndx(curFile->currLineCon, "*\/");

            if(indx != -1){

                curFile->nextCol += indx + 2;
                strcpy(curFile->currLineCon, FILLER_STRING_CHAR_TYP_STR); //Do not insert the current line content into the .tesf file

            }else{

                waitForComm = 1;

            }

        }else{

            curFile->nextCol += indx; //Ignore the comment for now, and check the code before the comment!

            //writeLogLine("DEBUG", 1, curFile->currLineCon, 0, 0, 0);

            curFile->currLineCon = getStrPrt(curFile->currLineCon, 0, indx, 1);

            //writeLogLine("DEBUG", 1, curFile->currLineCon, 0, 0, 0);

        }

    }else if(SUPPORT_MULTI_LINEAR_COMMENTS && waitForComm && inStrRng(curFile->currLineCon, "*\/")){

        indx = getStrIndx(curFile->currLineCon, "*\/");
        curFile->nextCol += indx + 2;

        writeLogLine("Preprocessor", 0, "The end of the multi-linear comment has been detected!", 1, curFile->currLine, curFile->nextCol);

        strcpy(curFile->currLineCon, "");

        waitForComm = 0; //You found the end of the comment, stop!

    }
    */

    int len = strlen(curFile->currLineCon), inStr = 0, inChr = 0;

    for(int i = 0; i < len; i++){

        (curFile->currLineCon)[i]; //Current character

        if((i - 1 != -1) ? ((curFile->currLineCon)[i - 1] != '\\') : 1) { //Look for the '\' char

            if(!inChr && (curFile->currLineCon)[i] == '"') //String opening/closing
                inStr = !inStr;

            if(!inStr && (curFile->currLineCon)[i] == '\'') //Char opening/closing
                inChr = !inChr;

        }

        int shdChk = !inStr && !inChr;

        if(SUPPORT_LINEAR_COMMENTS && shdChk && !waitForComm && i + 1 < len && (curFile->currLineCon)[i] == '/' && (curFile->currLineCon)[i + 1] == '/'){ // a linear comment has been detected!!!

            // Copy everything before this comment to the "curFile->currLineCon" variable

            writeLogLine("Preprocessor", 0, "A single line comment has been detected!", 1, curFile->currLine, curFile->currCol + i);

            if(i == 0)
                strcpy(curFile->currLineCon, FILLER_STRING_CHAR_TYP_STR);
            else{

                char *tmpStr = getStrPrt(curFile->currLineCon, 0, i, 1);

                strcpy(curFile->currLineCon, tmpStr);

                free(tmpStr);

            }

            //There is no need to set a next column value since everything after the linear comment operator will be ignored anyway!

        }

        //

    }

    SUPPORT_MULTI_LINEAR_COMMENTS; //Debug
    SUPPORT_LINEAR_COMMENTS; //Debug
    waitForComm; //Debug

    return curFile;

}