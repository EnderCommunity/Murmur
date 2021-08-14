int numLen(int num){

    return (num == 0) ? 1 : (floor(log10(abs(num))) + 1);

}