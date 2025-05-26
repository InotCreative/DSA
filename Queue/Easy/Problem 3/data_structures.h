#include <stdio.h>
#include <stdlib.h>

#define TEST(ptr, cmp, message) {if(ptr == cmp) {perror("MALLOC"); exit(EXIT_FAILURE);}}

typedef struct QueueNode {
    void *address;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    int length;

    QueueNode *head;
    QueueNode *tail;

    void (* enqueue)(struct Queue *, void *);
    QueueNode *(* dequeue)(struct Queue *);
    void (* freeQueue)(struct Queue *);
} Queue;

typedef struct DynamicArray {
    size_t size;
    size_t capacity;

    void **array;

    void (* append)(struct DynamicArray *, void *address);
    void (* freeArray)(struct DynamicArray *);
} DynamicArray;

typedef struct GraphNode {
    int index;
    int graphData;

    struct GraphNode *next;
} GraphNode;

void enqueue(Queue *queue, void *address);
QueueNode *dequeue(Queue *queue);
void growArray(DynamicArray *array);
void append(DynamicArray *array, void *address);
void freeArray(DynamicArray *array);
void freeLinkedList(GraphNode *head);
void freeQueue(Queue *queue);
void newVertex(DynamicArray *array, int graphData);
void addEdge(DynamicArray *array, int src, int dest);
DynamicArray initArray();
Queue initQueue();