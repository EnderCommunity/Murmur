typedef struct {

    int typ;
    char *val;

    int defVal1;
    int defVal2;
    int defVal3;
    int defVal4;

    int adtVal1;
    int adtVal2;
    int adtVal3;
    int adtVal4;

    char *srcFil;
    int srcLin;
    int srcCol;

    int __srcLin; //The line this token is stored in
    int __srcLinLen; //The length of this line
    int __ahd_filEnd; //Did the "ahead" function reach the file end?

} M_Token;