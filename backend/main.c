#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "dbms.h"

#define PORT 5000
#define MAX_CLIENTS 10
#define BUFFER 1000000


struct apollo_request
{
    char type;
    char resource[20];
    char data[BUFFER];
};

struct apollo_response 
{
    char status;
    unsigned int size;
    char data[20];
    int code;
};

FieldInfo *fields;
int field_count;

int Post_method(const char *data) {
    int result = insert_data("database/data", fields, field_count, data);
    if (result == 1) {
        printf("Failed to insert data.");
        return 1;
    }

    printf("Data inserted successfully.");
    free(fields);
    return 0;
}

void *handle_connection(void* p_client_socket) {
    int client_socket = *(int *)p_client_socket;
    free(p_client_socket);
    struct apollo_request request;
    struct apollo_response response;
    while(recv(client_socket, &request, sizeof(request), 0) > 0)
    {
        // Process the request and create a response
        // ...
        char protocol[8] = { 0 };
        sscanf(request.resource, "%7[^:]://", protocol);

        if(strcmp(protocol, "Apollo") == 0) {
            printf("%c \n %s \n %s \n", request.type, request.resource, request.data);
            switch (request.type)
            {
            case 'G':
                printf("its a get method \n");
                break;
            case 'P':
                printf("its a post method \n");
                json_error_t error;
                json_t *root = json_loads(request.data, 0, &error);

                if(!root)
                {
                    printf("Error parsing JSON: on line %d: %s\n", error.line, error.text);
                    return NULL;
                }
                const char* key;
                json_t *value;
                char string[1024];
                int offset = 0;
                json_object_foreach(root, key, value) {
                     if (json_is_string(value)) {
                        offset += snprintf(string + offset, 1024 - offset, "%s,", json_string_value(value));
                    } else if (json_is_integer(value)) {
                        offset += snprintf(string + offset, 1024 - offset, "%lld,", json_integer_value(value));
                    }
                }
                string[offset - 1] = '\0';
                printf("test : %s", string);
                json_decref(root);
                Post_method(string);
            }
            response.status = 'K';
            response.code = 601;
            strcpy(response.data, "status good");
        }else {
            return NULL;
        }


        // Send the response back to the client
        send(client_socket, &response, sizeof(response), 0);
    }
    return NULL;

}



int main(int argc, char **argv[]) {
    int server_socket, client_socket;
    struct sockaddr_in server, client;

    
    read_meta("test.meta", &fields, &field_count);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0) {
        perror("ERROR: can't create a socket\n");
        exit(EXIT_FAILURE);
    }
    printf("[+] Socket created \n");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);


    if(bind(server_socket, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("ERROR: can't bind server\n");
        exit(EXIT_FAILURE);
    }

    listen(server_socket, MAX_CLIENTS);
    printf("[+] Waiting for connections \n");

    int addrlen = sizeof(struct sockaddr_in);
    while(1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client, (socklen_t*)&addrlen);
        if (client_socket < 0)
        {
            perror("Error accepting client connection");
            exit(EXIT_FAILURE);
        }
	    pthread_t t;
	    int *pclient = malloc(sizeof(int));
	    *pclient = client_socket;
	    pthread_create(&t, NULL, handle_connection, pclient);
    }

    return 0;
}

