#include <stdio.h>
#include <stdlib.h>

#define INITAL_CAPACITY 8
#define TEST(ptr, cmp, message) {if(ptr == cmp) {perror(message); return;}}

typedef struct DynamicArray {
    size_t size;
    size_t capacity;

    void **nodeAddresses;

    void (* append)(struct DynamicArray *, void *);
    void *(* dequeue)(struct DynamicArray *, int);
    void (* freeArray)(struct DynamicArray *);
} DynamicArray;

typedef struct BinaryTreeNode {
    int data;

    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} BinaryTeeNode;

void growArray(DynamicArray *array) {
    if (array->size == 0) {
        array->capacity = INITAL_CAPACITY;
        void **temp = (void **)malloc(array->capacity * sizeof(void *));
        TEST(temp, NULL, "MALLOC");

        array->nodeAddresses = temp;
        return;
    }

    if (array->size + 1 > array->capacity) {
        array->capacity *= 2;
        void **temp = (void **)realloc(array->nodeAddresses, array->capacity * sizeof(void *));
        TEST(temp, NULL, "MALLOC");

        array->nodeAddresses = temp;
        return;
    }
}

void append(DynamicArray *array, void *address) {
    growArray(array);
    array->nodeAddresses[array->size] = address;
    array->size++;
}

void *dequeue(DynamicArray *array, int index) {
    if (!array || index < 0 || index >= array->size) return NULL;

    void *address = array->nodeAddresses[index];

    for (int i = index + 1; i < array->size; i++) {
        array->nodeAddresses[i - 1] = array->nodeAddresses[i];
    }

    array->size--;
    return address;
}

void freeArray(DynamicArray *array) {
    for (int i = 0; i < array->size; i++) {
        if (array->nodeAddresses[i] != NULL) free(array->nodeAddresses[i]);
    }

    free(array->nodeAddresses);
}

BinaryTeeNode *createNode(int data) {
    BinaryTeeNode *newNode = (BinaryTeeNode *)malloc(sizeof(BinaryTeeNode));
    
    newNode->data  = data;
    newNode->left  = NULL;
    newNode->right = NULL;

    return newNode;
}

DynamicArray init() {
    return (DynamicArray){
        .capacity = 0,
        .size = 0,
        .nodeAddresses = NULL,
        .append = append,
        .dequeue = dequeue,
        .freeArray = freeArray
    };
}

int minimumDepth(BinaryTeeNode *root) {
    if (root == NULL) return 0;

    DynamicArray array = init();
    array.append(&array, root);

    int depth = 1;

    while (array.size > 0) {
        int levelSize = array.size;

        for (int i = 0; i < levelSize; i++) {
            BinaryTeeNode *current = (BinaryTeeNode *)array.dequeue(&array, 0);

            if (current->left == NULL && current->right == NULL) {
                array.freeArray(&array);
                return depth;
            }

            if (current->left != NULL) {
                array.append(&array, current->left);
            }

            if (current->right != NULL) {
                array.append(&array, current->right);
            }
        }

        depth++;
    }
}

int main(int argc, char const *argv[]) {    
    BinaryTeeNode *nodeOne   = createNode(1);
    BinaryTeeNode *nodeTwo   = createNode(2);
    BinaryTeeNode *nodeThree = createNode(3);
    BinaryTeeNode *nodeFour  = createNode(4);
    BinaryTeeNode *nodeFive  = createNode(5);
    
    nodeOne->left = nodeTwo;
    nodeOne->right = nodeThree;
    nodeTwo->left = nodeFour;
    nodeTwo->right = nodeFive;

    printf("MINIMUM DEPTH: %d\n", minimumDepth(nodeOne));

    return 0;
}
