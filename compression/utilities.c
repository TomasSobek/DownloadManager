#include "utilities.h"
#include <stdio.h>

void calculate_frequencies(const char* filename, unsigned long long freq[]) {
    for (int i = 0; i < 256; i++)
        freq[i] = 0;

    FILE *file = fopen(filename, "rb");
    if (file == NULL) return;

    unsigned char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        for (size_t i = 0; i < bytesRead; i++) {
            freq[buffer[i]]++;
        }
    }
    fclose(file);
}
