#include <fcntl.h>
#include <stdio.h>
#include <string.h>

void create(char* string) {
    string += 7;
    strcat(string, ".db");
    char path[] = "database/";
    strcat(path, string);
    creat(path, S_IRUSR | S_IWUSR);
    printf("executed \n");
    
}