int isSyb(char chr){
    return (regChk("[_a-zA-Z]", &chr) && (!isCharSpcl(chr) || chr == '_'));
}

int isSybE(char chr){
    return (regChk("[_a-zA-Z0-9]", &chr) && (!isCharSpcl(chr) || chr == '_'));
}

int isThrMor(char chr){
    return ((isSyb(chr) || regChk("[0-9]", &chr)) && !isspace(chr));
}