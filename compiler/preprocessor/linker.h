#include "import.h"

FileInfo* chkForPprFunc(FileInfo *curFile, FILE *dstFilPtr, char *srcPth){

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

        if(shdChk && (curFile->currLineCon)[i] == '{'){ //Beaware, a new zone opening has been detected!

            curFile->curZon++;

        }else if(shdChk && (curFile->currLineCon)[i] == '}'){  //Beaware, a new zone closing has been detected!

            curFile->curZon--;

        }else if(shdChk && curFile->curZon == 0){

            //You can start looking now!

            if(i + 4 < len && (curFile->currLineCon)[i] == 'u' && (curFile->currLineCon)[i + 1] == 's' && (curFile->currLineCon)[i + 2] == 'i' && (curFile->currLineCon)[i + 3] == 'n' && (curFile->currLineCon)[i + 4] == 'g'){

                //The "use" statement has been detected!
                printf("\n'using' statement detected!");

            }

            if(i + 5 < len && (curFile->currLineCon)[i] == 'i' && (curFile->currLineCon)[i + 1] == 'm' && (curFile->currLineCon)[i + 2] == 'p' && (curFile->currLineCon)[i + 3] == 'o' && (curFile->currLineCon)[i + 4] == 'r' && (curFile->currLineCon)[i + 5] == 't'){

                //The "import" statement has been detected!
                printf("\n'import' statement detected!");

            }

            if(i + 5 < len && (curFile->currLineCon)[i] == 'd' && (curFile->currLineCon)[i + 1] == 'e' && (curFile->currLineCon)[i + 2] == 'f' && (curFile->currLineCon)[i + 3] == 'i' && (curFile->currLineCon)[i + 4] == 'n' && (curFile->currLineCon)[i + 5] == 'e'){

                //The "define" statement has been detected!
                printf("\n'define' statement detected!");

            }

            if(i + 6 < len && (curFile->currLineCon)[i] == 's' && (curFile->currLineCon)[i + 1] == 'e' && (curFile->currLineCon)[i + 2] == 't' && (curFile->currLineCon)[i + 3] == 's' && (curFile->currLineCon)[i + 4] == 'i' && (curFile->currLineCon)[i + 5] == 'z' && (curFile->currLineCon)[i + 6] == 'e'){

                //The "setsize" statement has been detected!
                printf("\n'setsize' statement detected!");

            }

        }

    }

    /*FileInfo *subFilInf = checkFlags(filePtr, full_path, 0); //An object that contains the sub-file info!

    fprintf(dstFilPtr, "[{curFil@%s},%d;%d]->%s\n", srcPth, subFilInf->currLine, subFilInf->currCol, subFilInf->currLineCon);

    writeLogLine("Preprocessor", 0, "Inserted the filtered code into the temporary output file.", 0, 0, 0);*/

    return curFile;

}