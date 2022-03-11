#include <fcntl.h>

void create(char* string) {
    int fd;
    fd = creat("apollo.db", S_IRUSR | S_IWUSR);
}