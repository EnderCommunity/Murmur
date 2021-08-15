/* All error messages should be saved here!*/

//You can also create sub-values for each variable (if needed)

//Compiler (software-only) (MSG_CMP_...)
//#define MSG_CMP_

//Preprocessor (MSG_PPC_...)
//#define MSG_PPC_

//"preprocessor/linker.h"
#define MSG_PPC_LINKER_IMPORT_CLOSINGQUOTE "The string closing quote is missing!"
#define MSG_PPC_LINKER_IMPORT_SEMICOLON "Expected a semicolon (;) at the end of the `import` method!"
#define MSG_PPC_LINKER_IMPORT_INCORRECTFILETYPE "File with an unknown extension was imported!"
#define MSG_PPC_LINKER_IMPORT_INACCESSIBLEFILE "Inaccessible file was imported! (This file does not exist, or may be in use)"
#define MSG_PPC_LINKER_IMPORT_NOSTRINGINPUT "Invalid input was passed to the `import` method"
#define MSG_PPC_LINKER_IMPORT_NOINPUT "No input was passed to the `import` method"

//"preprocessor/reader.h"
#define MSG_PPC_READER_MLCOMMENTEND "End of file has been reached, and the comment wasn't closed!"
#define MSG_PPC_READER_SPRZONEEND "End of file has been reached, and the separate zone wasn't closed!"


//Lexer (MSG_LXR_...)
//#define MSG_LXR_


//Parser (MSG_PRS_...)
//#define MSG_PRS_


//Optimiser (MSG_OPT_...)
//#define MSG_OPT_


//Evaluator (MSG_EVL_...)
//#define MSG_EVL_


//Bundler (MSG_BND_...)
//#define MSG_BND_


//C-related/C Compiler (MSG_C_...)
//#define MSG_C_

