#include <stdio.h>
#include <stdlib.h>

#define PTR_MEM_TEST(ptr, cmp, message) {if (ptr == cmp) {perror(message); exit(EXIT_FAILURE);}}

typedef struct StackNode {
    int value;
    int index;
} StackNode;

typedef struct DynamicIntArray {
    int size;
    int capacity;

    StackNode **structNodeArray;

    void (* reverseArray)(struct DynamicIntArray *);
    void (* push)(struct DynamicIntArray *, StackNode *);
    StackNode* (* pop)(struct DynamicIntArray *);
    void (* printArray)(struct DynamicIntArray *);
    StackNode* (* peek)(struct DynamicIntArray *);
    void (* freeDynamicArray)(struct DynamicIntArray *);
} DynamicIntArray;

void swap(StackNode **x, StackNode **y) {
    StackNode *temp = *x;
    *x = *y;
    *y = temp;
}

void reverseArray(DynamicIntArray *dynamicArray) {
    int middle = dynamicArray->size / 2;
    for (int start = 0, end = dynamicArray->size - 1; start < middle; start++, end--) {
        swap(&dynamicArray->structNodeArray[start], &dynamicArray->structNodeArray[end]);
    }
}

void growArray(DynamicIntArray *dynamicArray) {
    if (dynamicArray->capacity == 0) {
        dynamicArray->capacity = 8;
        StackNode **mallocArray = (StackNode **)malloc(dynamicArray->capacity * sizeof(StackNode *));
        PTR_MEM_TEST(mallocArray, NULL, "MALLOC\n");

        dynamicArray->structNodeArray = mallocArray;
        return;
    }

    if (dynamicArray->size >= dynamicArray->capacity) {
        dynamicArray->capacity *= 2;
        StackNode **reallocArray = (StackNode **)realloc(dynamicArray->structNodeArray, dynamicArray->capacity * sizeof(StackNode *));
        PTR_MEM_TEST(reallocArray, NULL, "REALLOC\n");

        dynamicArray->structNodeArray = reallocArray;
    }
}

void push(DynamicIntArray *dynamicArray, StackNode *node) {
    growArray(dynamicArray);
    dynamicArray->structNodeArray[dynamicArray->size++] = node;
    reverseArray(dynamicArray);
}

void printArray(DynamicIntArray *dynamicArray) {
    printf("[");
    for (int i = 0; i < dynamicArray->size; i++)
        printf("(%d,%d), ", dynamicArray->structNodeArray[i]->value, dynamicArray->structNodeArray[i]->index);
    printf("]\n");
}

StackNode* pop(DynamicIntArray *dynamicArray) {
    if (dynamicArray->size == 0) return NULL;
    StackNode *returnValue = dynamicArray->structNodeArray[0];
    for (int i = 0; i < dynamicArray->size - 1; i++) dynamicArray->structNodeArray[i] = dynamicArray->structNodeArray[i + 1];
    dynamicArray->size--;
    
    return returnValue;
}

StackNode* peek(DynamicIntArray *dynamicArray) {
    if (dynamicArray->size == 0) return NULL;
    return dynamicArray->structNodeArray[0];
}

void freeDynamicArray(DynamicIntArray *dynamicArray) {
    for (int i = 0; i < dynamicArray->size; i++) free(dynamicArray->structNodeArray[i]);
    free(dynamicArray->structNodeArray);
}

DynamicIntArray initDynamicArray() {
    return (DynamicIntArray) {
        .size             = 0,
        .capacity         = 0,
        .structNodeArray  = NULL,
        .push             = push,
        .pop              = pop,
        .peek             = peek,
        .freeDynamicArray = freeDynamicArray,
        .printArray       = printArray,
        .reverseArray     = reverseArray
    };
}

void dailyTemperature(int *array, int length) {
    DynamicIntArray stack = initDynamicArray();

    int *resultArray = (int *)calloc(length, sizeof(int));

    for (int i = 0; i < length; i++) {
        while (stack.size != 0 && stack.peek(&stack)->value < array[i]) {
            StackNode *nodeToRemove = stack.pop(&stack);
            resultArray[nodeToRemove->index] = (i - nodeToRemove->index);

            free(nodeToRemove);
        }

        StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
        newNode->index = i;
        newNode->value = array[i];

        stack.push(&stack, newNode);
    }

    stack.freeDynamicArray(&stack);

    printf("[");
    for (int i = 0; i < length; i++) printf("%d, ", resultArray[i]);
    printf("]\n");
}

int main() {
    int temperatures[] = {30, 38, 30, 36, 35, 40, 28};
    int length = sizeof(temperatures) / sizeof(temperatures[0]);

    dailyTemperature(temperatures, length);
    return 0;
}
