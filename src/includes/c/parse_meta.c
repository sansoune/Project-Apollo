#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../h/execute.h"


	
//make a ParserType function that takes a string and transform it into lines and return the type of each line


ParserType parse_meta(char* input) {
    if(strncmp(input, "varchar", 7) == 0) {
        return VARCHAR;
    }
    if(strncmp(input, "text", 4) == 0) {
        return TEXT;
    }
    if(strncmp(input, "binary", 6) == 0) {
        return BINARY;
    }
    if(strncmp(input, "image", 5) == 0) {
        return IMAGE;
    }
    if(strncmp(input, "video", 5) == 0) {
        return VIDEO;
    }
    if(strncmp(input, "float", 5) == 0) {
        return FLOAT;
    }
    if(strncmp(input, "int", 3) == 0) {
        return INT;
    }
    if(strncmp(input, "date", 4) == 0) {
        return DATE;
    }
    if(strncmp(input, "time", 4) == 0) {
        return TIME;
    }
    if(strncmp(input, "bool", 4) == 0) {
        return BOOL;
    }
   
}