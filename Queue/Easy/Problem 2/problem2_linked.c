#include <stdio.h>
#include <stdlib.h>

#define TEST(ptr, cmp, message) {if(ptr == cmp) {perror(message); exit(EXIT_FAILURE);}}

typedef struct GraphNode {
    int data;
    struct GraphNode *next;
} GraphNode;

typedef struct DynamicArray {
    size_t size;
    size_t capacity;

    void **array;
    
    void (* append)(struct DynamicArray *, void *address);
    void (* freeArray)(struct DynamicArray *);
    void (* printList)(struct DynamicArray *);

} DynamicArray;

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
        void **newArr = (void **)realloc(array->array, (array->capacity * sizeof(void *)));
        TEST(newArr, NULL, "MALLOC");

        array->array = newArr;
        return;
    }
}

void append(DynamicArray *array, void *address) {
    growArray(array);

    array->array[array->size++] = address;
}


void freeLinkedList(GraphNode *head) {
    GraphNode *temp = NULL;

    while (head != NULL) {
        temp = head;
        head = (head)->next;

        free(temp);
    }

    head = NULL;
}

void freeArray(DynamicArray *array) {
    for (int i = 0; i < array->size; i++) {
        if (array->array[i] != NULL) {
            freeLinkedList(((GraphNode *)array->array[i]));
        }
    }

    free(array->array);
}

void makeVertex(DynamicArray *array, int data) {
    GraphNode *newNode = (GraphNode *)malloc(sizeof(GraphNode));
    TEST(newNode, NULL, "MALLOC");

    newNode->data = data;
    newNode->next = NULL;

    array->append(array, newNode);
}


void addEdge(DynamicArray *list, int src, int dest) {
    if (src >= list->size || dest >= list->size) {
        fprintf(stderr, "Invalid vertex index\n");
        return;
    }

    GraphNode *head = (GraphNode *)list->array[src];
    GraphNode *newNode = (GraphNode *)malloc(sizeof(GraphNode));
    TEST(newNode, NULL, "MALLOC");

    newNode->data = dest;
    newNode->next = NULL;

    for (GraphNode *temp = head; temp != NULL; temp = temp->next) {
        if (temp->next == NULL) {
            temp->next = newNode;
            return;
        }
    }
}

void printList(DynamicArray *array) {
    for (int i = 0; i < array->size; i++) {
        printf("ADDRESS: %p | VALUE: %d\n", array->array[i], ((GraphNode *)array->array[i])->data);

        for (GraphNode *temp = (GraphNode *)array->array[i]; temp != NULL; temp = temp->next) {
            printf("%d->", temp->data);
        }

        printf("NULL\n");
    }
}

DynamicArray init() {
    return (DynamicArray){
        .size = 0,
        .capacity = 0,
        .array = NULL,
        .append = append,
        .freeArray = freeArray,
        .printList = printList
    };
}

int main(int argc, char const *argv[]) {
    DynamicArray adjacencyList = init();

    makeVertex(&adjacencyList, 0);
    makeVertex(&adjacencyList, 1);
    makeVertex(&adjacencyList, 2);
    makeVertex(&adjacencyList, 3);
    makeVertex(&adjacencyList, 4);

    addEdge(&adjacencyList, 0, 1);
    addEdge(&adjacencyList, 0, 2);

    addEdge(&adjacencyList, 1, 0);
    addEdge(&adjacencyList, 1, 2);
    addEdge(&adjacencyList, 1, 3);

    addEdge(&adjacencyList, 2, 0);
    addEdge(&adjacencyList, 2, 1);
    addEdge(&adjacencyList, 2, 4);

    addEdge(&adjacencyList, 3, 1);
    addEdge(&adjacencyList, 3, 4);

    addEdge(&adjacencyList, 4, 2);
    addEdge(&adjacencyList, 4, 3);

    adjacencyList.printList(&adjacencyList);
    adjacencyList.freeArray(&adjacencyList);
    return 0;
}