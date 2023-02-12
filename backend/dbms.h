#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

#define MAX_FILE_SIZE 1000000000 // 1 GB
// #define MAX_FILE_SIZE 4000 // 1 GB
#define MAX_TEXT_LENGTH 100000
#define MAX_TOPIC_LENGTH 100
#define MAX_INTENTION_LENGTH 100
#define MAX_FIELD_LENGTH 32

typedef struct {
    char text[MAX_TEXT_LENGTH];
    char topic[MAX_TOPIC_LENGTH];
    char intention[MAX_INTENTION_LENGTH];
} DataRecord;


typedef struct {
char name[MAX_FIELD_LENGTH];
char type[MAX_FIELD_LENGTH];
} FieldInfo;

int append_to_file(const char* file_name, FieldInfo *fields, int field_count, const char *data);
int insert_data(const char* file_name, FieldInfo *fields, int field_count, const char *data);
int read_meta(const char* filename, FieldInfo **fields, int *field_count);