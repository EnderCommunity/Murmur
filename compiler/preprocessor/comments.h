FileInfo* chkForCom(FileInfo *curFile){

    int indx;

    if(inStrRng(curFile->currLineCon, "/*")){ //Not working!

        printf("\n Current Line: %d, Current Column: %d.", curFile->currLine, curFile->currCol);

        Deb();

        indx = getStrIndx(curFile->currLineCon, "/*");

        printf("\n \"/*\"-'s Index: %d", indx);

        Deb();


        if(indx == 0){

            printf("ML (Same Line) comment: %d\n", inStrRng(curFile->currLineCon, "*/"));

            if(inStrRng(curFile->currLineCon, "*/")){

                curFile->nextCol = getStrIndx(curFile->currLineCon, "*/") + 2;

                printf("Next Col: %d\n", curFile->nextCol);


                if(curFile->nextCol >= strlen(curFile->currLineCon) + 1)
                    strcpy(curFile->currLineCon, " "); //NOT CORRECT!
                else
                    curFile->currLineCon = getStrPrt(curFile->currLineCon, curFile->nextCol, strlen(curFile->currLineCon), 0);


                printf("Line Con: %s\n", curFile->currLineCon);


            }else{

                //The end is in another line!

            }

            //curFile->nextCol = getStrIndx(curFile->currLineCon, "*/") + 2;

            //curFile->currLineCon = getStrPrt(curFile->currLineCon, curFile->nextCol, strlen(curFile->currLineCon), 0);
            

        }else{ //Skip the comment until the next loop!

            printf("\nSkipped line!");

            curFile->nextCol = getStrIndx(curFile->currLineCon, "/*");

            printf("\nNext Col: %d", curFile->nextCol);

            curFile->currLineCon = getStrPrt(curFile->currLineCon, 0, indx, 0);

            printf("\nLine Con: %s", curFile->currLineCon);

            //curFile->currCol = 1;

            //You've got a problem with the columns!

            //curFile->nextCol = indx;

            //curFile->currLineCon = getStrPrt(curFile->currLineCon, 0, indx - 1, 0); //Skip the comment and the content until the next loop!

            //curFile->currLineCon = apdStr(getStrPrt(curFile->currLineCon, 0, indx, 0), getStrPrt(curFile->currLineCon, curFile->currCol, strlen(curFile->currLineCon), 0));

        }

        printf("\n[Debug] Line Content: %s\n[Debug] '/*' Index: %d", curFile->currLineCon, indx);

    }else if(0 & inStrRng(curFile->currLineCon, "//")){ //COULD BREAK, multi-linear comments should be processed first!

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