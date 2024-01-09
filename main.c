#include "sockets.h"
#include "compression/compression.h"

#include <stdio.h>

#include "console.h"

int main(int argc, char* argv[]) {
    // short exit = 0;

    /*
    printf("You are entering Huffman compression mode.\n");
    huffman_encode("/home/sobek3/client1_files/random_text.txt",
                   "/home/sobek3/client1_files/compressed_text.z");
    huffman_decode("/home/sobek3/client1_files/compressed_text.z",
                   "/home/sobek3/client1_files/decompressed_text.txt");
    */

    console_main();
    printf("Exiting application...\n");
    /*
    while(exit != 1) {
        char mode;
        printf("\nEnter mode (s for sender, r for receiver, c for compression, e for exit): ");
        scanf(" %c", &mode);

        if (mode == 's') {
            printf("You are entering the 'sender' mode:\n");
            send_file_tcp("localhost", 1111, "/home/sobek3/client1_files/testfile");
        } else if (mode == 'r') {
            printf("You are entering the 'receiver' mode:\n");
            receive_file_tcp(1111, "/home/sobek3/client2_files/testfile_copy");
        } else if (mode == 'c') {
            printf("You are entering Huffman compression mode.\n");
            huffman_encode("/home/sobek3/client1_files/random_text.txt",
                           "/home/sobek3/client1_files/random_text_compressed.z");
        } else if (mode == 'e') {
            printf("Exiting application...\n");
            exit = 1;
        } else {
            printf("Invalid mode.\n");
        }
    }
    */
    return 0;
}
