/*

(OUTDATED)

All the expressions in Mur are gonna be:

syb: LEXER_SYMBOL
str: LEXER_STRING
chr: LEXER_CHAR
num: LEXER_NUMBER
op: LEXER_OPERATOR

val: all
none: void

assignment: <syb, "variable"> <op, "="> <val>, output: none
keyword: <syb, "gup:stms">
type: <syb, "gup:tps">
priority: <op, "("> ... <op, ")">, output: priority
operation: <num> <op, "math-related"> <num>, output: <num>
levelled_operation: <str>||<chr> + <str>||<chr>, output: <str>
declaration: <syb, "type"> <syb>, output: none
function_call: <syb, "function"> <op, "("> ... <op, ")">, output: <val>||none
function_levelled_call: <class_obj> <op, "."> <syb, "function"> <op, "("> ... <op, ")">, output: <val>||none
function_definition: <syb, "val:function"> <op, ":"> <op, ":"> <syb, "type"> <syb> <op, "("> ... <op, ")"> <op, "{"> ... <op, "}">, output: none
group_call: <syb, "group"> <op, ".">, output: <group_obj>
group_definition: <syb, "val:group"> <syb> <op, "{"> ... <op, "}">, output: none
class_call: <group_obj> <op, "."> <syb, "class">, output: <class_obj>
class_definition: <syb, "val:class"> <syb> <op, "{"> ... <op, "}">, output: none
constructor_definition: <syb, "val:function"> <op, ":"> <op, ":"> <syb, "val:constructor"> <syb> <op, "("> ... <op, ")"> <op, "{"> ... <op, "}">, output: <constructor_object>

*/
#include "gettkn.h"
#include "sav.h"

#include "terminal/specifiers.h"
#include "terminal/declarators.h"
#include "terminal/operators.h"
#include "terminal/statements.h"

void PrsProc(TmpFileStruc FilStruc, FILE *lexFilPtr){

    setTknFilPtr(lexFilPtr); //Setup the tokens queue

    M_Token tkn = getTkn();

    crtPrsFil(PARSER_TYPE_ONLY_TERMINAL); //Create a `.trm` file

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

/*

(OUTDATED)

The grammar of Mur:

[format: <sent>         (type1 | type2 | ...)                ::=                           <comp1> <comp2> <comp3> | aa <comp2> | ac aaw  ==>                  <output>(type1 | type2 | ...)]
//       ^ Event/Action ^possible types for the component    ^ definition statement quals  ^ a component           ^ "or"         ^string ^output statement    ^output ^possible output types

Available types:

LEXER_SYMBOL, LEXER_STRING, LEXER_CHAR, LEXER_NUMBER, LEXER_OPERATOR, LEXER_BOOLEAN


Core components:

<type_statement>(LEXER_SYMBOL)     ::=  int | float | double | char | string | bool | file
<scope_statement>(LEXER_SYMBOL)    ::=  group | class | function
<value>                            ::=  <>(<type_statement>)
<scope>                            ::=  { [...] }

<symbol>(LEXER_SYMBOL)             !!=  <type_statement> | <scope_statement>

Events/Actions:

<variable_definition_statement>    ::=  <type_statement> <symbol> ==> <variable>(<type_statement>)
<variable>                         ==>  <value>
<value_assignment>                 ::=  <variable> = <value>
<group_definition_statement>       ::=  <scope_statement, "group"> <symbol> <scope>
<class_definition_statement>       ::=  <scope_statement, "class"> <symbol> <scope>
<function_definition_statement>    ::=  <scope_statement, "function"> <symbol> <scope>
<return_statement>                 ::=  return <value>

group MyTest {

    class Program {

        int a = 0;

        function::int Main(string[] envi, int length){

            int b = 0;
            double c = .4, d = 5., e = 0.0;
            string test1 = "Hey, this is a test!";
            char test2 = 'H', test3 = '\'';

            return 0;

        }

        function::void Cmplx(){

            string test1 = "Hey, you can \"do whatever you want\" with 'this'!", test2 = "\"";
            char test3 = '"', test4 = '\'';
            int test5 = 0;
            float test6 = .00005;
            double test6 = .0, test7 = 0.; "\".\" alone will not be seen as a number!";

            bool _test = false, test_ = false, _test_ = true;

        }

    }
    
    class Smth {

        int c = 0;

        function::constructor(){

            this.c = 2;

        }

    }

}

*/