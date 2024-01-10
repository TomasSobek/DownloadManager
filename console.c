#include "console.h"
#include "sockets.h"
#include "compression/compression.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFFER_SIZE 256

char *dynamic_fgets(void) {
    char *buffer = NULL;
    size_t size = 0;
    getline(&buffer, &size, stdin);

    if (buffer) {
        size_t length = strlen(buffer);
        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0'; // Remove newline character
        }
    }

    return buffer;
}

int file_exists(const char *path) {
    struct stat buffer;
    return (stat(path, &buffer) == 0);
}

char *get_valid_file_path(void) {
    char *path;
    do {
        printf("Enter file path: ");
        path = dynamic_fgets();

        if (!path) {
            printf("Error reading input.\n");
            continue;
        }

        if (!file_exists(path)) {
            printf("File not found: %s\n", path);
            free(path);
            path = NULL;
        }
    } while (!path);
    return path;
}


void console_main(void) {
    while (1) {
        char mode;
        // char input_buffer[BUFFER_SIZE];
        printf("Choose a mode:\n");
        printf("'r', Receiver Mode\n");
        printf("'s', Sender Mode\n");
        printf("'h', Huffman Mode\n");
        printf("'e', Exit\n");
        printf("Enter your choice: ");

        scanf(" %c", &mode);
        getchar();

        if (mode == 'r') {
            receiver_mode();
        } else if (mode == 's') {
            sender_mode();
        } else if (mode == 'h') {
            huffman_mode();
        } else if (mode == 'e') {
            printf("Exiting the program.\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
 }

// basic console functions
void receiver_mode(void) {
    unsigned int port;
    char file_path[256];

    char *fp;
    // char* file_path = "/home/sobek3/client2_files/receiv.txt";
    printf("Select a port: ");
    scanf("%d", &port);
    getchar();

    if (port < 1000 || port > 65535) {
        printf("Not a valid port (1000 < port < 65535). Your option: %d\n", port);
        return;
    }

    //printf("Select file path for incoming file: ");
    //get_string(file_path);
    fp = get_valid_file_path();

    receive_file_tcp(port, fp);
    free(fp);
}
void sender_mode(void) {
    unsigned int port;
    //char file_path[256];
    char *fp;
    //char* file_path = "/home/sobek3/client1_files/send.txt";
    printf("Select a port: ");
    scanf(" %d", &port);

    if (port < 1000 || port > 65535) {
        printf("Not a valid port (1000, port, 65535). Your option: %d\n", port);
        return;
    }
    // clear_input_buffer();
    //printf("Select file path for sending file: ");
    fp = get_valid_file_path();
    send_file_tcp("localhost", port, fp);
    free(fp);
}
void huffman_mode(void) {

}
void execute_command(const char *command);

// linux commands functions
void ls_command(void);
void mkdir_command(void);
void rmdir_command(void);