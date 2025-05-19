#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Array {
    int size;
    int capacity;

    void **nodeAddresses;
    void (*betterAppend)(Node **, int *, struct Array *, int);
    void (*printList)(Node *);
    void (*printArray)(struct Array *);
    void (*quickSort)(struct Array *, Node **, int, int);
} Array;

void growArray(Array *array) {
    if (array->capacity == 0) {
        array->capacity = 8;
        array->nodeAddresses = (void **)malloc(array->capacity * sizeof(void *));
    } else {
        array->capacity *= 2;
        array->nodeAddresses = (void **)realloc(array->nodeAddresses, array->capacity * sizeof(void *));
    }

    if (array->nodeAddresses == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

void push(Array *array, void *address) {
    if (array->size >= array->capacity) {
        growArray(array);
    }

    array->nodeAddresses[array->size] = address;
    array->size++;
}

void append(Node **head, Array *array, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("ERROR MALLOC");
        return;
    }

    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        push(array, (void *)newNode);
        return;
    }

    for (Node *temp = *head; temp != NULL; temp = temp->next) {
        if (temp->next == NULL) {
            temp->next = newNode;
            push(array, newNode);
            return;
        }
    }
}

void betterAppend(Node **head, int *intArray, Array *array, int length) {
    for (int i = 0; i < length; i++) {
        append(head, array, intArray[i]);
    }
}

void printList(Node *head) {
    for (Node *temp = head; temp != NULL; temp = temp->next) {
        printf("%d->", temp->data);
    }

    printf("NULL\n");
}

void printArray(Array *array) {
    for (int i = 0; i < array->size; i++) {
        printf("ADDRESS: %p | VALUE: %d | INDEX: %d\n", array->nodeAddresses[i], ((Node *)array->nodeAddresses[i])->data, i);
    }

    printf("\n");
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

void swap(void **a, void **b) {
    void *temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Array *array, int low, int high) {
    int pivot = ((Node *)array->nodeAddresses[high])->data;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (((Node *)array->nodeAddresses[j])->data <= pivot) {
            i++;
            swap(&array->nodeAddresses[i], &array->nodeAddresses[j]);
        }
    }

    swap(&array->nodeAddresses[i + 1], &array->nodeAddresses[high]);
    return i + 1;
}

void quickSort(Array *array, Node **head, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);

        quickSort(array, head, low, pi - 1);
        quickSort(array, head, pi + 1, high);
    }

    *head = (Node *)array->nodeAddresses[0];
    (*head)->next = NULL;

    Node *temp = *head;

    for (int i = 1; i < high + 1; i++) {
        temp->next = (Node *)array->nodeAddresses[i];
        temp = temp->next;
    }

    temp->next = NULL;
}

void init(Array *array) {
    array->capacity = 0;
    array->size = 0;
    array->nodeAddresses = NULL;
    array->betterAppend = betterAppend;
    array->printArray = printArray;
    array->printList = printList;
    array->quickSort = quickSort;
}

int main(int argc, char const *argv[]) {
    int data[] = {5, 4, 1, 3, 2};
    int dataLength = (sizeof(data)) / (sizeof(data[0]));

    int arr[] = {45, 23, 89, 12, 78, 34, 67, 1, 99, 56, 32, 10, 5, 73, 88, 21, 4, 39, 91, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    Array array;
    Node *head = NULL;

    init(&array);

    array.betterAppend(&head, arr, &array, n);
    array.printList(head);
    array.printArray(&array);
    
    array.quickSort(&array, &head, 0, n - 1);
    array.printArray(&array);
    array.printList(head);
    
    freeList(&head);
    return 0;
}
