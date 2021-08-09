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

    int len = strlen(curFile->currLineCon) - END_OF_LINE_COUNT, inStr = 0, inChr = 0;

    for(int i = 0; i < len; i++){

        //(curFile->currLineCon)[i]; //Current character

        if((i - 1 != -1) ? ((curFile->currLineCon)[i - 1] != '\\') : 1) { //Look for the '\' char

            if(!inChr && (curFile->currLineCon)[i] == '"') //String opening/closing
                inStr = !inStr;

            if(!inStr && (curFile->currLineCon)[i] == '\'') //Char opening/closing
                inChr = !inChr;

        }

        int shdChk = !inStr && !inChr;

        if(SUPPORT_LINEAR_COMMENTS && !waitForComm && shdChk && i + 1 != len && (curFile->currLineCon)[i] == '/' && (curFile->currLineCon)[i + 1] == '/'){ // a linear comment has been detected!!!

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
            i = len;

        }else if(SUPPORT_MULTI_LINEAR_COMMENTS && ((shdChk && !waitForComm && i + 1 != len && (curFile->currLineCon)[i] == '/' && (curFile->currLineCon)[i + 1] == '*') || (waitForComm && inStrRng(curFile->currLineCon, "*/")))){ // a multi-linear comment has been detected!!!

            if(!waitForComm)
                writeLogLine("Preprocessor", 0, "A multi-linear comment has been detected!", 1, curFile->currLine, curFile->currCol + i);

            int tmpIndx = getStrIndx(curFile->currLineCon, "*/"), tmpIndx2 = getLstStrIndx(curFile->currLineCon, "*/");

            if(i == 0 || waitForComm){

                if(!waitForComm && tmpIndx == -1){ //The end of this comment is not in this line!

                    waitForComm = 1; //Start looking for the end of this comment!

                    i = len;

                    //                  "tmpIndx != tmpIndx2" IS NOT WORKING!
                }else if(waitForComm || (tmpIndx > 1 || tmpIndx != tmpIndx2)){ //The end of this comment is in this line!
                           //^ You don't want the case "/*/" to trigger this!

                    int indx;
                    
                    if(waitForComm || tmpIndx > 1)
                        indx = tmpIndx;
                    else
                        indx = tmpIndx2;

                    writeLogLine("Preprocessor", 0, "The end of the multi-linear comment has been detected!", 1, curFile->currLine, curFile->currCol + i + indx + 1);

                    if(indx + 1 == len){ //There's no content after the end of this comment

                        //Skip this whole line!

                        strcpy(curFile->currLineCon, FILLER_STRING_CHAR_TYP_STR);

                    }else{ //There's still some text after the end of this comment!

                        curFile->nextCol += indx + 2;

                        strcpy(curFile->currLineCon, FILLER_STRING_CHAR_TYP_STR);

                    }

                    i = len;

                    if(waitForComm)
                        waitForComm = 0; //You found the end of this comment!

                }

            }else{ //Ignore the comment for now

                curFile->nextCol += i;

                char *tmpStr = getStrPrt(curFile->currLineCon, 0, i, 1);

                strcpy(curFile->currLineCon, tmpStr);

                free(tmpStr);

                writeLogLine("Preprocessor", 0, "A multi-linear comment has been skipped!", 1, curFile->currLine, curFile->currCol + i);

                i = len;

            }

        }

    }

    return curFile;

}