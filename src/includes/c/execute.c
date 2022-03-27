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
        char* line = strtok(source, "\n");
        while (line != NULL)
        {
            
            switch (parse_meta(line))
            {
            case VARCHAR:
                printf("it's a varchar \n");
                break;
            case TEXT:
                printf("it's a text\n");
                break;
            case BINARY:
                printf("it's a binary\n");
                break;
            case IMAGE:
                printf("it's an image\n");
                break;
            case VIDEO:
                printf("it's a video\n");
                break;
            case FLOAT:
                printf("it's a float\n");
                break;
            case INT:
                printf("it's an int\n");
                break;
            case DATE:
                printf("it's a date\n");
                break;
            case TIME:
                printf("it's a time\n");
                break;
            case BOOL:
                printf("it's a bool\n");
                break;
            
            
            }
            line = strtok(NULL, "\n");
        }

        
        
        free(source);
        break;
    
    case (STATEMENT_SELECT):
        printf("this is a select statement");
        break;
    }
}