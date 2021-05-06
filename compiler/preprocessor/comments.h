FileInfo* chkForCom(FileInfo *curFile){
    int indx;
    if(inStrRng(curFile->currLineCon, "/*")){

        indx = getStrIndx(curFile->currLineCon, "/*");

        printf("\n[Debug] Line Content: %s\n[Debug] '/*' Index: %d", curFile->currLineCon, indx);

    }else if(inStrRng(curFile->currLineCon, "//")){

        indx = getStrIndx(curFile->currLineCon, "//");

        printf("\n[Debug] Line Content: %s\n[Debug] '//' Index: %d", curFile->currLineCon, indx);

        curFile->currLineCon = getStrPrt(curFile->currLineCon, 0, indx - 1, 1);

    }

    return curFile;
}