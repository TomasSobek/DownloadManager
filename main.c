#include "sockets.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
    short exit = 0;
    while(exit != 1) {
        char mode;
        printf("\nEnter mode (s for sender, r for receiver, e for exit): ");
        scanf(" %c", &mode);

        if (mode == 's') {
            printf("You are entering the 'sender' mode:\n");
            send_file_tcp("localhost", 1111, "/home/sobek3/client1_files/testfile");
        } else if (mode == 'r') {
            printf("You are entering the 'receiver' mode:\n");
            receive_file_tcp(1111, "/home/sobek3/client2_files/testfile_copy");
        } else if (mode == 'e') {
            printf("Exiting application...\n");
            exit = 1;
        } else {
            printf("Invalid mode.\n");
        }
    }

    return 0;
}
