#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {

    char* address;
    address = argv[1];

    // creating of socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0); // dobuducna definovat protokol?

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(80);
    // server_address.sin_addr.s_addr = INADDR_ANY;       // same as 0.0.0.0
    inet_aton(address, &server_address.sin_addr.s_addr);

    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if (connection_status == -1) {
        printf("There was an error making a connection to the remote socket. \n");
    }

    char request[] = "GET / HTTP/1.1\r\n\r\n";
    char response[4096];

    send(network_socket, request, sizeof(request), 0);

    // receive data from server
    recv(network_socket, &response, sizeof(response), 0);     // zistit co su to flags

    // print out the server's response
    printf("Response from server: %s\n", response);

    // close socket
    close(network_socket);
    return 0;
}