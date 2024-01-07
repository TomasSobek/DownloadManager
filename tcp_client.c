#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main() {
    // creating of socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0); // dobuducna definovat protokol?

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8002);
    server_address.sin_addr.s_addr = INADDR_ANY;       // same as 0.0.0.0

    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if (connection_status == -1) {
        printf("There was an error making a connection to the remote socket. \n");
    }

    // receive data from server
    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);     // zistit co su to flags

    // print out the server's response
    printf("The server sent data: %s\n", server_response);

    // close socket
    close(network_socket);
    return 0;
}