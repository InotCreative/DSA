/*
Given a string str, the task is to reverse it using stack. 

Example:

Input: s = "GeeksQuiz"
Output: ziuQskeeG

Input: s = "abc"
Output: cba
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST(comp, message) {if (comp) {perror(message); exit(EXIT_FAILURE);}}

typedef struct StackNode {
    char character;
    
    struct StackNode *next;
    struct StackNode *previous;
} StackNode;

typedef struct Stack {    
    StackNode *head;
    StackNode *tail;

    size_t length;
    void (* push)(struct Stack *, char);
    void (* printStack)(struct Stack *, int);
    void (* freeStack)(struct Stack *);
} Stack;

void push(Stack *stack, char character) {
    StackNode *newStackNode = (StackNode *)malloc(sizeof(StackNode));
    TEST(newStackNode == NULL, "ERROR: MALLOC @ LINE 30");

    newStackNode->character = character;
    newStackNode->next = NULL;

    if (stack->head == NULL) {
        stack->head = newStackNode;
        stack->tail = newStackNode;
        stack->head->previous = NULL;
        stack->length++;
        return;
    }

    newStackNode->next = stack->head;
    stack->head->previous = newStackNode;
    stack->head = newStackNode;
    stack->length++;
}

void printStack(Stack *stack, int flag) {
    switch (flag) {
        case 0: {
            printf("[");
            for (StackNode *temp = stack->head; temp != NULL; temp = temp->next) {
                if (temp->next->next == NULL) {
                    printf("\'%c\'", temp->character);
                    break;
                } else {
                    printf("\'%c\', ", temp->character);
                }
            }
            printf("]\n");

            break;
        } case 1: {
            printf("[");
            for (StackNode *temp = stack->tail; temp != NULL; temp = temp->previous) {
                if (temp->previous->previous == NULL) {
                    printf("\'%c\'", temp->character);
                    break;
                } else {
                    printf("\'%c\', ", temp->character);
                }
            }
            printf("]\n");

            break;
        }
    }
}

void freeStack(Stack *stack) {
    StackNode *temp = NULL;

    while (stack->head != NULL) {
        temp = stack->head;
        stack->head = stack->head->next;

        free(temp);
    }

    stack->head = NULL;
    stack->tail = NULL;
}

Stack initStack() {
    return (Stack){
        .head       = NULL,
        .tail       = NULL,
        .length     = 0,
        .push       = push,
        .printStack = printStack,
        .freeStack  = freeStack
    };
}

void reverseStringStack(const char *string) {
    Stack reversedStringStack = initStack();
    char *reversedString;

    for (int i = 0; i < strlen(string); i++) reversedStringStack.push(&reversedStringStack, string[i]);

    reversedString = (char *)malloc((reversedStringStack.length + 1) * sizeof(char));

    int i = 0;
    for (StackNode *temp = reversedStringStack.head; temp != NULL; temp = temp->next) {
        reversedString[i] = temp->character;
        i++;
    }

    reversedString[reversedStringStack.length] = '\0';

    printf("ORIGINAL STRING: %s\n", string);
    printf("REVERSED STRING: %s\n", reversedString);

    free(reversedString);
}

int main(int argc, char const *argv[]) {
    reverseStringStack("hello world");
    return 0;
}
