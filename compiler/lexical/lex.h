#include "../libraries/regex/reg.h"
//#include "../libraries/hex/hex.h"

typedef struct {
    char *type; //symbol, string, character, number & operator!
    char *value;
    int srcColumn;
    int srcLine;
    char *srcFile;
} M_Token;

FILE* lexProc(TmpFileStruc cFileObj){

    FILE *lexFil = fopen(apdStr(cFileObj.pth, ".lxic"), "w"); //Create a new lexer file in "write mode"

    char *tmpStr = malloc(sizeof(char)*MAX_LINE_LENGTH), *curLin = malloc(sizeof(char)*MAX_LINE_LENGTH);

    fgets(tmpStr, MAX_LINE_LENGTH, cFileObj.ptr); //Get the first line
    if(tmpStr[strlen(tmpStr) - 1] == '\n')
        tmpStr[strlen(tmpStr) - 1] = '\0'; //Remove the new line character (\n), and replace it with a line end character (\0)!

    while(getStrIndx(tmpStr, "[FileEnd]") != 0){

        curLin = getStrPrt(tmpStr, getStrIndx(tmpStr, "]->") + 3, strlen(tmpStr), 0); //Get the current line content

        char *curFil = getStrPrt(tmpStr, 2, getStrIndx(tmpStr, "}"), 0);
        //"[{main},%d;%d]->%
        int col = atoi(getStrPrt(tmpStr, getStrIndx(tmpStr, ";") + 1, getStrIndx(tmpStr, "]"), 0)), lin = atoi(getStrPrt(tmpStr, getStrIndx(tmpStr, ",") + 1, getStrIndx(tmpStr, ";"), 0));

        //fprintf(lexFil, "%s\n", curLin); //Debug

        for(int i = 0; i < strlen(curLin); i++, col++){ //Use this loop to scan every character one by one!

            char currChar = curLin[i];

            if(isspace(currChar)) { //Whitespace!

                //Do nothing!

            } else if(regChk("[.0-9]", &currChar)) { //Number

                int alowDot = 1;

                if(curLin[i] == '.' && !isdigit(curLin[i + 1])){

                    //false alarm
                    fprintf(lexFil, "%d `%c` <%s> 0x%09X 1x%09X\n", LEXER_OPERATOR, curLin[i], "0", lin, col); //This is an operator!

                }else{

                    if(curLin[i] == '.')
                        alowDot = 0;

                    fprintf(lexFil, "%d `%c", LEXER_NUMBER, curLin[i]);

                    int delt = 1;

                    while(delt + i < strlen(curLin) && (isdigit(curLin[i + delt]) || ((alowDot) ? curLin[i + delt] == '.' : 0))){

                        fprintf(lexFil, "%c", curLin[i + delt]);

                        if(curLin[i + delt] == '.')
                            alowDot = 0;

                        delt++;

                    }

                    i += delt;

                   fprintf(lexFil, "` <%s> 0x%09X 1x%09X\n", "0", lin, col);

                }


                /*if(curLin[i] == '.' && i + 1 < strlen(curLin) && !regChk("[0-9]", &(curLin[i + 1]))){ //False alarm, this is not a number...

                    fprintf(lexFil, "%d `%c` <%s> 0x%09X 1x%09X\n", LEXER_SYMBOL, curLin[i], "0", lin, col); //This is an operator!

                }else{ //This is a number, keep going...

                    char *num = malloc(sizeof(char)*MAX_LINE_LENGTH);
                    num[0] = curLin[i];
                    num[1] = '\0';
                    int alwDot = 1;

                    i++;

                    if(num[0] == '.')
                        alwDot = 0;
                
                    int delt = 1;

                    while(i - 1 + delt < strlen(curLin) && (alwDot) ? regChk("[.0-9]", &(curLin[i - 1 + delt])) : regChk("[0-9]", &curLin[i - 1 + delt])){

                        num[strlen(num) + 1] = '\0';
                        num[strlen(num)] = curLin[i - 1 + delt];

                        if(num[strlen(num)] == '.')
                            alwDot = 0;

                        delt++;

                    }

                    i += delt - 1;
                    col += delt - 1;

                    fprintf(lexFil, "%d `%s` <%s> 0x%09X 1x%09X\n", LEXER_NUMBER, num, "0", lin, col);

                    free(num);

                }*/

            } else if(curLin[i] == '"') { //String!

                //
                //fprintf(lexFil, "%d `%c` <%s> 0x%09X 1x%09X\n", LEXER_STRING, curLin[i], "0", lin, col);

                int delt = 1;

                fprintf(lexFil, "%d `", LEXER_STRING);

                while(i + delt < strlen(curLin) && (curLin[i + delt] != '"' || curLin[i + delt - 1] == '\\')){

                    fprintf(lexFil, "%c", curLin[i + delt]);

                    delt++;

                }

                col++;
                i += delt;

                fprintf(lexFil, "` <%s> 0x%09X 1x%09X\n", "0", lin, col);
                //fprintf(lexFil, "%d `%c` <%s> 0x%09X 1x%09X\n", LEXER_CHAR, curLin[i], "0", lin, col);

            } else if(curLin[i] == '\'') { //Character!

                int delt = 1;

                fprintf(lexFil, "%d `", LEXER_CHAR);

                while(i + delt < strlen(curLin) && (curLin[i + delt] != '\'' || curLin[i + delt - 1] == '\\')){

                    fprintf(lexFil, "%c", curLin[i + delt]);

                    delt++;

                }

                col++;
                i += delt;

                fprintf(lexFil, "` <%s> 0x%09X 1x%09X\n", "0", lin, col);
                //fprintf(lexFil, "%d `%c` <%s> 0x%09X 1x%09X\n", LEXER_CHAR, curLin[i], "0", lin, col);

            } else if(regChk("[_a-zA-Z]", &currChar) && (!isCharSpcl(currChar) || currChar == '_')) { //Symbol

                //char *sym = malloc(sizeof(char)*strlen(curLin));
                //memset(sym, 0x00, strlen(curLin)*sizeof(char));
                //char *sym;

                //sym[0] = curLin[i];
                //sym[1] = '\0';

                //i++;

                fprintf(lexFil, "%d `%c", LEXER_SYMBOL, curLin[i]);

                int delt = 1;

                while(i + delt < strlen(curLin) && !isspace(curLin[i + delt]) && (!isCharSpcl(curLin[i + delt]) || curLin[i + delt] == '_') && regChk("[a-zA-Z0-9]", &(curLin[i + delt]))){

                    //int l = strlen(sym);

                    //sym[l] = curLin[i + delt];
                    //sym[l + 1] = '\0';

                    fprintf(lexFil, "%c", curLin[i + delt]);

                    delt++;

                }

                //printf("\n\n0%s0\n\n", sym);

                delt--;

                i += delt;
                col += delt;

                fprintf(lexFil, "` <%s> 0x%09X 1x%09X\n", "0", lin, col);

                //fprintf(lexFil, "%d `%c` <%s> 0x%09X 1x%09X\n", LEXER_SYMBOL, sym, "0", lin, col);

                //free(sym);

            } else { //Operator!

                fprintf(lexFil, "%d `%c` <%s> 0x%09X 1x%09X\n", LEXER_OPERATOR, curLin[i], "0", lin, col);

            }

            //fprintf(lexFil, "%d `%s` <%s> 0x%09X 1x%09X\n", 1000, "", "0", 0, 0);
            //symbol -> 1001, string -> 1002, char -> 1003, number -> 1004, operator -> 1005
            //LEXER_SYMBOL, LEXER_STRING, LEXER_CHAR, LEXER_NUMBER, LEXER_OPERATOR
            //1000 `[value]` <[file]> 0x000000000 1x000000000
            //1000 `[value]` <[file]> 0x000000000 1x000000000
            //1000 `[value]` <[file]> 0x000000000 1x000000000
            //^typ ^value    ^scrFile ^srcLine(0) ^srcColumn(1)

            //printf("0x%8X", b)

            printf("[%c], ", curLin[i]); //Debug

        }

        printf(".\n");

        //Get the next line!
        fgets(tmpStr, MAX_LINE_LENGTH, cFileObj.ptr);
        if(tmpStr[strlen(tmpStr) - 1] == '\n')
            tmpStr[strlen(tmpStr) - 1] = '\0'; //Remove the new line character (\n), and replace it with a line end character (\0)!

    }

    fclose(lexFil); //Close the lexer file stream
    lexFil = fopen(apdStr(cFileObj.pth, ".lxic"), "r"); //Open a new lexer stream in "read mode"

    return lexFil;

}


/*

```
using system.io,
      a;
import "file.mur",
        "k.mur";
setsize int 10,
        double 100;

group Name {
    class Name {
        function::type name(){
            //
        }
    }
}
```
=>
```
(symbol)("using") (symbol)("system")("operator")(".")(symbol)("io")("operator")(",")
      (symbol)("a")("operator")(";")
(symbol)("import") (string)("file.mur"),
[...]

(symbol)("group") (symbol)("Name") (operator)("{")
    [...]
(operator)("}")
```
*/