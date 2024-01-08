#include "sockets.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
    char mode;
    printf("Enter mode (s for sender, r for receiver): ");
    scanf(" %c", &mode);

    if (mode == 's') {
        send_file_tcp("localhost", 1111, "/home/sobek3/client1_files/text1.txt");
    } else if (mode == 'r') {
        receive_file_tcp(1111, "/home/sobek3/client2_files/text.txt");
    } else {
        printf("Invalid mode.\n");
    }

    return 0;
}
