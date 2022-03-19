#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "includes/h/dbManager.h"
#include "includes/h/execute.h"
#include <stdint.h>
#include <fcntl.h>



typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;


void promt() {
    printf("Apollo > ");
}

void read_input(InputBuffer* input_buffer) {
    ssize_t bytes = getline(&(input_buffer->buffer), &(input_buffer->buffer_lenght), stdin);

    if (bytes <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    // Ignore trailing newline
    input_buffer->input_lenght = bytes - 1;
    input_buffer->buffer[bytes - 1] = 0;
}
InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_lenght = 0;
  input_buffer->input_lenght = 0;

  return input_buffer;
}

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

Pager* pager;
MetaCommandResult execute_command(InputBuffer* input_buffer) {
    if(strcmp(input_buffer->buffer, "exit") == 0) {
        exit(EXIT_SUCCESS);
    }if(strstr(input_buffer->buffer, "create") != NULL){
        create(input_buffer->buffer);
        return META_COMMAND_SUCCESS;
        
    }if(strncmp(input_buffer->buffer, "connect", 7) == 0){
        pager = connect(input_buffer->buffer);
        // read_meta();
        return META_COMMAND_SUCCESS;
    }if(strncmp(input_buffer->buffer, "disconnect", 10) == 0) {
        disconnect(pager);
        return META_COMMAND_SUCCESS;
    }else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}
Statement statement;
int main(int argc, char **argv[]) {
    InputBuffer* input_buffer = new_input_buffer();
    while (true){
        promt();
        read_input(input_buffer);
        switch (execute_command(input_buffer)) {
            case (META_COMMAND_SUCCESS):
                break;
            case (META_COMMAND_UNRECOGNIZED_COMMAND):
                switch (prepare_statement(input_buffer, &statement))
                {
                    case (PREPARE_SUCCESS):
                        break;
                    case(PREPARE_UNRECOGNIZED_STATEMENT):
                        printf("this sql statement %s does not exist \n", input_buffer->buffer);
                        continue;
                }
                execute(&statement);
                printf("Executed \n");
                continue;
        }
        
    }
}