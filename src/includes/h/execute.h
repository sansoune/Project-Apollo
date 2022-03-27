#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef enum { PREPARE_SUCCESS, PREPARE_SYNTAX_ERROR, PREPARE_UNRECOGNIZED_STATEMENT } PrepareResult;


typedef enum {
    VARCHAR,
    TEXT,
    BINARY,
    IMAGE,
    VIDEO,
    FLOAT,
    INT,
    DATE,
    TIME,
    BOOL
} ParserType;

typedef struct 
{
    char* buffer;
    size_t buffer_lenght;
    ssize_t input_lenght;
} InputBuffer;

typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementType;

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef struct 
{
    uint32_t id;
    
} Row;

char* read_meta(const char* path);
ParserType parse_meta(char* input);


typedef struct {
  StatementType type;
  Row row_to_insert;
} Statement;

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);
void execute (Statement* statement);

