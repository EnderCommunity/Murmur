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
#define MSG_PPC_LINKER_USING_RESTRICTEDNAMING "You can only use letters, underscores (_), and number to specify a library path!"
#define MSG_PPC_LINKER_USING_EMPTYSECTION "Sections can't be left empty!"
#define MSG_PPC_LINKER_USING_SEMICOLON "Expected a semicolon (;) at the end of the `using` method!"
#define MSG_PPC_LINKER_USING_INACCESSIBLEFILE "Inaccessible library was imported! (This library does not exist)"

//"preprocessor/reader.h"
#define MSG_PPC_READER_MLCOMMENTEND "End of file has been reached, and the comment wasn't closed!"
#define MSG_PPC_READER_SPRZONEEND "End of file has been reached, and the separate zone wasn't closed!"


//Lexer (MSG_LXR_...)
//#define MSG_LXR_

//"lexical/lex.h"
#define MSG_LXR_LEX_UNKNOWNCHAR "Unknown character has been detected!"


//Parser (MSG_PRS_...)
//#define MSG_PRS_

//"parser/terminal/specifiers.h"
#define MSG_PRS_TRM_SPC_ARRAYDEFFNOTCLOSED "Array was not closed!"


//Optimiser (MSG_OPT_...)
//#define MSG_OPT_


//Evaluator (MSG_EVL_...)
//#define MSG_EVL_


//Bundler (MSG_BND_...)
//#define MSG_BND_


//C-related/C Compiler (MSG_C_...)
//#define MSG_C_

