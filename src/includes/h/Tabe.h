#include <stdint.h>
#include "dbManager.h"
#define TABLE_MAX_PAGES 100

typedef struct
{
    uint32_t num_rows;
    Pager* pager;
} Table;
