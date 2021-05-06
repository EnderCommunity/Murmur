FileInfo* chkForCom(FileInfo *curFile){
    int indx;
    if(inStrRng(curFile->currLineCon, "/*")){

        indx = getStrIndx(curFile->currLineCon, "/*");

        printf("\n[Debug] Line Content: %s\n[Debug] '/*' Index: %d", curFile->currLineCon, indx);

    }else if(inStrRng(curFile->currLineCon, "//")){

        indx = getStrIndx(curFile->currLineCon, "//");

        printf("\n[Debug] Line Content: %s\n[Debug] '//' Index: %d", curFile->currLineCon, indx);

        printf("\n@@BEFORE: %s@@", curFile->currLineCon);


        if(indx == 0){
            (curFile->currLineCon)[0] = '\0';
        }else
            curFile->currLineCon = getStrPrt(curFile->currLineCon, 0, indx - 1, 1);

        printf("\n@@AFTER: %s@@", curFile->currLineCon);

    }

    return curFile;
}