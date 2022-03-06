#include <includes.h>

typedef struct 
{
    char* buffer;
    size_t buffer_lenght;
    ssize_t input_lenght;
} InputBuffer;


InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_lenght = 0;
  input_buffer->input_lenght = 0;

  return input_buffer;
}

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

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

int main(int argc, char **argv[]) {
    InputBuffer* input_buffer = new_input_buffer();
    while (true){
        promt();
        read_input(input_buffer);
        if(strcmp(input_buffer->buffer, "exit") == 0) {
            printf("good bye \n");
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        }else {
            parser(input_buffer->buffer);
        }
        
    }
}