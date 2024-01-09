#include "huffman_tree.h"

HUFFMAN_NODE* buildHuffmanTree(char data[], int freq[], int size) {
    PRIORITY_QUEUE* pq = createPriorityQueue(size);

    for (int i = 0; i < size; ++i)
        insertPriorityQueue(pq, create_node(data[i], freq[i]));

    while (pq->size != 1) {
        HUFFMAN_NODE* left = removeMin(pq);
        HUFFMAN_NODE* right = removeMin(pq);

        HUFFMAN_NODE* top = create_node('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        insertPriorityQueue(pq, top);
    }

    HUFFMAN_NODE* root = removeMin(pq);
    destroyPriorityQueue(pq);
    return root;
}