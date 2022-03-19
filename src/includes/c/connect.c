#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../h/dbManager.h"



Pager* connect(char* connecti) {
    connecti += 8;
    strcat(connecti, ".db");
    char path[100];
    strcpy(path, "database/");
    strcat(path, connecti);
    if(access(path, F_OK) != -1){
        int fd = open(path, O_RDWR, S_IWUSR | S_IRUSR );
        if (fd == -1) {
            printf("Unable to open file\n");
            exit(EXIT_FAILURE);
        }
    
        // off_t file_length = lseek(fd, 0, SEEK_END);
        Pager* pager = malloc(sizeof(Pager));
        pager->file_descriptor = fd;
        pager->file_length = 1000;
        printf("connected to db %s \n", connecti);
        return pager;
    }else {
        printf("file does not exist please create it \n");
    }
}

