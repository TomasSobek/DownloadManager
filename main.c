#include "sockets.h"
#include "compression/compression.h"

#include <stdio.h>
#include <string.h>

#include "console.h"


int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Usage: %s <mode>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "sender") == 0) {
        sender_mode();
    } else if (strcmp(argv[1], "receiver") == 0) {
        receiver_mode();
    } else if (strcmp(argv[1], "huffman") == 0) {
        huffman_mode();
    } else {
        printf("Invalid mode. Available modes are 'sender', 'receiver', 'huffman'.\n");
        return 1;
    }

    //console_main();
    printf("Exiting application...\n");
    return 0;
}
