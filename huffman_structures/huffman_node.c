#include "huffman_node.h"

#include <stdlib.h>

HUFFMAN_NODE* create_node(char character, unsigned frequency) {
    HUFFMAN_NODE *node = (HUFFMAN_NODE *) malloc(sizeof(HUFFMAN_NODE));
    node->character = character;
    node->frequency = frequency;

    node->left = NULL;
    node->right = NULL;

    return node;
}

void destroy_node(HUFFMAN_NODE *node) {
    node->character = ' ';
    node->frequency = 0;
    node->left = NULL;
    node->right = NULL;

    free(node);
}