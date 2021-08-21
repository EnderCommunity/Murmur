//You will find all the environment variables here.



//Files

#define MAX_LINE_LENGTH 509 //The maximum line length in files
#define MAX_PATH_LENGTH 255 //The maximum path length
#define MAX_FILE_NAME_LENGTH 150 //The maximum file name length


//Strings

/* (!) Still not implemented */ #define MAX_LONG_STRING_LENGTH 819208 //The maximum long string length
/* (!) Still not implemented */ #define MAX_NORMAL_STRING_LENGTH 2048 //The maximum normal string length
/* (!) Still not implemented */ #define MAX_SHORT_STRING_LENGTH 256 //The maximum short string length
#define FILLER_STRING_CHAR '\t' //The character used to generate a filler string
#define FILLER_STRING_CHAR_TYP_STR "\t" //The character used to generate a filler string (in a string type)
#if _WIN64 || _WIN32

    #define END_OF_LINE_COUNT 0 //Does the end-of-line character effect the `strlen()` function?

#else

    #define END_OF_LINE_COUNT 1 //Does the end-of-line character effect the `strlen()` function?

#endif


//Paths

#if _WIN64 || _WIN32

    #define PATH_SLASH "\\"
    #define PATH_SLASH_TYP_CHAR '\\'

#else

    #define PATH_SLASH "/"
    #define PATH_SLASH_TYP_CHAR '/'

#endif


//Input (needed directoies and files)
#define MUR_FILEEXT ".mur"
#define MUR_LIB_FILEEXT ".lib.mur"
#if _WIN64 || _WIN32 //Windows

    #define C_COMPILER_EXECUTABLE_DIR "C:\\msys64\\mingw64\\bin\\gcc.exe"
    #define MUR_LIBRARIES_DIR "resources\\libraries\\"
    #define SYSTEM_TMP_DIR "%%temp%%/"

#elif __APPLE__ //macOS

    #define C_COMPILER_EXECUTABLE_DIR "gcc"
    #define MUR_LIBRARIES_DIR "resources/libraries/"
    #define SYSTEM_TMP_DIR "/var/TMP"

#else //Linux

    #define C_COMPILER_EXECUTABLE_DIR "gcc"
    #define MUR_LIBRARIES_DIR "resources/libraries/"
    #define SYSTEM_TMP_DIR "/var/tmp/"

#endif


//Output (NOTE: some of these files might still get generated in the `/tmp` directory)

#define REMOVE_WHITESPACE_AT_LINE_START 1 //Remove the extra whitespace at the start of each line
#define REMOVE_WHITESPACE_AT_LINE_END 1 //Remove the extra whitespace at the end of each line
#define OUTPUT_LOG_FILE 1 //Output a `.log` file (Logs files may affect the speed of
//the compiler severely. The log file stream is constantly closed and re-opened to
//ensure that the user will get the logs even when the compiler crashes.)
#define OUTPUT_TEMP_FILE 1 //Output a `.tmp` file (stage one code)
/* (!) Still not implemented */ #define OUTPUT_C_CODE_FILE 0 //Output a `.c` file (stage two code)
#define OUTPUT_EXECUTABLE 1 //Output an executable file (stage three code)
#if _WIN64 || _WIN32 //Windows

    #define OUTPUT_EXECUTABLE_EXT ".exe" //Output executable ext

#elif __APPLE__ //macOS

    #define OUTPUT_EXECUTABLE_EXT "" //Output executable ext

#else //Linux

    #define OUTPUT_EXECUTABLE_EXT ".out" //Output executable ext

#endif



//Preprocessor

#define ENABLE_PREPROCESSOR_METHODS 1 //Enable preprocessor methods (will not effect the header method)
#define ENABLE_PREPROCESSOR_HEADER 1 //Enable the `#header` super-method
#define ENABLE_ALLOW_SEPARATE_FLAG 0 //Enable the header `allow-separate` flag
#define ENABLE_USING_STATEMENT 1 //Enable the `using` statement
#define ENABLE_IMPORT_STATEMENT 1 //Enable the `import` statement
#define ENABLE_TELL_STATEMENT 1 //Enable the `tell` statement
#define ENABLE_SETSIZE_STATEMENT 1 //Enable the `setsize` statement
#define ENABLE_DEFINE_STATEMENT 1 //Enable the `define` statement


//Comments

#define ENABLE_COMMENTS 1 //Enable comments detection an filtering
#define SUPPORT_LINEAR_COMMENTS 1 //The compiler will identify and remove linear comments from your code when this option is enabled
#define SUPPORT_MULTI_LINEAR_COMMENTS 1 //The compiler will identify and remove multi-linear comments from your code when this option is enabled


//Data

#define DATA_PATH 'A'
#define DATA_PATH_STR "A"
#define DATA_ZONE 'B'
#define DATA_ZONE_STR "B"


//Lexer

#define LEXER_SYMBOL 1001
#define LEXER_SYMBOL_STR "1001"
#define LEXER_STRING 1002
#define LEXER_STRING_STR "1002"
#define LEXER_CHAR 1003
#define LEXER_CHAR_STR "1003"
#define LEXER_NUMBER 1004
#define LEXER_NUMBER_STR "1004"
#define LEXER_OPERATOR 1005
#define LEXER_OPERATOR_STR "1005"
#define LEXER_BOOLEAN 1006
#define LEXER_BOOLEAN_STR "1006"
#define LEXER_ZONE_LINE 1007
#define LEXER_ZONE_LINE_STR "1007"
#define LEXER_HEX 1008
#define LEXER_HEX_STR "1008"


//States

/* (!) Still not implemented */ #define ENABLE_STATES 1 //Functions, groups, and classes will be forced to have a state definition (If disabled, all states will be set to 'public' with no way to change that)


//Compiler Process Termination

#define DEBUG_ALLOW_TERMINATION 0 //Allow errors to terminate the compiling process (Use this when you need to test errors & warnings)
/* (!) Still not implemented */ #define EMPTY_COMPILER_TMP_DIR 0 //Empty the `/compiler/tmp/` directory at the end of every process


//Commands

#if _WIN64 || _WIN32

    #define SYSTEM_COMMANDS_PAUSE system("pause") //The pause command

#else

    #define SYSTEM_COMMANDS_PAUSE system("read -r -p \"Press enter to continue...\" key") //The pause command (NOTE: '-n1' is not working for some reason)

#endif


//Errors and Warnings

#define REPORT_CODE_ERROR 2
#define REPORT_CODE_WARNING 1
#define REPORT_CODE_MESSAGE 0
#define REPORT_SECTION_GENERAL 1
#define REPORT_SECTION_PREPROCESSOR 2
#define REPORT_SECTION_LEXER 3
#define REPORT_SECTION_PARSER 4
#define REPORT_SECTION_OPTIMISER 5
#define REPORT_SECTION_EVALUATOR 6
#define REPORT_SECTION_BUNDLER 7
#define REPORT_SECTION_C 8
#define REPORT_SECTION_RUNTIME 9

#define ERROR_STR_OUTOFBOUNDS "::ERR_OOB::" //an "out of bounds" error string
