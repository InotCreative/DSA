#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LENGTH(ARRAY_PTR) ((sizeof(ARRAY_PTR)) / (sizeof(ARRAY_PTR[0])))

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct DynamicArray {
    int size;
    int capacity;
    void **nodeAddresses;

    void (* printArray)(struct DynamicArray *);

} DynamicArray;

#define INITALIZE_SIZE 8

#define GROW_CAPACITY(dynamicArrayPtr) {                            \
    if ((dynamicArrayPtr->size + 1) > dynamicArrayPtr->capacity) {  \
        dynamicArrayPtr->capacity = dynamicArrayPtr->capacity * 2;  \
    }                                                               \
}                                                                   \

void growArray(DynamicArray *array) {
    if (array->capacity == 0) {
        array->capacity = INITALIZE_SIZE;
        array->nodeAddresses = (void **)malloc(array->capacity * sizeof(void *));
    } else if (array->size + 1 > array->capacity) {
        array->capacity *= 2;
        array->nodeAddresses = (void **)realloc(array->nodeAddresses, array->capacity * sizeof(void *));
    }
}

void pushArray(DynamicArray *array, void *address) {
    growArray(array);

    array->nodeAddresses[array->size] = address;
    array->size++;
}

void append(Node **head, DynamicArray *array, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("ERROR | MALLOC\n");
        return;
    }

    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        pushArray(array, newNode);
        return;
    }

    for (Node *temp = *head; temp != NULL; temp = temp->next) {
        if (temp->next == NULL) {
            temp->next = newNode;
            pushArray(array, newNode);
            return;
        }
    }
}

void betterAppend(Node **head, DynamicArray *array, int *intArray, int length) {
    for (int i = 0; i < length; i++) {
        append(head, array, intArray[i]);
    }
}

void freeList(Node **head) {
    Node *temp = NULL;

    while (*head != NULL) {
        temp = *head;
        (*head) = (*head)->next;
        
        free(temp);
    }

    *head = NULL;
}

void printList(Node *head) {
    for (Node *temp = head; temp != NULL; temp = temp->next) {
        printf("%d->", temp->data);
    }

    printf("NULL\n");
}

void printArray(DynamicArray *array) {
    for (int i = 0; i < array->size; i++) {
        printf("ADDRESS: %p | VALUE: %d | INDEX: %d\n", array->nodeAddresses[i], ((Node *)array->nodeAddresses[i])->data, i);
    }

    printf("--------------------------------------------------\n");
}

void initDynamicArray(DynamicArray *array) {
    array->capacity = 0;
    array->size = 0;
    array->nodeAddresses = NULL;
    array->printArray = printArray;
}

void swap(void **a, void **b) {
    void *temp = *a;
    *a = *b;
    *b = temp;
}

int partition(DynamicArray *array, int low, int high) {
    int pivot = ((Node *)array->nodeAddresses[high])->data; // Choosing the last element as pivot
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (((Node *)array->nodeAddresses[j])->data < pivot) {
            i++;
            swap(&array->nodeAddresses[i], &array->nodeAddresses[j]);
        }
    }

    swap(&array->nodeAddresses[i + 1], &array->nodeAddresses[high]);
    return i + 1;
}

void quickSort(DynamicArray *array, Node **head, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);  // Partition index

        quickSort(array,  head, low, pi - 1);  // Left side
        quickSort(array, head, pi + 1, high); // Right side
    }

    *head = (Node *)array->nodeAddresses[0];
    Node *temp = (*head);

    for (int i = 1; i < array->size; i++) {
        temp->next = (Node *)array->nodeAddresses[i];
        temp = temp->next;
    }

    temp->next = NULL;
}

int main(int argc, char const *argv[]) {
    DynamicArray array;

    initDynamicArray(&array);

    Node *headOne = NULL;
    Node *headTwo = NULL;
    Node *headThree = NULL;
    Node *headFour = NULL;

    int dataOne[] = {1, 3, 5, 7};
    int dataTwo[] = {2, 4, 6, 8};
    int dataThree[] = {0, 9, 10, 11};

    betterAppend(&headOne, &array, dataOne, ARRAY_LENGTH(dataOne));
    printList(headOne);

    betterAppend(&headTwo, &array, dataTwo, ARRAY_LENGTH(dataTwo));
    printList(headTwo);

    betterAppend(&headThree, &array, dataThree, ARRAY_LENGTH(dataThree));
    printList(headThree);

    array.printArray(&array);

    quickSort(&array, &headFour, 0, array.size - 1);
    array.printArray(&array);

    printList(headFour);

    freeList(&headFour);
    return 0;
}
