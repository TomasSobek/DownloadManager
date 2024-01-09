#ifndef SEMESTRALNAPRACAUDSP_PRIORITY_QUEUE_H
#define SEMESTRALNAPRACAUDSP_PRIORITY_QUEUE_H

#include "huffman_node.h"

typedef struct PriorityQueue {
    int capacity;
    int size;
    HUFFMAN_NODE **array;
} PRIORITY_QUEUE;

PRIORITY_QUEUE* createPriorityQueue(int capacity);
void destroyPriorityQueue(PRIORITY_QUEUE *pq);
void insertPriorityQueue(PRIORITY_QUEUE *pq, HUFFMAN_NODE *node);
HUFFMAN_NODE* removeMin(PRIORITY_QUEUE *pq);
int isPriorityQueueEmpty(PRIORITY_QUEUE *pq);

#endif //SEMESTRALNAPRACAUDSP_PRIORITY_QUEUE_H
