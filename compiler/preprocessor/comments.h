FileInfo* chkForCom(FileInfo *curFile){

    if(SUPPORT_MULTI_LINEAR_COMMENTS && waitForComm)
        writeLogLine("Preprocessor", 0, "Looking for the end of the multi-linear comment that has been detected!", 0, 0, 0);
    else if(SUPPORT_LINEAR_COMMENTS && SUPPORT_MULTI_LINEAR_COMMENTS)
        writeLogLine("Preprocessor", 0, "Checking for comments...", 1, curFile->currLine, curFile->currCol);

    int indx;

    if(SUPPORT_LINEAR_COMMENTS && !waitForComm && inStrRng(curFile->currLineCon, "//")){ //Working (DO NOT TOUCH!)

        indx = getStrIndx(curFile->currLineCon, "//");

        writeLogLine("Preprocessor", 0, "A single line comment has been detected!", 1, curFile->currLine, curFile->currCol + indx);

        if(indx == 0)
            strcpy(curFile->currLineCon, FILLER_STRING_CHAR_TYP_STR);
        else
            curFile->currLineCon = getStrPrt(curFile->currLineCon, 0, indx, 1);

        //There is no need to set a next column value since everything after the linear comment operator will be ignored anyway!

    }else if(SUPPORT_MULTI_LINEAR_COMMENTS && !waitForComm && inStrRng(curFile->currLineCon, "/*")){ //Not working!

        indx = getStrIndx(curFile->currLineCon, "/*");

        writeLogLine("Preprocessor", 0, "A multi-linear comment has been detected!", 1, curFile->currLine, curFile->currCol + indx);

        if(indx == 0){

            //Start a loop to find the end of this comment!
            indx = getStrIndx(curFile->currLineCon, "*/");

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

    }else if(SUPPORT_MULTI_LINEAR_COMMENTS && waitForComm && inStrRng(curFile->currLineCon, "*/")){

        indx = getStrIndx(curFile->currLineCon, "*/");
        curFile->nextCol += indx + 2;

        writeLogLine("Preprocessor", 0, "The end of the multi-linear comment has been detected!", 1, curFile->currLine, curFile->nextCol);

        strcpy(curFile->currLineCon, "");

        waitForComm = 0; //You found the end of the comment, stop!

    }

    return curFile;

}