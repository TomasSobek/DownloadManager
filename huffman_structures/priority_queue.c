#include "priority_queue.h"
#include <stdlib.h>

PRIORITY_QUEUE* createPriorityQueue(int capacity) {
    PRIORITY_QUEUE* pq = (PRIORITY_QUEUE*)malloc(sizeof(PRIORITY_QUEUE));
    pq->capacity = capacity;
    pq->size = 0;
    pq->array = (HUFFMAN_NODE**)malloc(capacity * sizeof(HUFFMAN_NODE*));
    return pq;
}

void destroyPriorityQueue(PRIORITY_QUEUE* pq) {
    free(pq->array);
    free(pq);
}

void minHeapify(PRIORITY_QUEUE* pq, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < pq->size && pq->array[left]->frequency < pq->array[smallest]->frequency)
        smallest = left;
    if (right < pq->size && pq->array[right]->frequency < pq->array[smallest]->frequency)
        smallest = right;
    if (smallest != idx) {
        HUFFMAN_NODE* temp = pq->array[smallest];
        pq->array[smallest] = pq->array[idx];
        pq->array[idx] = temp;
        minHeapify(pq, smallest);
    }
}

HUFFMAN_NODE* removeMin(PRIORITY_QUEUE* pq) {
    if (pq->size == 0) return NULL;

    HUFFMAN_NODE* root = pq->array[0];
    pq->array[0] = pq->array[pq->size - 1];
    pq->size--;
    minHeapify(pq, 0);
    return root;
}

void insertPriorityQueue(PRIORITY_QUEUE* pq, HUFFMAN_NODE* node) {
    pq->size++;
    int i = pq->size - 1;
    while (i && node->frequency < pq->array[(i - 1) / 2]->frequency) {
        pq->array[i] = pq->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    pq->array[i] = node;
}

int isPriorityQueueEmpty(PRIORITY_QUEUE* pq) {
    return pq->size == 0;
}