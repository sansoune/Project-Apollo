#include "./dbms.h"

int read_meta(const char* filename, FieldInfo **fields, int *field_count) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error: Unable to open meta file\n");
        return 1;
    }

    *field_count = 1;
    char c;
    for (c = getc(fp); c != EOF; c = getc(fp)) {
        if(c == '\n') {
            *field_count+= 1;
        }
    }
    printf("%d", *field_count);

    // Allocate memory for the fields array
    *fields = (FieldInfo *)malloc(*field_count * sizeof(FieldInfo));
    if (!(*fields)) {
        fprintf(stderr, "Error: Unable to allocate memory for fields\n");
        return 1;
    }

    rewind(fp);

    // Read the fields information from the meta file
    for (int i = 0; i < *field_count; i++) {
        if (fscanf(fp, "%s %s", (*fields)[i].name, (*fields)[i].type) != 2) {
            fprintf(stderr, "Error: Invalid field information in meta file\n");
            return 1;
        }
    }

    // Close the meta file
    fclose(fp);

    return 0;
}

const char* turn_it_into_json(FieldInfo *fields, int field_count, const char *data) {
    // Create a JSON object to store the data
    json_t *root = json_object();
    if (!root) {
    fprintf(stderr, "Error: Unable to create JSON object\n");
        exit(1);
    }
    // Loop through the fields and add each field to the JSON object
    for (int i = 0; i < field_count; i++) {
        // Extract the field value from the data string
        const char *start = data;
        for (int j = 0; j < i; j++) {
            start = strstr(start, ",");
            if (!start) {
                fprintf(stderr, "Error: Invalid data format\n");
                exit(1);
            }
            start++;
        }
        const char *end = strstr(start, ",");
        if (!end) {
            end = data + strlen(data);
        }
        int length = end - start;
        char value[length + 1];
        strncpy(value, start, length);
        value[length] = '\0';

        // Add the field to the JSON object
        json_t *json_value = json_string(value);
        // Add the field value to the JSON object
        if (json_object_set_new(root, fields[i].name, json_string(value)) != 0) {
            fprintf(stderr, "Error: Unable to add field value to JSON object\n");
            exit(1);
        }
    }
    // json_dump_file(root, filename, JSON_INDENT(4));
    const char* ttt = json_dumps(root, 0);
    printf("%s", ttt);

    // Free the JSON object
    json_decref(root);

    return ttt;
}


int append_to_file(const char* file_name, FieldInfo *fields, int field_count, const char *data) {
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

    const char* dataa = turn_it_into_json(fields, field_count, data);
    fprintf(file, "%s]", dataa);
    fclose(file);
    return 0;
}

int insert_data(const char* file_name, FieldInfo *fields, int field_count, const char *data) {
    int file_count = 0;
    char file_buffer[256];
    while (1)
    {
        sprintf(file_buffer, "%s_%d.json", file_name, file_count);
        FILE* file = fopen(file_buffer, "r");
        if(!file) {
            return append_to_file(file_buffer, fields, field_count, data);
        }
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        fclose(file);
        if(file_size >= MAX_FILE_SIZE) {
            file_count++;
        }else {
            return append_to_file(file_buffer, fields, field_count, data);
        }
        

    }
}