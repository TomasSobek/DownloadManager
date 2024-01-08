#ifndef SEMESTRALNAPRACAUDSP_HUFFMAN_NODE_H
#define SEMESTRALNAPRACAUDSP_HUFFMAN_NODE_H

typedef struct Huffman_Node {
    char character;
    unsigned frequency;
    struct Huffman_Node *left, *right;
} HUFFMAN_NODE;

HUFFMAN_NODE* create_node(char character, unsigned frequency);
void destroy_node(HUFFMAN_NODE *node);

#endif //SEMESTRALNAPRACAUDSP_HUFFMAN_NODE_H
