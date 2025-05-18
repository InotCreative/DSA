#include <stdio.h>
#include <stdlib.h>

typedef struct DynamicArray {
    size_t size;
    size_t capacity;
    void **nodeAddresses;
} DynamicArray;

typedef struct Node {
    int data;
    struct Node *next;
} Node;

#define INITIAL_CAPACITY 8

void growArray(DynamicArray *array) {
    if (array->capacity == 0) {
        array->capacity = INITIAL_CAPACITY;
        array->nodeAddresses = (void **)malloc(array->capacity * sizeof(void *));
    } else {
        array->capacity *= 2;
        void **temp = (void **)realloc(array->nodeAddresses, array->capacity * sizeof(void *));
        if (temp == NULL) {
            fprintf(stderr, "ERROR | REALLOC FAILED\n");
            exit(EXIT_FAILURE);
        }
        array->nodeAddresses = temp;
    }

    if (array->nodeAddresses == NULL) {
        fprintf(stderr, "ERROR | MALLOC FAILED\n");
        exit(EXIT_FAILURE);
    }
}

void push(DynamicArray *array, void *nodeAddress) {
    if (array->size >= array->capacity) {
        growArray(array);
    }

    array->nodeAddresses[array->size] = nodeAddress;
    array->size++;
}

void init(DynamicArray *array) {
    array->capacity = 0;
    array->size = 0;
    array->nodeAddresses = NULL;
}

void append(Node **head, DynamicArray *array, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "ERROR | MALLOC FAILED\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    push(array, (void *)newNode);
}

void betterAppend(Node **head, DynamicArray *array, int *intArray, int length) {
    for (int i = 0; i < length; i++) {
        append(head, array, intArray[i]);
    }
}

void printList(Node *head) {
    for (Node *temp = head; temp != NULL; temp = temp->next) {
        printf("%d->", temp->data);
    }
    printf("NULL\n\n");
}

void printDynamicArray(DynamicArray *array) {
    for (int i = 0; i < array->size; i++) {
        Node *node = (Node *)array->nodeAddresses[i];
        printf("ADDRESS: %p | VALUE: %d | INDEX: %d\n", (void *)node, node->data, i);
    }
}

void freeNode(Node **head) {
    Node *temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *head = NULL;
}

void solution(Node **head, DynamicArray *array, int k) {
    if (array->size == 0 || k <= 0) return;

    *head = (Node *)array->nodeAddresses[0];
    Node *temp = *head;
    int count = 1;

    for (int i = 1; i < array->size; i++) {
        if ((count % k) != 0) {
            temp->next = (Node *)array->nodeAddresses[i];
            temp = temp->next;
        }
        count++;
    }

    if (temp != NULL) {
        temp->next = NULL;
    }
}


void freeArray(DynamicArray *array) {
    free(array->nodeAddresses);
    array->nodeAddresses = NULL;
    array->size = 0;
    array->capacity = 0;
}

int main(void) {
    Node *head = NULL;
    DynamicArray array;

    int dataTwo[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int length = sizeof(dataTwo) / sizeof(dataTwo[0]);

    init(&array);
    betterAppend(&head, &array, dataTwo, length);
    printList(head);
    printDynamicArray(&array);

    solution(&head, &array, 3);
    printList(head);

    freeNode(&head);
    freeArray(&array);

    return 0;
}
