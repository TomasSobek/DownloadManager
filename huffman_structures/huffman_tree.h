#ifndef SEMESTRALNAPRACAUDSP_HUFFMAN_TREE_H
#define SEMESTRALNAPRACAUDSP_HUFFMAN_TREE_H

#include "priority_queue.h"

HUFFMAN_NODE* build_huffman_tree(char data[], unsigned long long freq[], int size);
void destroy_huffman_tree(HUFFMAN_NODE *root);      // need to implement

#endif //SEMESTRALNAPRACAUDSP_HUFFMAN_TREE_H
