#include "data_structures.h"

void enqueue(Queue *queue, void *address) {
    QueueNode *newQueueNode = (QueueNode *)malloc(sizeof(QueueNode));
    TEST(newQueueNode, NULL, "MALLOC");

    newQueueNode->address = address;
    newQueueNode->next = NULL;

    if (queue->head == NULL) {
        queue->head = newQueueNode;
        queue->tail = newQueueNode;
        queue->length++;

        return;
    }

    queue->length++;
    queue->tail->next = newQueueNode;
    queue->tail = newQueueNode;
}

QueueNode *dequeue(Queue *queue) {
    TEST(queue->head, NULL, "HEAD EMPTY");

    QueueNode *returnAddress = queue->head;
    queue->head = queue->head->next;
    queue->length--;

    return returnAddress;
}

void growArray(DynamicArray *array) {
    if (array->size == 0) {
        array->capacity = 8;
        void **arr = (void **)malloc(array->capacity * sizeof(void *));
        TEST(arr, NULL, "MALLOC");
        
        array->array = arr;
        return;
    }

    if (array->size >= array->capacity) {
        array->capacity *= 2;
        void **arr = (void **)realloc(array->array, array->capacity * sizeof(void *));
        TEST(arr, NULL, "REALLOC");
        
        array->array = arr;
        return;
    }
}

void append(DynamicArray *array, void *address) {
    growArray(array);
    array->array[array->size++] = address;
}

void freeQueue(Queue *queue) {
    QueueNode *temp = NULL;

    while (queue->head != NULL) {
        temp = queue->head;
        queue->head = queue->head->next;

        free(temp);
    }

    queue->head = NULL;
    queue->tail = NULL;
}

Queue initQueue() {
    return (Queue){
        .enqueue   = enqueue,
        .dequeue   = dequeue,
        .head      = NULL,
        .length    = 0,
        .tail      = NULL,
        .freeQueue = freeQueue
    };
}

void freeArray(DynamicArray *array) {
    for (int i = 0; i < array->size; i++) {
        if (array->array[i] != NULL) freeLinkedList((GraphNode *)array->array[i]);
    }

    free(array->array);
}

void freeLinkedList(GraphNode *head) {
    GraphNode *temp = NULL;

    while (head != NULL) {
        temp = head;
        head = head->next;

        free(temp);
    }

    head = NULL;
}

DynamicArray initArray() {
    return (DynamicArray){
        .append = append,
        .array = NULL,
        .capacity = 0,
        .freeArray = freeArray,
        .size = 0
    };
}

void newVertex(DynamicArray *array, int graphData) {
    GraphNode *newGraphVertex = (GraphNode *)malloc(sizeof(GraphNode));
    TEST(newGraphVertex, NULL, "MALLOC");

    newGraphVertex->graphData = graphData;
    newGraphVertex->next = NULL;

    if (array->size == 0) {
        newGraphVertex->index = array->size;
        array->append(array, newGraphVertex);
        return;
    }
    
    newGraphVertex->index = array->size;
    array->append(array, newGraphVertex);
}

void addEdge(DynamicArray *array, int src, int dest) {
    
    GraphNode *head = (GraphNode *)array->array[src];
    GraphNode *newNode = (GraphNode *)malloc(sizeof(GraphNode));
    TEST(newNode, NULL, "MALLOC");

    newNode->graphData = dest;
    newNode->index = ((GraphNode *)array->array[dest])->index;

    for (GraphNode *temp = head; temp != NULL; temp = temp->next) {
        if (temp->graphData == dest) {
            free(newNode);
            return;
        }

        if (temp->next == NULL) {
            temp->next = newNode;
            return;
        }
    }
}