typedef struct {

    int typ; // Token type
    char *val; // Token value

    int defVal1; // Token sub-value 1
    int defVal2; // Token sub-value 2
    int defVal3; // Token sub-value 3
    int defVal4; // Token sub-value 4

    int adtVal1; // Token sub-value 5
    int adtVal2; // Token sub-value 6
    int adtVal3; // Token sub-value 7
    int adtVal4; // Token sub-value 8

    char *srcFil; // Token source file
    int srcLin; // Token source line
    int srcCol; // Token source column

    int __srcLin; //The line this token is stored in
    int __srcLinLen; //The length of this line
    int __ahd_filEnd; //Did the "ahead" function reach the file end?

} M_Token;