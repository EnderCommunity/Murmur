/* All error messages should be saved here!*/

//You can also create sub-values for each variable (if needed)

//Compiler (software-only) (MSG_CMP_...)
//#define MSG_CMP_

//Preprocessor (MSG_PPC_...)
//#define MSG_PPC_

//"preprocessor/linker.h"
#define MSG_PPC_LINKER_INCORRECTFILETYPE "File with an unknown extension was imported!"
#define MSG_PPC_LINKER_IMPORT_CLOSINGQUOTE "The string closing quote is missing!"
#define MSG_PPC_LINKER_IMPORT_SEMICOLON "Expected a semicolon (;) at the end of the `import` method!"
#define MSG_PPC_LINKER_IMPORT_INACCESSIBLEFILE "Inaccessible file was imported! (This file does not exist, or may be in use)"
#define MSG_PPC_LINKER_IMPORT_NOSTRINGINPUT "Invalid input was passed to the `import` method"
#define MSG_PPC_LINKER_IMPORT_NOINPUT "No input was passed to the `import` method"
#define MSG_PPC_LINKER_TELL_CLOSINGQUOTE "The string closing quote is missing!"
#define MSG_PPC_LINKER_TELL_SEMICOLON "Expected a semicolon (;) at the end of the `tell` method!"
//#define MSG_PPC_LINKER_TELL_INCORRECTFORMAT "Incorrect data format (Correct format is TYPE::DATA1:DATA2)"
#define MSG_PPC_LINKER_TELL_NOSTRINGINPUT "Invalid input was passed to the `tell` method"
#define MSG_PPC_LINKER_TELL_NOINPUT "No input was passed to the `tell` method"
#define MSG_PPC_LINKER_USING_NODIGITSATSTART "Using numbers at the start of a symbol is not allowed!"
#define MSG_PPC_LINKER_USING_RESTRICTEDNAMING "You can only use letters, underscores (_), and numbers to specify a library path!"
#define MSG_PPC_LINKER_USING_EMPTYSECTION "Sections can't be left empty!"
#define MSG_PPC_LINKER_USING_SEMICOLON "Expected a semicolon (;) at the end of the `using` method!"
#define MSG_PPC_LINKER_USING_INACCESSIBLEFILE "Inaccessible library was imported! (This library does not exist)"
#define MSG_PPC_LINKER_DEFINE_MISSINGNAME "No name was passed to the `define` method"
#define MSG_PPC_LINKER_DEFINE_MISSINGVALUE "No value was passed to the `define` method"
#define MSG_PPC_LINKER_DEFINE_SEMICOLON "Expected a semicolon (;) at the end of the `define` method!"
#define MSG_PPC_LINKER_DEFINE_NODIGITSATSTART "Using numbers at the start of a symbol is not allowed!"
#define MSG_PPC_LINKER_DEFINE_RESTRICTEDNAMING "You can only use letters, underscores (_), and numbers to name a constant!"

//"preprocessor/reader.h"
#define MSG_PPC_READER_MLCOMMENTEND "End of file has been reached, and the comment wasn't closed!"
#define MSG_PPC_READER_SPRZONEEND "End of file has been reached, and the separate zone wasn't closed!"

//"preprocessor/process.h"
#define MSG_PPC_PROCESS_FLAGCLOSINGQUOTEMISSING "Flag closing quote is missing!"
#define MSG_PPC_PROCESS_FLAGEMPTY "Flag is empty!"
#define MSG_PPC_PROCESS_FLAGUNKNOWN "Unknown flag!"


//Lexer (MSG_LXR_...)
//#define MSG_LXR_

//"lexical/lex.h"
#define MSG_LXR_LEX_UNKNOWNCHAR "Unknown character has been detected!"


//Parser (MSG_PRS_...)
//#define MSG_PRS_

//"parser/terminal/specifiers.h"
#define MSG_PRS_TRM_SPC_ARRAYDEFFNOTCLOSED "Array was not closed!"

//"parser/prs.h"
#define MSG_PRS_VARNAMEMISSING "No name is present for the variable!"
#define MSG_PRS_FUNCRETURNTYPEMISSING "No valid return type is present for the function!"
#define MSG_PRS_FUNCNAMEMISSING "No valid name is present for the function!"
#define MSG_PRS_FUNCRETURNOPMISSING "Return-type declarative operator is not present!"
#define MSG_PRS_GROUPNAMEMISSING "No valid name is present for the group!"
#define MSG_PRS_INCORRECTUSEOFSTATE "Incorrect use of the `public`/`private` state keyword!"
#define MSG_PRS_MISSINGSTRUCTVALUE "Missing structure-related/zone-related value!"
#define MSG_PRS_SETSIZEINVALIDSIZEINPUT "Invalid `setsize` size input!"
#define MSG_PRS_SETSIZEINVALIDTYPEINPUT "Invalid `setsize` type input!"
#define MSG_PRS_DOTINVALIDFOLLOWUP "Dot (.) operator not followed by a valid continuation!"
#define MSG_PRS_FUNCINVALIDRETURNTYPESPECIF "No valid return type is present for the function call!"
#define MSG_PRS_DELETEMISSINGINPUT "Missing valid `delete` input!"
#define MSG_PRS_DELETEMISSINGEND "Expected a semicolon (;) at the end of the delete method!"
#define MSG_PRS_VAR_NOVALIDTYPE "No valid type is present for the variable!"
#define MSG_PRS_INFOINDIC_INVALIDINFO "No valid info is present after the data indicator (::)/(:)!"
#define MSG_PRS_VAR_NOVALIDNAME "No valid name is present for the variable!"
#define MSG_PRS_VAR_SEMICOLON "Expected a semicolon (;) at the end of the variable definition!"
#define MSG_PRS_VAR_INVALIDSUBVAR "Invalid (sub) variable name!"
#define MSG_PRS_VAR_INVALIDDECLASSIGNMENT "Invalid variable assignment!"
#define MSG_PRS_CLASS_NAMEMISSING "No valid name is present for the class!"
#define MSG_PRS_GROUP_NAMEMISSING "No valid name is present for the group!"
#define MSG_PRS_FUNCTION_NOVALIDTYPE "No valid return type is present for the function!"
#define MSG_PRS_FUNCTION_NOVALIDNAME "No valid name is present for the function!"
#define MSG_PRS_IF_CONDITIONSINSIDEPARENTHESES "The `if` statement only accepts conditions inside parentheses!"


//Optimiser (MSG_OPT_...)
//#define MSG_OPT_


//Evaluator (MSG_EVL_...)
//#define MSG_EVL_


//Bundler (MSG_BND_...)
//#define MSG_BND_


//C-related/C Compiler (MSG_C_...)
//#define MSG_C_

