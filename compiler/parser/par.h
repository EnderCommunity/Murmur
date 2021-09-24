#include "names.h"

#include "gettkn.h"
#include "sav.h"
#include "trmtkn.h"
#include "prstkn.h"

#include "infotkn.h"

#include "terminal/specifiers.h"
#include "terminal/declarators.h"
#include "terminal/operators.h"
#include "terminal/statements.h"

void rptPrs(int id, int colOff, char *msg){

    Inf_Token tmpInf = getLxrInfTkn(id);

    //printf("\n[%d,%d]", id, colOff);

    rpt(REPORT_CODE_ERROR, //This is an error
    REPORT_SECTION_PARSER, //The error was detected by the preprocessor
    msg, //This is the custom error message (check /compiler/errors/messages.h)
    tmpInf.src, //The source of this error
    tmpInf.lin, //The line of this error
    tmpInf.col + colOff); //The column the error occurs
    isrtPrsNTrm("ERROR", "", -1);

    delLxrInfTkn(tmpInf);

}

int canAsg(T_Comp cmp){

    return (
        strcmp(cmp.nam, PARSER_DEFAULTS_IDENTIFIER) == 0 ||
        strcmp(cmp.nam, PARSER_DEFAULTS_STRING) == 0 ||
        strcmp(cmp.nam, PARSER_DEFAULTS_CHAR) == 0 ||
        strcmp(cmp.nam, PARSER_DEFAULTS_BOOLEAN) == 0 ||
        strcmp(cmp.nam, PARSER_DEFAULTS_NUMBER) == 0 ||
        strcmp(cmp.nam, PARSER_DEFAULTS_DECNUMBER) == 0 ||
        strcmp(cmp.nam, PARSER_DEFAULTS_HEX) == 0
    );

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

        }else if(isVarDcl(tkn.typ, tkn.val)){ //"variable_declarator"

            crtVarDcl(tkn.__srcLin);

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

        }else if(isSttOpr(tkn)){ //"state_operator"

            crtSttOpr(tkn.__srcLin);

        }else if(isInfOpr(tkn)){ //"info_operator"

            crtInfOpr(tkn.__srcLin);

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

        }else if(isThsStt(tkn.typ, tkn.val)){ //"return_statement"

            crtThsStt(tkn.__srcLin);

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

    //crtPrsFil(FilStruc.pth); //Create a `.prs` file
    //`prsFilPtr` is now referring to the `.prs` file
    rdTrmCmpFil(trmCmpFilPth);
    crtFnlPrsFil(FilStruc.pth); //Create a `.prs` file

    //Now, start making sense of the terminal components!
    T_Comp cmp = getTrmCmp();

    char *curGrp = malloc(sizeof(char)*( // The current group name
        MAX_LINE_LENGTH +
        1
    )), *curCls = malloc(sizeof(char)*( // The current class name
        MAX_LINE_LENGTH +
        1
    ));

    int lokForCndEnd = 0, // Should the parser look for the end of a condition?
        PrhPsd = 0; // How many parentheses were passed since the start of this condition

    strcpy(curGrp, "NULL");
    strcpy(curCls, "NULL");

    while(kepLopTrm){

        //curTrmZon:
        //0 - outside
        //1 - inside a group
        //2 - inside a class
        //3 - inside a function

        if(lokForCndEnd && strcmp(cmp.nam, PARSER_OPERATORS_PARENTHESES) == 0){

            PrhPsd += (strcmp(cmp.cnt, PARSER_GENERAL_END) == 0) ? -1 : 1;

        }

        if(curTrmZon > 1 && strcmp(cmp.nam, PARSER_DECLARATORS_VARIABLE) == 0){ // A variable!

            T_Comp tmpTop = cpyCmp(cmp);

            if(nxtTknCmp(&cmp)){

                int isPub = 1; // Is public?
                char *tmpTyp = NULL;

                while(kepLopTrm && (strcmp(cmp.nam, PARSER_OPERATORS_STATE) == 0 || strcmp(cmp.nam, PARSER_OPERATORS_INFO) == 0)){

                    T_Comp tmpMid = cpyCmp(cmp);

                    if(nxtTknCmp(&cmp)){

                        if(strcmp(tmpMid.nam, PARSER_OPERATORS_STATE) == 0){ //A state

                            if(strcmp(cmp.nam, PARSER_SPECIFIERS_STATE) == 0){

                                isPub = strcmp(cmp.cnt, WORD_STATE_PUBLIC) == 0;

                            }else{

                                rptPrs(cmp.srcLin,
                                       2,
                                       MSG_PRS_INFOINDIC_INVALIDINFO);

                            }

                        }else{ //Other info!

                            if(strcmp(cmp.nam, PARSER_SPECIFIERS_TYPE) == 0 || strcmp(cmp.nam, PARSER_DEFAULTS_IDENTIFIER) == 0){

                                tmpTyp = malloc(sizeof(char)*(strlen(cmp.cnt) + 1));
                                strcpy(tmpTyp, cmp.cnt);

                            }else{

                                rptPrs(cmp.srcLin,
                                       1,
                                       MSG_PRS_INFOINDIC_INVALIDINFO);

                            }

                        }

                    }else{

                        rptPrs(tmpTop.srcLin,
                               1 + (tmpMid.nam[1] == ':'),
                               MSG_PRS_INFOINDIC_INVALIDINFO);

                    }

                    nxtTknCmp(&cmp);

                    remTrmCmp(tmpMid);

                }

                if(kepLopTrm && strcmp(cmp.nam, PARSER_DEFAULTS_IDENTIFIER) == 0){

                    if(tmpTyp != NULL){

                        char *tmpStr;

                        if(curTrmZon > 2) {

                            tmpStr = malloc(sizeof(char)*(
                                strlen(cmp.cnt) +
                                strlen(tmpTyp) +
                                1 +
                                1 +
                                2 +
                                1
                            ));

                            sprintf(tmpStr, "~%s,%s,%d", cmp.cnt, tmpTyp, isPub);

                        }else{

                            tmpStr = malloc(sizeof(char)*(
                                strlen(cmp.cnt) +
                                strlen(tmpTyp) +
                                strlen(curGrp) +
                                strlen(curCls) +
                                2 +
                                1 +
                                2 +
                                1
                            ));

                            sprintf(tmpStr, "%s.%s.%s,%s,%d", curGrp, curCls, cmp.cnt, tmpTyp, isPub);

                        }

                        isrtPrsNTrm(PARSER_NTERMINAL_DEFINEVAR, tmpStr, cmp.srcLin);

                        free(tmpStr);

                        T_Comp tmpCmp = cpyCmp(cmp);

                        while(nxtTknCmp(&cmp) && strcmp(cmp.nam, PARSER_OPERATORS_END) != 0){

                            if(strcmp(cmp.nam, PARSER_OPERATORS_ASSIGNMENT) == 0){

                                if(strcmp(cmp.cnt, "=") == 0 && nxtTknCmp(&cmp)){

                                    isrtPrsMltNTrm(PARSER_NTERMINAL_ASSIGN, tmpCmp.cnt, cmp.srcLin);

                                    int prvIncAsi = 0; // Make sure to ignore the
                                                       // "PARSER_OPERATORS_SEPARATION"
                                                       // component inside parentheses!

                                    while(kepLopTrm &&
                                          strcmp(cmp.nam, PARSER_OPERATORS_END) != 0 &&
                                          ((prvIncAsi == 0) ? strcmp(cmp.nam, PARSER_OPERATORS_SEPARATION) != 0 : 1)){

                                        if(strcmp(cmp.nam, PARSER_OPERATORS_PARENTHESES) == 0){

                                            prvIncAsi += (strcmp(cmp.cnt, PARSER_GENERAL_START) == 0) ? 1 : -1;

                                        }

                                        isrtPrsNTrm(cmp.nam, cmp.cnt, cmp.srcLin);

                                        nxtTknCmp(&cmp);

                                    }

                                    prvTknCmp(&cmp);

                                    isrtPrsEndNTrm(); //End the assign function

                                }else{

                                    rptPrs(cmp.srcLin,
                                           0,
                                           MSG_PRS_VAR_INVALIDDECLASSIGNMENT);

                                }

                            }else if(strcmp(cmp.nam, PARSER_OPERATORS_SEPARATION) == 0){

                                if(nxtTknCmp(&cmp) && strcmp(cmp.nam, PARSER_DEFAULTS_IDENTIFIER) == 0){

                                    char *subTmpStr;

                                    if(curTrmZon > 2) {

                                        subTmpStr = malloc(sizeof(char)*(
                                            strlen(cmp.cnt) +
                                            strlen(tmpTyp) +
                                            1 +
                                            1 +
                                            2 +
                                            1
                                        ));

                                        sprintf(subTmpStr, "~%s,%s,%d", cmp.cnt, tmpTyp, isPub);

                                    }else{

                                        subTmpStr = malloc(sizeof(char)*(
                                            strlen(cmp.cnt) +
                                            strlen(tmpTyp) +
                                            strlen(curGrp) +
                                            strlen(curCls) +
                                            2 +
                                            1 +
                                            2 +
                                            1
                                        ));

                                        sprintf(subTmpStr, "%s.%s.%s,%s,%d", curGrp, curCls, cmp.cnt, tmpTyp, isPub);

                                    }

                                    isrtPrsNTrm(PARSER_NTERMINAL_DEFINEVAR, subTmpStr, cmp.srcLin);

                                    free(subTmpStr);

                                }else{

                                    rptPrs(cmp.srcLin,
                                           0,
                                           MSG_PRS_VAR_INVALIDSUBVAR);

                                }

                            }else{

                                rptPrs(tmpTop.srcLin,
                                       strlen(WORD_STATEMENT_VARIABLE),
                                       MSG_PRS_VAR_SEMICOLON);

                            }

                            remTrmCmp(tmpCmp);
                            tmpCmp = cpyCmp(cmp);

                        }

                        remTrmCmp(tmpCmp);

                        if(!kepLopTrm){

                            rptPrs(cmp.srcLin,
                                   0,
                                   MSG_PRS_VAR_SEMICOLON);

                        }

                        free(tmpTyp);

                    }else{

                        rptPrs(tmpTop.srcLin,
                               strlen(WORD_STATEMENT_VARIABLE),
                               MSG_PRS_VAR_NOVALIDTYPE);

                    }

                }else{

                    rptPrs(cmp.srcLin,
                           0,
                           MSG_PRS_VAR_NOVALIDNAME);

                }

            }else{

                rptPrs(tmpTop.srcLin,
                       strlen(WORD_STATEMENT_VARIABLE),
                       MSG_PRS_VAR_NOVALIDTYPE);

            }

            remTrmCmp(tmpTop);

        }else if(curTrmZon == 2 && strcmp(cmp.nam, PARSER_DECLARATORS_FUNCTION) == 0){ // A function!

            T_Comp tmpTop = cpyCmp(cmp);

            if(nxtTknCmp(&cmp)){

                int isPub = 1; // Is public?
                char *tmpTyp = NULL;

                while(kepLopTrm && (strcmp(cmp.nam, PARSER_OPERATORS_STATE) == 0 || strcmp(cmp.nam, PARSER_OPERATORS_INFO) == 0)){

                    T_Comp tmpMid = cpyCmp(cmp);

                    if(nxtTknCmp(&cmp)){

                        if(strcmp(tmpMid.nam, PARSER_OPERATORS_STATE) == 0){ //A state

                            if(strcmp(cmp.nam, PARSER_SPECIFIERS_STATE) == 0){

                                isPub = strcmp(cmp.cnt, WORD_STATE_PUBLIC) == 0;

                            }else{

                                rptPrs(cmp.srcLin,
                                       2,
                                       MSG_PRS_INFOINDIC_INVALIDINFO);

                            }

                        }else{ //Other info!

                            if(strcmp(cmp.nam, PARSER_SPECIFIERS_TYPE) == 0 || strcmp(cmp.nam, PARSER_DEFAULTS_IDENTIFIER) == 0){

                                tmpTyp = malloc(sizeof(char)*(strlen(cmp.cnt) + 1));
                                strcpy(tmpTyp, cmp.cnt);

                            }else{

                                rptPrs(cmp.srcLin,
                                       1,
                                       MSG_PRS_INFOINDIC_INVALIDINFO);

                            }

                        }

                    }else{

                        rptPrs(tmpTop.srcLin,
                               1 + (tmpMid.nam[1] == ':'),
                               MSG_PRS_INFOINDIC_INVALIDINFO);

                    }

                    nxtTknCmp(&cmp);

                    remTrmCmp(tmpMid);

                }

                if(kepLopTrm && strcmp(cmp.nam, PARSER_DEFAULTS_IDENTIFIER) == 0){

                    if(tmpTyp != NULL){

                        char *tmpStr = malloc(sizeof(char)*(
                            strlen(cmp.cnt) +
                            strlen(tmpTyp) +
                            strlen(curGrp) +
                            strlen(curCls) +
                            2 +
                            1 +
                            2 +
                            1
                        ));

                        sprintf(tmpStr, "%s.%s.%s,%s,%d", curGrp, curCls, cmp.cnt, tmpTyp, isPub);

                        isrtPrsNTrm(PARSER_NTERMINAL_DEFINEFUNCTION, tmpStr, cmp.srcLin);

                        free(tmpStr);
                        free(tmpTyp);

                    }else{

                        rptPrs(tmpTop.srcLin,
                               strlen(WORD_STATEMENT_VARIABLE),
                               MSG_PRS_FUNCTION_NOVALIDNAME);

                    }

                }else{

                    rptPrs(cmp.srcLin,
                           0,
                           MSG_PRS_FUNCTION_NOVALIDNAME);

                }

            }else{

                rptPrs(tmpTop.srcLin,
                       strlen(WORD_STATEMENT_VARIABLE),
                       MSG_PRS_FUNCTION_NOVALIDTYPE);

            }

            remTrmCmp(tmpTop);

        }else if(curTrmZon == 1 && strcmp(cmp.nam, PARSER_DECLARATORS_CLASS) == 0){ // A class!

            T_Comp tmpTop = cpyCmp(cmp);

            if(nxtTknCmp(&cmp)){

                int isPub = 1; // Is public?

                while(kepLopTrm && strcmp(cmp.nam, PARSER_OPERATORS_STATE) == 0){

                    if(nxtTknCmp(&cmp)){

                        if(strcmp(cmp.nam, PARSER_SPECIFIERS_STATE) == 0){

                            isPub = strcmp(cmp.cnt, WORD_STATE_PUBLIC) == 0;

                        }else{

                            rptPrs(cmp.srcLin,
                                   2,
                                   MSG_PRS_INFOINDIC_INVALIDINFO);

                        }

                    }else{

                        rptPrs(tmpTop.srcLin,
                               2,
                               MSG_PRS_INFOINDIC_INVALIDINFO);

                    }

                    nxtTknCmp(&cmp);

                }

                if(kepLopTrm && strcmp(cmp.nam, PARSER_DEFAULTS_IDENTIFIER) == 0){

                    char *tmpStr = malloc(sizeof(char)*(
                        strlen(cmp.cnt) +
                        strlen(curGrp) +
                        1 +
                        2 +
                        1
                    ));

                    strcpy(curCls, cmp.cnt);

                    sprintf(tmpStr, "%s.%s,%d", curGrp, cmp.cnt, isPub);

                    isrtPrsNTrm(PARSER_NTERMINAL_DEFINECLASS, tmpStr, tmpTop.srcLin);

                    free(tmpStr);

                }else{

                    rptPrs(tmpTop.srcLin,
                           strlen(WORD_STATEMENT_CLASS),
                           MSG_PRS_CLASS_NAMEMISSING);

                }

            }else{

                rptPrs(tmpTop.srcLin,
                       strlen(WORD_STATEMENT_CLASS),
                       MSG_PRS_CLASS_NAMEMISSING);

            }

            remTrmCmp(tmpTop);

        }else if(curTrmZon == 0 && strcmp(cmp.nam, PARSER_DECLARATORS_GROUP) == 0){ // A group!

            T_Comp tmpTop = cpyCmp(cmp);

            if(nxtTknCmp(&cmp)){

                int isPub = 1; // Is public?

                while(kepLopTrm && strcmp(cmp.nam, PARSER_OPERATORS_STATE) == 0){

                    if(nxtTknCmp(&cmp)){

                        if(strcmp(cmp.nam, PARSER_SPECIFIERS_STATE) == 0){

                            isPub = strcmp(cmp.cnt, WORD_STATE_PUBLIC) == 0;

                        }else{

                            rptPrs(cmp.srcLin,
                                   2,
                                   MSG_PRS_INFOINDIC_INVALIDINFO);

                        }

                    }else{

                        rptPrs(tmpTop.srcLin,
                               2,
                               MSG_PRS_INFOINDIC_INVALIDINFO);

                    }

                    nxtTknCmp(&cmp);

                }

                if(kepLopTrm && strcmp(cmp.nam, PARSER_DEFAULTS_IDENTIFIER) == 0){

                    char *tmpStr = malloc(sizeof(char)*(
                        strlen(cmp.cnt) +
                        2 +
                        1
                    ));

                    strcpy(curGrp, cmp.cnt);

                    sprintf(tmpStr, "%s,%d", cmp.cnt, isPub);

                    isrtPrsNTrm(PARSER_NTERMINAL_DEFINEGROUP, tmpStr, tmpTop.srcLin);

                    free(tmpStr);

                }else{

                    rptPrs(tmpTop.srcLin,
                           strlen(WORD_STATEMENT_GROUP),
                           MSG_PRS_GROUP_NAMEMISSING);

                }

            }else{

                rptPrs(tmpTop.srcLin,
                       strlen(WORD_STATEMENT_GROUP),
                       MSG_PRS_GROUP_NAMEMISSING);

            }

            remTrmCmp(tmpTop);

        }else if(curTrmZon == 0 && strcmp(cmp.nam, PARSER_STATEMENTS_SETSIZE) == 0){ //The setsize method

            T_Comp tmpBkp = cpyCmp(cmp);

            if(nxtTknCmp(&cmp) && strcmp(cmp.nam, PARSER_SPECIFIERS_TYPE) == 0){

                T_Comp cmpTyp = cpyCmp(cmp);

                if(nxtTknCmp(&cmp) && strcmp(cmp.nam, PARSER_DEFAULTS_NUMBER) == 0){

                    char *tmpStr = malloc(sizeof(char)*(strlen(cmp.cnt) + strlen(cmpTyp.cnt) + 2));

                    sprintf(tmpStr, "%s,%s", cmpTyp.cnt, cmp.cnt);

                    isrtPrsNTrm(PARSER_NTERMINAL_CALLSETSIZE, tmpStr, tmpBkp.srcLin);

                    free(tmpStr);

                }else{

                    rptPrs(cmpTyp.srcLin, 0, MSG_PRS_SETSIZEINVALIDSIZEINPUT);

                }

                remTrmCmp(cmpTyp);

            }else{

                rptPrs(tmpBkp.srcLin, 0, MSG_PRS_SETSIZEINVALIDTYPEINPUT);

            }

            remTrmCmp(tmpBkp);

        }else if(curTrmZon > 2 && strcmp(cmp.nam, PARSER_STATEMENTS_DELETE) == 0){ //The delete method

            T_Comp tmpBkp = cpyCmp(cmp);

            if(nxtTknCmp(&cmp) && strcmp(cmp.nam, PARSER_DEFAULTS_IDENTIFIER) == 0){

                T_Comp cmpTyp = cpyCmp(cmp);

                isrtPrsNTrm(PARSER_NTERMINAL_DELETE, cmp.cnt, cmp.srcLin);

                //Wait for the char ";", or the char ",".
                //If the char "," is detected, start a loop.
                //If not, just end the operation.

                int isEnd = 0;

                while(nxtTknCmp(&cmp) && (
                    (isEnd = (strcmp(cmp.nam, PARSER_OPERATORS_END) == 0)) ||
                    strcmp(cmp.nam, PARSER_OPERATORS_SEPARATION) == 0
                )){

                    if(isEnd)
                        break; //Stop the loop!
                    else if(!isEnd && nxtTknCmp(&cmp) && strcmp(cmp.nam, PARSER_DEFAULTS_IDENTIFIER) == 0)
                        isrtPrsNTrm(PARSER_NTERMINAL_DELETE, cmp.cnt, cmp.srcLin);
                    else
                        rptPrs(cmp.srcLin, 0, MSG_PRS_DELETEMISSINGINPUT);

                }

                if(!isEnd){

                    rptPrs(tmpBkp.srcLin, 0, MSG_PRS_DELETEMISSINGEND);
                    break;

                }

                remTrmCmp(cmpTyp);

            }else
                rptPrs(tmpBkp.srcLin, 0, MSG_PRS_DELETEMISSINGINPUT);

            remTrmCmp(tmpBkp);

        }else if(curTrmZon > 2 && !lokForCndEnd && strcmp(cmp.nam, PARSER_STATEMENTS_IF) == 0){ // The if statement

            if(nxtTknCmp(&cmp) && strcmp(cmp.nam, PARSER_OPERATORS_PARENTHESES) == 0){

                isrtPrsMltNTrm(PARSER_NTERMINAL_IF, "", cmp.srcLin);

                lokForCndEnd = 1;
                PrhPsd = 0;

            }else{

                rptPrs(cmp.srcLin,
                       0,
                       MSG_PRS_IF_CONDITIONSINSIDEPARENTHESES);

            }

        }else if(0 && curTrmZon > 2 && !lokForCndEnd && strcmp(cmp.nam, PARSER_STATEMENTS_ELSE) == 0){ // The else & "else if" statement

            if(nxtTknCmp(&cmp) && strcmp(cmp.nam, PARSER_OPERATORS_ZONE) == 0 && strcmp(cmp.cnt, PARSER_GENERAL_START) == 0){

                isrtPrsNTrm(PARSER_NTERMINAL_ELSE, "", cmp.srcLin);

                prvTknCmp(&cmp);

            }else if(strcmp(cmp.nam, PARSER_STATEMENTS_IF) == 0){

                if(nxtTknCmp(&cmp) && strcmp(cmp.nam, PARSER_OPERATORS_PARENTHESES) == 0){

                    isrtPrsMltNTrm(PARSER_NTERMINAL_ELSEIF, "", cmp.srcLin);

                    lokForCndEnd = 1;
                    PrhPsd = 0;

                }else{

                    rptPrs(cmp.srcLin,
                           0,
                           MSG_PRS_IF_CONDITIONSINSIDEPARENTHESES);

                }

            }else{

                rptPrs(cmp.srcLin,
                       0,
                       MSG_PRS_IF_CONDITIONSINSIDEPARENTHESES);

            }

        }else if(lokForCndEnd && PrhPsd == -1 && strcmp(cmp.nam, PARSER_OPERATORS_PARENTHESES) == 0 && strcmp(cmp.cnt, PARSER_GENERAL_END) == 0){

            isrtPrsEndNTrm(); // End the "if"/"else if"/"else" statement

            lokForCndEnd = PrhPsd = 0;

        }else if(curTrmZon < 4 && strcmp(cmp.nam, PARSER_OPERATORS_ZONE) == 0){ // Manage zone operators

            //curTrmZon:
            //0 - outside
            //1 - inside a group
            //2 - inside a class
            //3 - inside a function

            if(strcmp(cmp.cnt, PARSER_GENERAL_END) == 0)
                isrtPrsNTrm(PARSER_NTERMINAL_ENDDEFINITION, "", cmp.srcLin);

            /*if(curTrmZon > 2) { // If you're inside a function

                //

            }*/

            //

        }else if(strcmp(cmp.nam, PARSER_OPERATORS_END) == 0){

            // Don't do anything!

        }else{

            isrtPrsNTrm(cmp.nam, cmp.cnt, cmp.srcLin);

        }

        nxtTknCmp(&cmp);

    }

    free(curGrp);
    free(curCls);

    remTrmCmp(cmp);

    clsFnlPrsFil(); //Close the `.prs` file

    //clsPrsFil();
    clsTrmCmpFil();
    //fclose(trmCmpFilPtr); //Close the file stream!

    fclose(lexFilPtr); //Close the file stream!

    //PARSER_TYPE_ALL
    //Now, create a new file for non-terminal data

}