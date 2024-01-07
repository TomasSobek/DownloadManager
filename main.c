#include "sockets.h"

#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int server_sock, client_sock;
    server_sock = create_server_socket(8002);

    client_sock = create_client_socket("", 8002);

    close(server_sock);
    close(client_sock);
    return 0;
}
