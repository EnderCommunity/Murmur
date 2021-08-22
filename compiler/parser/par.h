#include "gettkn.h"
#include "sav.h"
#include "trmtkn.h"
#include "prstkn.h"

#include "names.h"
#include "infotkn.h"

#include "terminal/specifiers.h"
#include "terminal/declarators.h"
#include "terminal/operators.h"
#include "terminal/statements.h"

void rptPrs(int id, char *msg){

    Inf_Token tmpInf = getLxrInfTkn(id);

    rpt(REPORT_CODE_ERROR, //This is an error
    REPORT_SECTION_PARSER, //The error was detected by the preprocessor
    msg, //This is the custom error message (check /compiler/errors/messages.h)
    tmpInf.src, //The source of this error
    tmpInf.lin, //The line of this error
    tmpInf.col); //The column the error occurs
    isrtPrsNTrm("ERROR", "", -1);

    delLxrInfTkn(tmpInf);

}

void PrsProc(TmpFileStruc FilStruc, FILE *lexFilPtr){

    setTknFilPtr(lexFilPtr); //Setup the tokens queue

    M_Token tkn = getTkn();

    crtPrsFil(FilStruc.pth); //Create a `.trm` file

    while(kepLop){

        //printf("%d `%s` %d %d %d %d | %d %d %d %d [%s] 0x%09X 1x%09X\n\n", tkn.typ, tkn.val, tkn.defVal1, tkn.defVal2, tkn.defVal3, tkn.defVal4, tkn.adtVal1, tkn.adtVal2, tkn.adtVal3, tkn.adtVal4, tkn.srcFil, tkn.srcLin, tkn.srcCol); //Debug


        // Specifiers
        if(isTypSpc(tkn)){ //"type_specifier"

            crtTypSpc(tkn);

        }else if(isSttSpc(tkn.typ, tkn.val)){ //"state_specifier"

            crtSttSpc(tkn.val, tkn.__srcLin);

        }

        // Declarators
        else if(isFncDcl(tkn.typ, tkn.val)){ //"function_declarator"

            crtFncDcl(tkn.__srcLin);

        }else if(isGrpDcl(tkn.typ, tkn.val)){ //"group_declarator"

            crtGrpDcl(tkn.__srcLin);

        }else if(isClsDcl(tkn.typ, tkn.val)){ //"class_declarator"

            crtClsDcl(tkn.__srcLin);

        }
        
        // Operators
        else if(isEndOpr(tkn)){ //"end_operator"

            crtEndOpr(tkn.__srcLin);

        }else if(isZonOpr(tkn)){ //"zone_operator"

            crtZonOpr(tkn.val, tkn.__srcLin);

        }else if(isRtrTypOpr(tkn)){ //"return_type_operator"

            crtRtrTypOpr(tkn.__srcLin);

        }else if(isArrOpr(tkn)){ //"array_operator"

            crtArrOpr(tkn.val, tkn.__srcLin);

        }else if(isCmpOpr(tkn)){ //"comparison_operator"

            char *tmp = malloc(sizeof(char)*3);

            if(tkn.defVal3)
                sprintf(tmp, "~%s", tkn.val);
            else
                strcpy(tmp, tkn.val);

            crtCmpOpr(tmp, tkn.__srcLin);

            free(tmp);

        }else if(isAsiOpr(tkn)){ //"assignment_operator"

            crtAsiOpr(tkn.val, tkn.__srcLin);

        }else if(isAsiShrOpr(tkn)){ //"assignment_short_operator"

            crtAsiShrOpr(tkn.val, tkn.__srcLin);

        }else if(isPrnOpr(tkn)){ //"parentheses_operator"

            crtPrnOpr(tkn.val, tkn.__srcLin);

        }else if(isSprOpr(tkn)){ //"separation_operator"

            crtSprOpr(tkn.__srcLin);

        }else if(isDotOpr(tkn)){ //"dot_operator"

            crtDotOpr(tkn.__srcLin);

        }else if(isMthOpr(tkn)){ //"maths_operator"

            crtMthOpr(tkn.val, tkn.__srcLin);

        }else if(isNgtOpr(tkn)){ //"negative_operator"

            crtNgtOpr(tkn.__srcLin);

        }

        // Statements
        else if(isRtnStt(tkn.typ, tkn.val)){ //"return_statement"

            crtRtnStt(tkn.__srcLin);

        }else if(isRefStt(tkn.typ, tkn.val)){ //"ref_statement"

            crtRefStt(tkn.__srcLin);

        }else if(isIfStt(tkn.typ, tkn.val)){ //"if_statement"

            crtIfStt(tkn.__srcLin);

        }else if(isElsStt(tkn.typ, tkn.val)){ //"else_statement"

            crtElsStt(tkn.__srcLin);

        }else if(isDelStt(tkn.typ, tkn.val)){ //"delete_statement"

            crtDelStt(tkn.__srcLin);

        }else if(isSetSizStt(tkn.typ, tkn.val)){ //"setsize_statement"

            crtSetSizStt(tkn.__srcLin);

        }
        
        // Defaults
        else if(tkn.typ == LEXER_SYMBOL){ //This is an "IDENTIFIER"

            isrtPrsTrm(PARSER_DEFAULTS_IDENTIFIER, tkn.val, tkn.__srcLin);

        }else if(tkn.typ == LEXER_STRING){ //This is a "STRING"

            isrtPrsTrm(PARSER_DEFAULTS_STRING, tkn.val, tkn.__srcLin);

        }else if(tkn.typ == LEXER_CHAR){ //This is a "CHAR"

            isrtPrsTrm(PARSER_DEFAULTS_CHAR, tkn.val, tkn.__srcLin);

        }else if(tkn.typ == LEXER_BOOLEAN){ //This is a "BOOLEAN"

            isrtPrsTrm(PARSER_DEFAULTS_BOOLEAN, tkn.val, tkn.__srcLin);

        }else if(tkn.typ == LEXER_NUMBER && tkn.adtVal1 == 1){ //This is a "NUMBER"

            isrtPrsTrm(PARSER_DEFAULTS_DECNUMBER, tkn.val, tkn.__srcLin);

        }else if(tkn.typ == LEXER_NUMBER){ //This is a "NUMBER"

            isrtPrsTrm(PARSER_DEFAULTS_NUMBER, tkn.val, tkn.__srcLin);

        }else if(tkn.typ == LEXER_ZONE_LINE){ //This is a "ZONE_LINE"

            isrtPrsTrm(PARSER_DEFAULTS_ZONE_LINE, tkn.val, tkn.__srcLin);

        }else if(tkn.typ == LEXER_HEX){ //This is a "HEX"

            isrtPrsTrm(PARSER_DEFAULTS_HEX, tkn.val, tkn.__srcLin);

        }else{ //Unknown component!

            isrtPrsTrm("?", tkn.val, tkn.__srcLin);

        }

        nxtTkn(&tkn); //Get the next token!

    }

    char *trmCmpFilPth = malloc(sizeof(char)*(strlen(prsFilPth) + 1));
    strcpy(trmCmpFilPth, prsFilPth);

    clsPrsFil();
    fclose(lexFilPtr); //Close the file stream!

    //crtPrsFil(FilStruc.pth); //Create a `.prs` file
    //`prsFilPtr` is now referring to the `.prs` file
    rdTrmCmpFil(trmCmpFilPth);
    crtFnlPrsFil(FilStruc.pth); //Create a `.prs` file

    //Now, start making sense of the terminal components!
    T_Comp cmp = getTrmCmp();

    while(kepLopTrm){

        //printf("%s(%s)<%d>\n", cmp.nam, cmp.cnt, cmp.srcLin);

        if(strcmp(cmp.nam, PARSER_SPECIFIERS_STATE) == 0 || // Could be a Group, class, function, or a class-level variable
            strcmp(cmp.nam, PARSER_DECLARATORS_FUNCTION) == 0 || // a function!
            strcmp(cmp.nam, PARSER_DECLARATORS_GROUP) == 0 || // a group!
            strcmp(cmp.nam, PARSER_DECLARATORS_CLASS) == 0 || // a class!
            strcmp(cmp.nam, PARSER_SPECIFIERS_TYPE) == 0 // a variable!
            ){

            T_Comp tmpTop = cpyCmp(cmp);

            int isStat = strcmp(cmp.nam, PARSER_SPECIFIERS_STATE) == 0;

            if(nxtTknCmp(&cmp)){

                if((isStat) ? ( //DefVar!
                        strcmp(cmp.nam, PARSER_SPECIFIERS_TYPE) == 0
                    ) : (
                        strcmp(tmpTop.nam, PARSER_SPECIFIERS_TYPE) == 0
                    )){

                    T_Comp tmpTyp;

                    if(isStat)
                        tmpTyp = cpyCmp(cmp);

                    if(!isStat || (nxtTknCmp(&cmp) && strcmp(cmp.nam, PARSER_DEFAULTS_IDENTIFIER) == 0)){

                        char *tmpStr = malloc(sizeof(char)*(((!isStat) ?
                                                                (strlen(cmp.cnt) + strlen(tmpTop.cnt) + strlen("public")) :
                                                                (strlen(cmp.cnt) + strlen(tmpTyp.cnt) + strlen(tmpTop.cnt))
                                                            ) + 2 + 1));
                        if(!isStat)
                            sprintf(tmpStr, "%s,%s,public", cmp.cnt, tmpTop.cnt);
                        else
                            sprintf(tmpStr, "%s,%s,%s", cmp.cnt, tmpTyp.cnt, tmpTop.cnt);

                        isrtPrsNTrm(PARSER_NTERMINAL_DEFINEVAR, tmpStr, tmpTop.srcLin);

                        free(tmpStr);

                    }else{

                        rptPrs(tmpTyp.srcLin, MSG_PRS_VARNAMEMISSING);

                    }

                    if(isStat)
                        remTrmCmp(tmpTyp);

                }else if((isStat) ? ( //FUNCTION!
                        strcmp(cmp.nam, PARSER_DECLARATORS_FUNCTION) == 0
                    ) : (
                        strcmp(tmpTop.nam, PARSER_DECLARATORS_FUNCTION) == 0
                    )){

                    if((!isStat && strcmp(cmp.nam, PARSER_OPERATORS_RETURN_TYPE) == 0) ||
                        (nxtTknCmp(&cmp) && strcmp(cmp.nam, PARSER_OPERATORS_RETURN_TYPE) == 0)
                        ){

                        T_Comp tmpCrd = cpyCmp(cmp);

                        if(nxtTknCmp(&cmp) && strcmp(cmp.nam, PARSER_SPECIFIERS_TYPE) == 0 ||
                            strcmp(cmp.nam, PARSER_DEFAULTS_IDENTIFIER) == 0 ){

                            T_Comp tmpRtrTyp = cpyCmp(cmp);

                            if(nxtTknCmp(&cmp) && strcmp(cmp.nam, PARSER_DEFAULTS_IDENTIFIER) == 0 ){

                                char *tmpStr = malloc(sizeof(char)*(((!isStat) ? (
                                                                        strlen(tmpRtrTyp.cnt) + strlen(cmp.cnt) + strlen("public")) : (
                                                                        strlen(tmpRtrTyp.cnt) + strlen(cmp.cnt) + strlen(tmpTop.cnt)
                                                                        )
                                                                    ) + 2 + 1));

                                if(!isStat)
                                    sprintf(tmpStr, "%s,%s,public", cmp.cnt, tmpRtrTyp.cnt);
                                else
                                    sprintf(tmpStr, "%s,%s,%s", cmp.cnt, tmpRtrTyp.cnt, tmpTop.cnt);

                                isrtPrsNTrm(PARSER_NTERMINAL_DEFINEFUNCTION, tmpStr, tmpTop.srcLin);

                                free(tmpStr);

                            }else{

                                rptPrs(tmpRtrTyp.srcLin, MSG_PRS_FUNCNAMEMISSING);

                            }

                            remTrmCmp(tmpRtrTyp);

                        }else{

                            rptPrs(tmpCrd.srcLin, MSG_PRS_FUNCRETURNTYPEMISSING);

                        }

                        remTrmCmp(tmpCrd);

                    }else{

                        rptPrs((isStat) ? cmp.srcLin : tmpTop.srcLin, MSG_PRS_FUNCRETURNOPMISSING);

                    }

                }else if((isStat) ? ( //GROUP!
                        strcmp(cmp.nam, PARSER_DECLARATORS_GROUP) == 0
                    ) : (
                        strcmp(tmpTop.nam, PARSER_DECLARATORS_GROUP) == 0
                    )){

                    T_Comp tmpTop = cpyCmp(cmp);

                    if((!isStat && strcmp(cmp.nam, PARSER_DEFAULTS_IDENTIFIER) == 0) ||
                        (nxtTknCmp(&cmp) && strcmp(cmp.nam, PARSER_DEFAULTS_IDENTIFIER) == 0)
                        ){

                        char *tmpStr = malloc(sizeof(char)*(((!isStat) ? (
                                                                strlen(cmp.cnt) + strlen("public")) : (
                                                                strlen(cmp.cnt) + strlen(tmpTop.cnt)
                                                                )
                                                            ) + 2 + 1));

                        if(!isStat)
                            sprintf(tmpStr, "%s,public", cmp.cnt);
                        else
                            sprintf(tmpStr, "%s,%s", cmp.cnt, tmpTop.cnt);

                        isrtPrsNTrm(PARSER_NTERMINAL_DEFINEGROUP, tmpStr, tmpTop.srcLin);

                        free(tmpStr);

                    }else{

                        rptPrs(tmpTop.srcLin, MSG_PRS_GROUPNAMEMISSING);

                    }

                    remTrmCmp(tmpTop);

                }else if((isStat) ? ( //CLASS!
                        strcmp(cmp.nam, PARSER_DECLARATORS_CLASS) == 0
                    ) : (
                        strcmp(tmpTop.nam, PARSER_DECLARATORS_CLASS) == 0
                    )){

                    T_Comp tmpTop = cpyCmp(cmp);

                    if((!isStat && strcmp(cmp.nam, PARSER_DEFAULTS_IDENTIFIER) == 0) ||
                        (nxtTknCmp(&cmp) && strcmp(cmp.nam, PARSER_DEFAULTS_IDENTIFIER) == 0)
                        ){

                        char *tmpStr = malloc(sizeof(char)*(((!isStat) ? (
                                                                strlen(cmp.cnt) + strlen("public")) : (
                                                                strlen(cmp.cnt) + strlen(tmpTop.cnt)
                                                                )
                                                            ) + 2 + 1));

                        if(!isStat)
                            sprintf(tmpStr, "%s,public", cmp.cnt);
                        else
                            sprintf(tmpStr, "%s,%s", cmp.cnt, tmpTop.cnt);

                        isrtPrsNTrm(PARSER_NTERMINAL_DEFINECLASS, tmpStr, tmpTop.srcLin);

                        free(tmpStr);

                    }else{

                        rptPrs(tmpTop.srcLin, MSG_PRS_CLASSNAMEMISSING);

                    }

                    remTrmCmp(tmpTop);

                }else{

                    rptPrs(cmp.srcLin, MSG_PRS_INCORRECTUSEOFSTATE);

                }

            }else{

                rptPrs(tmpTop.srcLin, MSG_PRS_MISSINGSTRUCTVALUE);

            }

            remTrmCmp(tmpTop);

        }else if(strcmp(cmp.nam, PARSER_STATEMENTS_SETSIZE) == 0){ //The setsize method

            T_Comp tmpBkp = cpyCmp(cmp);

            if(nxtTknCmp(&cmp) && strcmp(cmp.nam, PARSER_SPECIFIERS_TYPE) == 0){

                T_Comp cmpTyp = cpyCmp(cmp);

                if(nxtTknCmp(&cmp) && strcmp(cmp.nam, PARSER_DEFAULTS_NUMBER) == 0){

                    char *tmpStr = malloc(sizeof(char)*(strlen(cmp.cnt) + strlen(cmpTyp.cnt) + 2));

                    sprintf(tmpStr, "%s,%s", cmpTyp.cnt, cmp.cnt);

                    isrtPrsNTrm(PARSER_NTERMINAL_CALLSETSIZE, tmpStr, tmpBkp.srcLin);

                    free(tmpStr);

                }else{

                    isrtPrsNTrm("ERROR", "", -1);

                }

                remTrmCmp(cmpTyp);

            }else{

                isrtPrsNTrm("ERROR", "", -1);

            }

            remTrmCmp(tmpBkp);

        }else if(strcmp(cmp.nam, PARSER_DEFAULTS_IDENTIFIER) == 0){ // Call a function, group, class, or variable

            T_Comp tmpBkp = cpyCmp(cmp);
            char *tmpStr = malloc(sizeof(char)*(strlen(cmp.cnt) + 1));
            strcpy(tmpStr, cmp.cnt);

            int lokForDot = 1;

            while(nxtTknCmp(&cmp) && strcmp(cmp.nam, (lokForDot) ? PARSER_OPERATORS_DOT : PARSER_DEFAULTS_IDENTIFIER) == 0){

                int valLen = strlen(cmp.cnt);
                valLen = (valLen == 0 ? 1 : valLen);

                tmpStr = realloc(tmpStr, sizeof(char)*(strlen(tmpStr) + valLen + 1));
                char *tmpStr2 = malloc(sizeof(char)*(strlen(tmpStr) + valLen + 1));

                sprintf(tmpStr2, "%s%s", tmpStr, (strlen(cmp.cnt) == 0) ? "." : cmp.cnt);
                strcpy(tmpStr, tmpStr2);

                free(tmpStr2);

                remTrmCmp(tmpBkp);
                tmpBkp = cpyCmp(cmp);

                lokForDot = !lokForDot;

            }

            if(!lokForDot){

                isrtPrsNTrm("ERROR", "", -1);

            }else{

                if(strcmp(cmp.nam, PARSER_OPERATORS_PARENTHESES) == 0 &&
                        strcmp(cmp.cnt, PARSER_GENERAL_START) == 0){ // A function - IDENTIFIER()

                    prvTknCmp(&cmp);

                    isrtPrsNTrm(PARSER_NTERMINAL_CALLFUNC, tmpStr, tmpBkp.srcLin);

                }else if(strcmp(cmp.nam, PARSER_OPERATORS_RETURN_TYPE) == 0){ // A function - IDENTIFIER::TYPE()

                    if(nxtTknCmp(&cmp) && strcmp(cmp.nam, PARSER_SPECIFIERS_TYPE) == 0){

                        tmpStr = realloc(tmpStr, sizeof(char)*(strlen(cmp.nam) + strlen(cmp.cnt) + 2));
                        char *tmpStr2 = malloc(sizeof(char)*(strlen(cmp.nam) + strlen(cmp.cnt) + 2));

                        sprintf(tmpStr2, "%s:%s", tmpStr, cmp.cnt);
                        strcpy(tmpStr, tmpStr2);

                        free(tmpStr2);

                        isrtPrsNTrm(PARSER_NTERMINAL_CALLFUNC, tmpStr, tmpBkp.srcLin);

                    }else{

                        isrtPrsNTrm("ERROR", "", -1);

                    }

                }else{ // A variable

                    prvTknCmp(&cmp);

                    isrtPrsNTrm(PARSER_NTERMINAL_CALLVAR, tmpStr, tmpBkp.srcLin);

                }

            }

            free(tmpStr);

            remTrmCmp(tmpBkp);

        }else{

            isrtPrsNTrm(cmp.nam, cmp.cnt, cmp.srcLin);

        }

        nxtTknCmp(&cmp);

    }

    clsFnlPrsFil(); //Close the `.prs` file

    //clsPrsFil();
    clsTrmCmpFil();
    //fclose(trmCmpFilPtr); //Close the file stream!

    //PARSER_TYPE_ALL
    //Now, create a new file for non-terminal data

}