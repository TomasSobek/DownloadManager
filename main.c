#include "sockets.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc == 0) {
        printf("Program doesn't received any parameters.\n");
        return 1;
    }
    if (strcmp(argv[1], "0") == 0) {
        create_server_socket(8002);
    } else if (strcmp(argv[1], "1") == 0) {
        create_client_socket("", 8002);
    } else {
        printf("Wrong selected arguments.\n");
        return 1;
    }

    return 0;
}
