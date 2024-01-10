#include "compression.h"
#include "utilities.h"
#include "../huffman_structures/huffman_tree.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// helper function to generate Huffman codes and store them in an array.
static void generate_huffman_codes(HUFFMAN_NODE *root, char** codes, char *code, int top) {
    if (root == NULL) {
        return;
    }
    if (root->left) {
        code[top] = '0';
        generate_huffman_codes(root->left, codes, code, top + 1);
    }
    if (root->right) {
        code[top] = '1';
        generate_huffman_codes(root->right, codes, code, top + 1);
    }
    if (!root->left && !root->right) {
        // codes[root->character] = strdup(code);
        code[top] = '\0'; // Null-terminate the code string
        if (root->character == '\n') {
            printf("Character: endl, Code: %s\n", code);
        } else {
            printf("Character: %c, Code: %s\n", root->character, code); // Debugging print
        }
        codes[root->character] = strdup(code);
        if (codes[root->character] == NULL) {
            fprintf(stderr, "Memory allocation failed for code of character %c\n", root->character);
            exit(EXIT_FAILURE);
        }
    }
}

// serialize and write the Huffman tree to the output file.
static void serialize_huffman_tree(HUFFMAN_NODE *root, FILE *output_file) {
    /*
    if (root == NULL) {
        return;
    }

    // Write a leaf marker followed by the character if it's a leaf node
    if (root->left == NULL && root->right == NULL) {
        fputc('1', output_file); // '1' indicates a leaf node
        fputc(root->character, output_file);
    } else {
        // Otherwise, write a non-leaf marker and recurse
        fputc('0', output_file); // '0' indicates a non-leaf node
        serialize_huffman_tree(root->left, output_file);
        serialize_huffman_tree(root->right, output_file);
    }
     */
    static char debug_string[1024] = ""; // Buffer to keep track of the serialization stream
    static int depth = 0; // Depth in the tree

    if (root == NULL) {
        return;
    }

    // Ensure we don't overflow the buffer
    if (depth >= 1023) {
        printf("serialize_huffman_tree: Debug string buffer overflow.\n");
        return;
    }

    // Write a leaf marker followed by the character if it's a leaf node
    if (root->left == NULL && root->right == NULL) {
        debug_string[depth++] = '1'; // Add '1' to the debug string
        debug_string[depth] = '\0';  // Null-terminate the string
        printf("serialize_huffman_tree: Leaf node '%c', Stream: %s\n", root->character, debug_string);

        fputc('1', output_file);
        fputc(root->character, output_file);
    } else {
        // Otherwise, write a non-leaf marker and recurse
        debug_string[depth++] = '0'; // Add '0' to the debug string
        debug_string[depth] = '\0';  // Null-terminate the string
        printf("serialize_huffman_tree: Internal node, Stream: %s\n", debug_string);

        fputc('0', output_file);
        serialize_huffman_tree(root->left, output_file);
        serialize_huffman_tree(root->right, output_file);
    }

    depth--;
    //printf("%s\n", debug_string);
}

static HUFFMAN_NODE* deserialize_huffman_tree(FILE *input_file) {
    int marker = fgetc(input_file);
    if (marker == EOF) {
        return NULL;
    }

    if (marker == '1') {
        // Leaf node
        int charVal = fgetc(input_file);
        if (charVal == EOF) {
            return NULL;
        }
        return create_node((char)charVal, 0);
    } else {
        // Internal node
        HUFFMAN_NODE* left = deserialize_huffman_tree(input_file);
        HUFFMAN_NODE* right = deserialize_huffman_tree(input_file);
        HUFFMAN_NODE* node = create_node('\0', 0);
        node->left = left;
        node->right = right;
        return node;
    }
}

static void decode_data(FILE *input_file, FILE *output_file, HUFFMAN_NODE *root) {
    HUFFMAN_NODE* current = root;
    int bit;
    unsigned char byte;

    while (fread(&byte, 1, 1, input_file)) {
        for (int i = 7; i >= 0; i--) {
            bit = (byte >> i) & 1; // Extract the current bit (starting from the MSB)
            if (bit == 0) {
                current = current->left; // Go left for 0
            } else {
                current = current->right; // Go right for 1
            }

            // Check if we've reached a leaf node
            if (current->left == NULL && current->right == NULL) {
                fputc(current->character, output_file); // Write the character to output
                current = root; // Reset to start of the tree for next character
            }
        }
    }
}

void huffman_encode(const char *input_filename, const char *output_filename) {
    unsigned long long freq[256] = {0};
    calculate_frequencies(input_filename, freq);

    char data[256];
    for (int i = 0; i < 256; i++) {
        data[i] = (char)i;
    }

    HUFFMAN_NODE *root = build_huffman_tree(data, freq, 256);
    printf("I have created huffman tree.\n");

    // Array to store Huffman codes
    char* codes[256] = {0};
    char code[256];
    int top = 0;
    generate_huffman_codes(root, codes, code, top);
    printf("I have generated huffman codes.\n");

    FILE* input_file = fopen(input_filename, "rb");
    if (input_file == NULL) {
        perror("Error opening input file");
        return;
    }

    FILE* output_file = fopen(output_filename, "wb");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return;
    }

    printf("I have opened both files.\n");

    // Serialize and write the Huffman tree to the output file
    serialize_huffman_tree(root, output_file);
    printf("I have serialized huffman tree.\n");

    // Encoding process starts here
    unsigned char buffer;
    unsigned char out_byte = 0;
    int bit_count = 0;

    while (fread(&buffer, 1, 1, input_file)) {
        char* codee = codes[buffer];  // Retrieve the Huffman code for the byte.

        for (int i = 0; codee[i] != '\0'; i++) {
            out_byte <<= 1;
            if (codee[i] == '1') {
                out_byte |= 1;
            }
            bit_count++;

            // When we have 8 bits, write them to the file.
            if (bit_count == 8) {
                fwrite(&out_byte, 1, 1, output_file);
                bit_count = 0;
                out_byte = 0;
            }
        }
    }

    // Write any remaining bits (with padding if necessary).
    if (bit_count > 0) {
        out_byte <<= (8 - bit_count); // Pad the remaining bits with zeros.
        fwrite(&out_byte, 1, 1, output_file);
    }

    fclose(input_file);
    fclose(output_file);

    // Free allocated resources
    for (int i = 0; i < 256; i++) {
        free(codes[i]);
    }
    destroy_huffman_tree(root);
}

void huffman_decode(const char *input_filename, const char *output_filename) {
    FILE* input_file = fopen(input_filename, "rb");
    if (input_file == NULL) {
        perror("Error opening input file");
        return;
    }

    FILE* output_file = fopen(output_filename, "wb");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return;
    }

    // Reconstruct the Huffman tree from the input file.
    HUFFMAN_NODE* root = deserialize_huffman_tree(input_file);
    if (root == NULL) {
        perror("Error reconstructing Huffman tree");
        fclose(input_file);
        fclose(output_file);
        return;
    }

    // Decode the data using the Huffman tree and write to the output file.
    decode_data(input_file, output_file, root);

    fclose(input_file);
    fclose(output_file);
    destroy_huffman_tree(root);
}