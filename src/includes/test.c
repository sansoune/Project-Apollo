#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

void test(int fd, char* striing) {
    striing += 7;
    write(fd, striing, strlen(striing));
}