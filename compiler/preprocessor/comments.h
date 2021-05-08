FileInfo* chkForCom(FileInfo *curFile){

    int indx;

    if(inStrRng(curFile->currLineCon, "/*")){ //Not working!

        indx = getStrIndx(curFile->currLineCon, "/*");


        if(indx == 0){

            if(inStrRng(curFile->currLineCon, "*/")){

                curFile->nextCol = getStrIndx(curFile->currLineCon, "*/") + 2;

                strcpy(curFile->currLineCon, " ");

            }else{

                //The end is in another line!

            }

            //curFile->nextCol = getStrIndx(curFile->currLineCon, "*/") + 2;

            //curFile->currLineCon = getStrPrt(curFile->currLineCon, curFile->nextCol, strlen(curFile->currLineCon), 0);
            

        }else{ //Skip the comment until the next loop!

            //curFile->currCol = 1;

            //You've got a problem with the columns!

            //curFile->nextCol = indx;

            //curFile->currLineCon = getStrPrt(curFile->currLineCon, 0, indx - 1, 0); //Skip the comment and the content until the next loop!

            //curFile->currLineCon = apdStr(getStrPrt(curFile->currLineCon, 0, indx, 0), getStrPrt(curFile->currLineCon, curFile->currCol, strlen(curFile->currLineCon), 0));

        }

        printf("\n[Debug] Line Content: %s\n[Debug] '/*' Index: %d", curFile->currLineCon, indx);

    }else if(inStrRng(curFile->currLineCon, "//")){ //Fully functional!

        indx = getStrIndx(curFile->currLineCon, "//");


        printf("\n[Debug] Line Content: %s\n[Debug] '//' Index: %d", curFile->currLineCon, indx);

        printf("\n--BEFORE: %s--", curFile->currLineCon);


        if(indx == 0)
            strcpy(curFile->currLineCon, "");
        else
            curFile->currLineCon = getStrPrt(curFile->currLineCon, 0, indx - 1, 1);

        printf("\n--AFTER: %s--", curFile->currLineCon);

    }

    return curFile;

}