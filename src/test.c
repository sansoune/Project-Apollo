#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 


void read_meta() {
    FILE* fd;
    // int display;
    char c;

    fd = fopen("yassine.meta", "r");
    // printf("%s", fgets(c, 1000, fd));
    // c = fgetc(fd);
    // printf("%c", c);
    c = fgetc(fd);
    while (1)
    {
        printf("%c", c);
        c = fgetc(fd);
        if (c == EOF) {
            break;
        }
    }
    
    fclose(fd);
    
    

    
}

int main(void) {
    read_meta();
    return 0;
}