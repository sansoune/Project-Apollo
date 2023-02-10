#include "./dbms.h"

int append_to_file(const char* file_name, DataRecord* record) {
    FILE* file_delete = fopen(file_name, "r+");
    if(!file_delete) {
        return 1;
    }
    // fseek(file_delete, -1, SEEK_END);
    // fwrite(" ", 1, 1, file_delete);
    // fclose(file_delete);

    FILE* file = fopen(file_name, "a");
    if (!file) {
        return 1;
    }

    if (ftell(file) == 0) {
        fprintf(file, "[\n");
    } else {
        fseek(file_delete, -1, SEEK_END);
        fwrite(" ", 1, 1, file_delete);
        fclose(file_delete);
        fprintf(file, ",\n");
    }
    // Write the data to the file in JSON format
    fprintf(file, "{\"text\": \"%s\", \"topic\": \"%s\", \"intention\": \"%s\"}]", record->text, record->topic, record->intention);
    fclose(file);
    return 0;
}

int insert_data(const char* file_name, DataRecord* record) {
    int file_count = 0;
    char file_buffer[256];
    while (1)
    {
        sprintf(file_buffer, "%s_%d.json", file_name, file_count);
        FILE* file = fopen(file_buffer, "r");
        if(!file) {
            return append_to_file(file_buffer, record);
        }
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        fclose(file);
        if(file_size >= MAX_FILE_SIZE) {
            file_count++;
        }else {
            return append_to_file(file_buffer, record);
        }
        

    }
}