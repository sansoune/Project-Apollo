#include <stdio.h>
#include <stdlib.h>
#include "../h/execute.h"



char* read_meta(const char* path) {
    FILE* file = fopen(path, "r"); // open the file
    if (file == NULL) {
        printf("Unable to open file\n");
        return NULL;
    } 
    fseek(file, 0, SEEK_END); // seek to end of file
    int file_size = ftell(file); // get current file size
    fseek(file, 0, SEEK_SET); // seek back to beginning of file

    char * buf = (char*) malloc(sizeof(char) * (file_size + 1)); // allocate memory to contain the whole file
    fread(buf, file_size, 1, file); // read the file into memory
    buf[file_size] = '\0'; // add a null terminator
    fclose(file); // close the file

    return buf; // return the file as a string
}
