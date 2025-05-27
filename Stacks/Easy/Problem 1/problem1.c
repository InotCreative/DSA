/*
Given a string s representing an expression containing various types of brackets: {}, (), and [],
the task is to determine whether the brackets in the expression are balanced or not. A balanced expression
is one where every opening bracket has a corresponding closing bracket in the correct order.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TEST(condition, message) {if (condition) {perror(message); exit(EXIT_FAILURE);}}

typedef struct StackNode {
    char character;
    struct StackNode *next;
    struct StackNode *previous;
} StackNode;

typedef struct Stack {
    StackNode *head;
    StackNode *tail;

    void (* push)(struct Stack *, char);
    void (* printStack)(struct Stack *, int);
    void (* freeStack)(struct Stack *);
    StackNode *(* pop)(struct Stack *);
} Stack;

void push(Stack *stack, char character) {
    StackNode *newStackNode = (StackNode *)malloc(sizeof(StackNode));
    TEST((newStackNode == NULL), "MALLOC @ LINE 24");   
    
    newStackNode->character = character;
    newStackNode->next      = NULL;
    newStackNode->previous  = NULL;

    if (stack->head == NULL) {
        stack->head = newStackNode;
        stack->tail = newStackNode;
        newStackNode->previous = NULL;

        return;
    }

    newStackNode->next = stack->head;
    stack->head->previous = newStackNode;
    stack->head = newStackNode;
}

void printStack(Stack *stack, int flag) {
    if (flag == 0) {
        printf("[");

        for (StackNode *temp = stack->head; temp != NULL; temp = temp->next) {
            printf("\'%c\', ", temp->character);
        }

        printf("]\n");
    } else if (flag == 1) {
        printf("[");

        for (StackNode *temp = stack->tail; temp != NULL; temp = temp->previous) {
            printf("\'%c\', ", temp->character);
        }

        printf("]\n");
    }
}

void freeStack(Stack *stack) {
    StackNode *temp = NULL;

    while (stack->head != NULL) {
        temp = stack->head;
        stack->head = stack->head->next;

        free(temp);
    }

    stack->head       = NULL;
    stack->tail       = NULL;
    stack->freeStack  = freeStack;
    stack->printStack = printStack;
    stack->push       = push;
}

StackNode *pop(Stack *stack) {
    if (stack->head == NULL) return NULL;

    StackNode *returnAddress = stack->head;
    stack->head = stack->head->next;

    if (stack->head != NULL) stack->head->previous = NULL;
    else stack->tail = NULL;

    return returnAddress;
}

Stack initStack() {
    return (Stack){
        .head       = NULL,
        .push       = push,
        .tail       = NULL,
        .printStack = printStack,
        .freeStack  = freeStack,
        .pop        = pop
    };
}

bool isValidParenthesis(const char *expression) {
    Stack expressionStack = initStack();

    for (int i = 0; i < strlen(expression); i++) {
        char character = expression[i];

        if (character == '(' || character == '{' || character == '[') {
            expressionStack.push(&expressionStack, character);
        } else if (character == ')' || character == '}' || character == ']') {
            StackNode *top = expressionStack.pop(&expressionStack);

            if (top == NULL) {
                expressionStack.freeStack(&expressionStack);
                return false;
            }

            char open = top->character;
            free(top);

            if ((open == '(' && character != ')') ||
                (open == '[' && character != ']') ||
                (open == '{' && character != '}')) {
                expressionStack.freeStack(&expressionStack);
                return false;
            }
        }
    }

    bool isBalanced = (expressionStack.head == NULL);
    expressionStack.freeStack(&expressionStack);
    return isBalanced;
}

int main(int argc, char const *argv[]) {
    printf("%s\n", isValidParenthesis("[{()}]") ? "VALID PARENTHESIS" : "PARENTHESIS MISMATCH");

}