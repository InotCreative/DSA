#include <stdio.h>
#include <stdlib.h>

#define PTR_MEM_TEST(ptr, cmp, message) {if (ptr == cmp) {perror(message); exit(EXIT_FAILURE);}}

typedef struct DynamicIntArray {
    int size;
    int capacity;

    int *array;

    void (* reverseArray)(struct DynamicIntArray *);
    void (* push)(struct DynamicIntArray *, int);
    //int (* pop)(struct DynamicIntArray *);
    void (* printArray)(struct DynamicIntArray *);
} DynamicIntArray;

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void reverseArray(DynamicIntArray *dynamicArray) {
    int middle = dynamicArray->size / 2;
    for (int start = 0, end = dynamicArray->size - 1; start < middle; start++) {
        swap(&dynamicArray->array[start], &dynamicArray->array[end]);
    }
}

void growArray(DynamicIntArray *dynamicArray) {
    if (dynamicArray->capacity == 0) {
        dynamicArray->capacity = 8;
        int *mallocArray = (int *)malloc(dynamicArray->capacity * sizeof(int));
        PTR_MEM_TEST(mallocArray, NULL, "MALLOC\n");

        dynamicArray->array = mallocArray;
        return;
    }

    if (dynamicArray->size >= dynamicArray->capacity) {
        dynamicArray->capacity *= 2;
        int *mallocArray = (int *)malloc(dynamicArray->capacity * sizeof(int));
        PTR_MEM_TEST(mallocArray, NULL, "REALLOC\n");

        dynamicArray->array = mallocArray;
        return;
    }
}

void push(DynamicIntArray *dynamicArray, int value) {
    growArray(dynamicArray);
    dynamicArray->array[dynamicArray->size++] = value;
    reverseArray(dynamicArray);

}

void printArray(DynamicIntArray *dynamicArray) {
    printf("[");
    for (int i = 0; i < dynamicArray->size; i++) printf("%d, ", dynamicArray->array[i]);
    printf("]\n");
}

DynamicIntArray initDynamicArray() {
    return (DynamicIntArray) {
        .size = 0,
        .capacity = 0,
        .array = NULL,
        .push = push,
        //.pop = pop,
        .printArray = printArray,
        .reverseArray = reverseArray
    };
}

DynamicIntArray *dailyTempurature(int *array) {
    
}

int main(int argc, char const *argv[]) {

}
