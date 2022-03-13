#include <stdint.h>
void create(char* string);

typedef struct {
  int file_descriptor;
  uint32_t file_length;
  void* pages[10000];
} Pager;

Pager* connect(char* connecti);