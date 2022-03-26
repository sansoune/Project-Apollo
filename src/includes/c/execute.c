#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../h/execute.h"

void execute(Statement*  statement) {
    switch (statement->type)
    {
    case (STATEMENT_INSERT): ;
        // printf("it's an insert statement");
        char* source = read_meta("yassine.meta");
        printf("%s \n", source);
        free(source);
        break;
    
    case (STATEMENT_SELECT):
        printf("this is a select statement");
        break;
    }
}