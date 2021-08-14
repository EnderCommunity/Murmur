int hexToInt(char *hex){

    int dec = 0, base = 1;
    int i = 0, value, length;
    length = strlen(hex);

    for(i = length--; i >= 0; i--){

        if(hex[i] >= '0' && hex[i] <= '9'){

            dec += (hex[i] - 48) * base;
            base *= 16;

        }else if(hex[i] >= 'A' && hex[i] <= 'F'){

            dec += (hex[i] - 55) * base;
            base *= 16;

        }else if(hex[i] >= 'a' && hex[i] <= 'f'){

            dec += (hex[i] - 87) * base;
            base *= 16;

        }

    }

    free(hex);

    return dec;
}

char *intToHex(int dec){

    char *hex;

    strcpy(hex, "000000000");
    sprintf(hex, "%09X", dec);

	return hex;

}