typedef struct{ //An array object

    int length;
    int *cLength;
    char *type;

    union content{

        char cha;
        char *str;
        int intg;
        int intg;

    };

} Array;

typedef struct{ //A multidimensional array object

    int length;
    int dimensions;

} MDArray;