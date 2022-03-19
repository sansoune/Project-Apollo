#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h> 


void read_meta() {
    char c[100];
    int fd = open("yassine.meta", O_RDONLY, S_IRUSR);
    read(fd, &c, 100);
    int b = 0;
    for (int i = 0; i < sizeof(c); i++)
    {
        printf("%c \n", c[i]);
        // if (c[i] == ';' ) {
        //     printf("%.*s \n", i+1, c+b);
        //     b=i+1;
        // }if (c[i] == '\0') {
        //     b++;
        // }
    }
    
}
