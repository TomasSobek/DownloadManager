#include "sockets.h"

#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>

#define BUFFER_SIZE 1024

static int create_TCP_IPV4_socket(void) {
    int socket_fd;
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) <= 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    return socket_fd;
}

static void print_progress(size_t total_sent, size_t total_size) {
    const int bar_width = 50; // Width of the progress bar
    float progress = (float)total_sent / total_size;
    int pos = bar_width * progress;

    printf("\rProgress: [");
    for (int i = 0; i < bar_width; ++i) {
        if (i < pos) printf("=");
        else if (i == pos) printf(">");
        else printf(" ");
    }
    printf("] %d %%", (int)(progress * 100.0));
    fflush(stdout); // Flush stdout to update the progress bar in place
}


static char* replace_filename(const char *file_path, const char *new_filename) {
    // Find the last '/' or '\' in the path
    char *last_slash = strrchr(file_path, '/');
    if (last_slash == NULL) {
        last_slash = strrchr(file_path, '\\');
    }

    char *modified_path = NULL;

    if (last_slash != NULL) {
        // Calculate the position of the last slash in the string
        size_t last_slash_position = last_slash - file_path;

        // Allocate memory for the modified path
        modified_path = (char*)malloc(256);

        if (modified_path != NULL) {
            // Copy the original path into the modified path
            strcpy(modified_path, file_path);

            // Copy the new filename into the path after the last slash
            strcpy(modified_path + last_slash_position + 1, new_filename);
        }
    }
    else {
        // If no slash or backslash is found, return a copy of the new filename
        modified_path = strdup(new_filename);
    }

    return modified_path;
}

void send_file_tcp(const char *ip, int port, const char *file_path) {
    int socket_fd;
    struct sockaddr_in server_addr;
    FILE *file;
    char buffer[BUFFER_SIZE];

    // Creating socket
    socket_fd = create_TCP_IPV4_socket();

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (strlen(ip) == 0) {
        server_addr.sin_addr.s_addr = INADDR_ANY;       // localhost
    } else {
        inet_pton(AF_INET, ip, &server_addr.sin_addr);
    }

    // Connect to the server
    if (connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(socket_fd);
        return;
    }

    // Open the file
    if ((file = fopen(file_path, "rb")) == NULL) {
        perror("File open failed");
        close(socket_fd);
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Send the file size first
    char file_size_str[20];
    sprintf(file_size_str, "%ld", file_size);
    size_t str_length = strlen(file_size_str);
    send(socket_fd, file_size_str, str_length, 0);

    // Read and send the file contents with progress update
    size_t total_sent = 0;
    memset(buffer, 0, sizeof(buffer));
    while (!feof(file)) {
        size_t bytes_read = fread(buffer, 1, sizeof(buffer), file);
        if (bytes_read > 0) {
            send(socket_fd, buffer, bytes_read, 0);
            total_sent += bytes_read;
            print_progress(total_sent, file_size);
        }
    }

    printf("\nFile sent successfully.\n");

    // Cleanup
    fclose(file);
    close(socket_fd);
}

void receive_file_tcp(int port, const char *file_path) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    FILE *file;
    char buffer[BUFFER_SIZE];

    // Creating socket file descriptor
    server_fd = create_TCP_IPV4_socket();

    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        return;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Bind the socket to the address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return;
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        return;
    }
    printf("Im listening on port: %d", port);

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        close(new_socket);
        close(server_fd);
        return;
    }

    // Open file for writing
    if ((file = fopen(file_path, "wb")) == NULL) {
        perror("File open failed");
        close(new_socket);
        close(server_fd);
        return;
    }

    // Receive file size first
    /*
    char file_size_str[20];
    read(new_socket, file_size_str, sizeof(file_size_str));
    long file_size = strtol(file_size_str, NULL, 10);
     */
    char file_size_str[20] = {0}; // Initialize all elements to zero
    ssize_t bytes_read = read(new_socket, file_size_str, sizeof(file_size_str) - 1); // Leave space for the null terminator
    if (bytes_read < 0) {
        printf("No file size received.\n");
        return;
    }
    file_size_str[bytes_read] = '\0'; // Explicitly null-terminate the string
    long file_size = strtol(file_size_str, NULL, 10);

    long total_received = 0;
    while (total_received < file_size) {
        ssize_t bytes_received = read(new_socket, buffer, BUFFER_SIZE);
        if (bytes_received <= 0) {
            break; // Handle end of file or error
        }
        fwrite(buffer, 1, bytes_received, file);
        total_received += bytes_received;

        // Print progress
        print_progress(total_received, file_size);
    }

    printf("\nFile received successfully.\n");

    // Cleanup
    fclose(file);
    close(new_socket);
    close(server_fd);
}
#undef BUFFER_SIZE