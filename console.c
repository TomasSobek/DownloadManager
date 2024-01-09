#include "console.h"
#include "sockets.h"
#include "compression/compression.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFFER_SIZE 256

// checking if file exists
static _Bool is_file_exists(const char *file_path) {
    struct stat fileStat;
    if (stat(file_path, &fileStat) == 0) {
        if (S_ISREG(fileStat.st_mode)) {
            return true;        // is a file
        } else if (S_ISDIR(fileStat.st_mode)) {
            return false;       // is a directory
        }
    }
    return false;
}

// checking file path for file creation
static _Bool is_file_creation_path_valid(const char *file_path) {
    if (access(file_path, F_OK) == -1) {
        return true;
    } else {
        return false;
    }
}

static void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

static void get_string(char* buffer) {
    if (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
    } else {
        printf("Error reading input.\n");
    }
    clear_input_buffer();
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
    while (1) {
        char choice;
        char input_buffer[BUFFER_SIZE];
        printf("You are entering the receiver mode, make your choice:\n");
        printf("'c', Execute command\n");
        printf("'r', start receiving files\n");
        printf("'e', exit mode\n");

        printf("Enter choice: ");
        scanf(" %c", &choice);
        getchar();

        if (choice == 'c') {

        } else if (choice == 'r') {
            int port;
            // char file_path[BUFFER_SIZE];
            char* file_path = "/home/sobek3/client2_files/receiv.txt";
            printf("Select a port: ");
            scanf("%d", &port);
            getchar();

            if (port < 1000 || port > 65535) {
                printf("Not a valid port (1000 < port < 65535). Your option: %d\n", port);
                break;
            }

            //printf("Select file path for incoming file: ");
            // get_string(file_path);
            receive_file_tcp(port, file_path);

        } else if (choice == 'e') {
            printf("Exiting receiver mode...\n");
            break;
        } else {
            printf("Wrong option, try again.\n");
        }
    }
}
void sender_mode(void) {
    while(1) {
        char choice;
        printf("You are entering the sender mode, make your choice:\n");
        printf("'c', Execute command\n");
        printf("'s', start sending files\n");
        printf("'e', exit mode\n");

        printf("Enter your choice: ");
        scanf(" %c", &choice);

        if (choice == 'c') {

        } else if (choice == 's') {
            unsigned int port;
            //char file_path[BUFFER_SIZE];
            char* file_path = "/home/sobek3/client1_files/send.txt";
            printf("Select a port: ");
            scanf(" %d", &port);

            if (port < 1000 || port > 65535) {
                printf("Not a valid port (1000, port, 65535). Your option: %d\n", port);
                break;
            }
            // clear_input_buffer();
            //printf("Select file path for sending file: ");
            //get_string(file_path);

            send_file_tcp("localhost", port, file_path);
        } else if (choice == 'e') {
            printf("Exiting receiver mode...\n");
            break;
        } else {
            printf("Wrong option, try again.\n");
        }
    }
}
void huffman_mode(void) {
    while (1) {
        char choice;
        printf("You are entering the huffman compression mode, make your choice:\n");
        printf("'c', Execute command\n");
        printf("'n', Encode file\n");
        printf("'d', Decode file\n");
        printf("'e', exit mode\n");

        scanf(" %c", &choice);

        if (choice == 'c') {

        } else if (choice == 'n') {
            char input_file_path[256];
            char output_file_path[256];

            // input file
            printf("Select input file path: ");
            fgets(input_file_path, sizeof(input_file_path), stdin);
            size_t len = strlen(input_file_path);
            if (len > 0 && input_file_path[len - 1] == '\n') {
                input_file_path[len - 1] = '\0';
            }

            if (!is_file_exists(input_file_path)) {
                printf("Wrong input file path.\n");
                break;
            }

            // output file
            printf("Select output file path: ");
            fgets(output_file_path, sizeof(output_file_path), stdin);
            size_t out_len = strlen(output_file_path);
            if (out_len > 0 && output_file_path[out_len - 1] == '\n') {
                output_file_path[len - 1] = '\0';
            }

            if (is_file_creation_path_valid(output_file_path)) {
                printf("Huffman encoding: \n");
                huffman_encode(input_file_path, output_file_path);
            } else {
                printf("Wrong output file path.\n");
                break;
            }
        } else if (choice == 'e') {
            printf("Exiting receiver mode...\n");
            break;
        } else {
            printf("Wrong option, try again.\n");
        }
    }
}
void execute_command(const char *command);

// linux commands functions
void ls_command(void);
void mkdir_command(void);
void rmdir_command(void);