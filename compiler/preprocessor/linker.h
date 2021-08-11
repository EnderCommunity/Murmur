#include "import.h"


//Error [preprocessor.linker.invalid_function]

FileInfo* chkForPprFunc(FileInfo *curFile, FILE *dstFilPtr, char *srcPth){

    int len = strlen(curFile->currLineCon) - END_OF_LINE_COUNT, inStr = 0, inChr = 0;

    printf("\n[New Line, state: ");
    int didPass = 0;

    for(int i = 0; i < len; i++){

        //(curFile->currLineCon)[i]; //Current character

        if((i - 1 != -1) ? ((curFile->currLineCon)[i - 1] != '\\') : 1) { //Look for the '\' char

            if(!inChr && (curFile->currLineCon)[i] == '"') //String opening/closing
                inStr = !inStr;

            if(!inStr && (curFile->currLineCon)[i] == '\'') //Char opening/closing
                inChr = !inChr;

        }

        int shdChk = !inStr && !inChr;

        if(shdChk && (curFile->currLineCon)[i] == '{'){ //Beaware, a new zone opening has been detected!

            curFile->curZon++;

        }else if(shdChk && (curFile->currLineCon)[i] == '}'){  //Beaware, a new zone closing has been detected!

            curFile->curZon--;

        }else{

            shdChk = shdChk && curFile->curZon == 0; //Only look in the zone 0 (the root-level zone)

            if(shdChk){

                //You can start looking now!
                if(!didPass){
    
                    printf("<passed>]");
                    didPass = 1;
    
                }

            }

        }

    }

    if(!didPass){
    
        printf("<failed>]");
    
    }


    //look for "use", "import", "define", and "setsize"

    /*FileInfo *subFilInf = checkFlags(filePtr, full_path, 0); //An object that contains the sub-file info!

    fprintf(dstFilPtr, "[{curFil@%s},%d;%d]->%s\n", srcPth, subFilInf->currLine, subFilInf->currCol, subFilInf->currLineCon);

    writeLogLine("Preprocessor", 0, "Inserted the filtered code into the temporary output file.", 0, 0, 0);*/

    return curFile;

}