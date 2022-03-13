#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void create(char* string) {
    string += 7;
    strcat(string, ".db");
    char path[100];
    strcpy(path, "database/");
    strcat(path, string);
    if (access(path, F_OK) != -1){
        printf("file exists \n");
    }
    else {
        creat(path, S_IRUSR | S_IWUSR);
        printf("executed \n");
    }
}