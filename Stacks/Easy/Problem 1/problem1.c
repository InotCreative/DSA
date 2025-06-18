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
    char symbol;
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

void push(Stack *stack, char symbol) {
    StackNode *newStackNode = (StackNode *)malloc(sizeof(StackNode));
    TEST((newStackNode == NULL), "MALLOC\n");

    newStackNode->next     = NULL;
    newStackNode->previous = NULL;
    newStackNode->symbol   = symbol;

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
        printf("FORWARD TRAVLE\n");
        for (StackNode *temp = stack->head; temp != NULL; temp = temp->next) printf("%c->", temp->symbol);
        printf("NULL\n");
    } else {
        printf("BACKWARD TRAVLE\n");
        for (StackNode *temp = stack->tail; temp != NULL; temp = temp->previous) printf("%c->", temp->symbol);
        printf("NULL\n");
    }
}

void freeStack(Stack *stack) {
    StackNode *temp = NULL;

    while(stack->head != NULL) {
        temp = stack->head;
        stack->head = stack->head->next;

        free(temp);
    }
}

StackNode *pop(Stack *stack) {
    StackNode *returnAddress = stack->head;

    stack->head = stack->head->next;

    if (stack->head != NULL) stack->head->previous = NULL;
    else stack->tail = NULL;

    return returnAddress;
}

Stack initStack() {
    return (Stack){
        .head       = NULL,
        .tail       = NULL,
        .freeStack  = freeStack,
        .push       = push,
        .printStack = printStack,
        .pop        = pop
    };
}

bool isValidParenthesis(char *string) {
    if (strlen(string) % 2 != 0) return false;

    bool isValid = false;
    Stack symbolStack = initStack();

    for (char *character = &string[0]; *character != '\0'; character++) {
        if (*character == '(' || *character == '{' || *character == '[') {
            symbolStack.push(&symbolStack, *character);
        }

        if (*character == ')' || *character == '}' || *character == ']') {
            StackNode *opeaningSymbol = symbolStack.pop(&symbolStack);

            switch (*character) {
                case ')': 
                    if (opeaningSymbol->symbol == '(') isValid = true;
                    else return false;
                    break;
                case '}':
                    if (opeaningSymbol->symbol == '{') isValid = true;
                    else return false;
                    break;
                case ']':
                    if (opeaningSymbol->symbol == '[') isValid = true;
                    else return false;
                    break;
            }

            free(opeaningSymbol);
        }
    }

    symbolStack.freeStack(&symbolStack);
    return isValid;

}

int main(int argc, char const *argv[]) {
    isValidParenthesis("[{()}]") ? printf("True\n") : printf("False\n");
    isValidParenthesis("[()()]{}") ? printf("True\n") : printf("False\n");
    isValidParenthesis("([]") ? printf("True\n") : printf("False\n");
    isValidParenthesis("([{]})") ? printf("True\n") : printf("False\n");

}