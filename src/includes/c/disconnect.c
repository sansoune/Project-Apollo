#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "../h/dbManager.h"

void disconnect(Pager* pager) {
    close(pager->file_descriptor);
}