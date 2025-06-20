#include <stdio.h>
#include <stdlib.h>

#define PTR_MEM_TEST(ptr, cmp, message) {if (ptr == cmp) {perror(message); exit(EXIT_FAILURE);}}

typedef struct BinaryTreeNode {
    int value;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} BinaryTreeNode;

typedef struct StackNode {
    BinaryTreeNode *binaryTreeNode;
    struct StackNode *next;
    struct StackNode *previous;
} StackNode;

typedef struct Stack {
    StackNode *head;
    StackNode *tail;

    void (*push)(struct Stack *, BinaryTreeNode *);
    void (*printStack)(struct Stack *, int);
    void (*freeStack)(struct Stack *);
    StackNode *(*pop)(struct Stack *);
} Stack;

void push(Stack *stack, BinaryTreeNode *binaryTreeNode) {
    StackNode *newStackNode = (StackNode *)malloc(sizeof(StackNode));
    PTR_MEM_TEST(newStackNode, NULL, "MALLOC");

    newStackNode->binaryTreeNode = binaryTreeNode;
    newStackNode->next = NULL;
    newStackNode->previous = NULL;

    if (stack->head == NULL) {
        stack->head = newStackNode;
        stack->tail = newStackNode;
        return;
    }

    newStackNode->next = stack->head;
    stack->head->previous = newStackNode;
    stack->head = newStackNode;
}

StackNode *pop(Stack *stack) {
    if (stack->head == NULL) {
        return NULL;
    }

    StackNode *poppedNode = stack->head;
    stack->head = stack->head->next;

    if (stack->head != NULL) {
        stack->head->previous = NULL;
    } else {
        stack->tail = NULL;
    }

    poppedNode->next = NULL;
    poppedNode->previous = NULL;

    return poppedNode;
}

void printStack(Stack *stack, int flag) {
    switch (flag) {
        case 1: {
            for (StackNode *temp = stack->head; temp != NULL; temp = temp->next) {
                printf("BinaryTreeNode value: %d\n", temp->binaryTreeNode->value);
            }
            break;
        }
        case 2: {
            for (StackNode *temp = stack->tail; temp != NULL; temp = temp->previous) {
                printf("BinaryTreeNode value: %d\n", temp->binaryTreeNode->value);
            }
            break;
        }
        default: {
            printf("Invalid flag value. Use 1 for forward, 2 for backward.\n");
            break;
        }
    }
}

void freeStack(Stack *stack) {
    StackNode *current = stack->head;

    while (current != NULL) {
        StackNode *temp = current;
        
        current = current->next;
        free(temp);
    }

    stack->head = NULL;
    stack->tail = NULL;
}

Stack initStack() {
    return (Stack) {
        .head       = NULL,
        .tail       = NULL,
        .push       = push,
        .pop        = pop,
        .printStack = printStack,
        .freeStack  = freeStack
    };
}

void flattenBinayTree(BinaryTreeNode *head, Stack *stack) {

    if (head == NULL) return;

    stack->push(stack, head);
    flattenBinayTree(head->left, stack);
    flattenBinayTree(head->right, stack);
}

int main(int argc, char const *argv[]) {
    BinaryTreeNode *nodeOne   = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    nodeOne->value = 1;
    BinaryTreeNode *nodeTwo   = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    nodeTwo->value = 2;
    BinaryTreeNode *nodeThree = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    nodeThree->value = 3;
    BinaryTreeNode *nodeFour  = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    nodeFour->value = 4;
    BinaryTreeNode *nodeFive  = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    nodeFive->value = 5;
    BinaryTreeNode *nodeSix   = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    nodeSix->value = 6;

    nodeOne->left  = nodeTwo;
    nodeOne->right = nodeFive;
    nodeTwo->left  = nodeThree;
    nodeTwo->right = nodeFour;
    nodeFive->left = nodeSix;

    Stack flattenedStack = initStack();
    flattenBinayTree(nodeOne, &flattenedStack);
    flattenedStack.printStack(&flattenedStack, 2);

    return 0;
}
