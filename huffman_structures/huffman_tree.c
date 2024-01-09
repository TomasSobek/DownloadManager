#include "huffman_tree.h"

#include <stdlib.h>

HUFFMAN_NODE* build_huffman_tree(char data[], unsigned long long freq[], int size) {
    PRIORITY_QUEUE* pq = createPriorityQueue(size);

    for (int i = 0; i < size; ++i) {
        if (freq[i] > 0) {
            insertPriorityQueue(pq, create_node(data[i], freq[i]));
        }
    }
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

void destroy_huffman_tree(HUFFMAN_NODE* root) {
    if (root != NULL) {
        destroy_huffman_tree(root->left);
        destroy_huffman_tree(root->right);
        free(root);
    }
}