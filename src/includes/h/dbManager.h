#include <stdint.h>
void create(char* string);

#define TABLE_MAX_PAGES 100

typedef struct {
  int file_descriptor;
  uint32_t file_length;
  void* pages[TABLE_MAX_PAGES];
} Pager;

Pager* connect(char* connecti);

void disconnect(Pager* pager);