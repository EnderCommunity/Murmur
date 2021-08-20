#include "gettkn.h"
#include "sav.h"

#include "terminal/specifiers.h"
#include "terminal/declarators.h"
#include "terminal/operators.h"
#include "terminal/statements.h"

void PrsProc(TmpFileStruc FilStruc, FILE *lexFilPtr){

    setTknFilPtr(lexFilPtr); //Setup the tokens queue

    M_Token tkn = getTkn();

    crtPrsFil(FilStruc.pth, PARSER_TYPE_ONLY_TERMINAL); //Create a `.trm` file

    while(kepLop){

        //printf("%d `%s` %d %d %d %d | %d %d %d %d [%s] 0x%09X 1x%09X\n\n", tkn.typ, tkn.val, tkn.defVal1, tkn.defVal2, tkn.defVal3, tkn.defVal4, tkn.adtVal1, tkn.adtVal2, tkn.adtVal3, tkn.adtVal4, tkn.srcFil, tkn.srcLin, tkn.srcCol); //Debug


        // Specifiers
        if(isTypSpc(tkn.typ, tkn.val)){ //"type_specifier"

            crtTypSpc(tkn.val, tkn.__srcLin);

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

        }else if(isElvOpr(tkn)){ //"elevational_operator"

            crtElvOpr(tkn.__srcLin);

        }else if(isNgtOpr(tkn)){ //"negative_operator"

            crtNgtOpr(tkn.__srcLin);

        }

        // Statements
        else if(isRtnStt(tkn.typ, tkn.val)){ //"return_statement"

            crtRtnStt(tkn.__srcLin);

        }else if(isRefStt(tkn.typ, tkn.val)){ //"ref_statement"

            crtRefStt(tkn.__srcLin);

        }else if(isDelStt(tkn.typ, tkn.val)){ //"delete_statement"

            crtDelStt(tkn.__srcLin);

        }
        
        // Defaults
        else if(tkn.typ == LEXER_SYMBOL){ //This is an "IDENTIFIER"

            isrtPrsTrm("IDENTIFIER", tkn.val, tkn.__srcLin);

        }else if(tkn.typ == LEXER_STRING){ //This is a "STRING"

            isrtPrsTrm("STRING", tkn.val, tkn.__srcLin);

        }else if(tkn.typ == LEXER_CHAR){ //This is a "CHAR"

            isrtPrsTrm("CHAR", tkn.val, tkn.__srcLin);

        }else if(tkn.typ == LEXER_BOOLEAN){ //This is a "BOOLEAN"

            isrtPrsTrm("BOOLEAN", tkn.val, tkn.__srcLin);

        }else if(tkn.typ == LEXER_NUMBER){ //This is a "NUMBER"

            isrtPrsTrm("NUMBER", tkn.val, tkn.__srcLin);

        }else if(tkn.typ == LEXER_ZONE_LINE){ //This is a "ZONE_LINE"

            isrtPrsTrm("ZONE_LINE", tkn.val, tkn.__srcLin);

        }else if(tkn.typ == LEXER_HEX){ //This is a "HEX"

            isrtPrsTrm("HEX", tkn.val, tkn.__srcLin);

        }else{ //Unknown component!

            isrtPrsTrm("?", tkn.val, tkn.__srcLin);

        }

        nxtTkn(&tkn); //Get the next token!

    }

    clsPrsFil();
    fclose(lexFilPtr); //Close the file stream!

    //PARSER_TYPE_ALL
    //Now, create a new file for non-terminal data

}