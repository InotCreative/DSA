#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_TEST(ptr, cmp, message) {if(ptr == cmp){perror(message); exit(EXIT_FAILURE);}}

typedef struct StackNode {
    int symbol;
    struct StackNode *next;
    struct StackNode *previous;
} StackNode;

typedef struct Stack {
    StackNode *head;
    StackNode *tail;

    void (* push)(struct Stack *, int);
    StackNode *(* pop)(struct Stack *);
    void (* freeStack)(struct Stack *);
    void (* printStack)(struct Stack *, int);
} Stack;

void push(Stack *stack, int symbol) {
    StackNode *newStackNode = (StackNode *)malloc(sizeof(StackNode));
    MEM_TEST(newStackNode, NULL, "MALLOC\n");

    newStackNode->symbol   = symbol;
    newStackNode->next     = NULL;
    newStackNode->previous = NULL;

    if (stack->head == NULL) {
        stack->head            = newStackNode;
        newStackNode->previous = NULL;
        newStackNode->next     = NULL;
        stack->tail            = newStackNode;
        return;
    }

    newStackNode->next = stack->head;
    stack->head->previous = newStackNode;
    stack->head = newStackNode;
}

StackNode *pop(Stack *stack) {
    if (stack->head == NULL) return NULL;

    StackNode *returnAddress = stack->head;
    stack->head = stack->head->next;

    if (stack->head != NULL) stack->head->previous = NULL;
    else stack->tail = NULL;

    return returnAddress;
}

void printStack(Stack *stack, int flag) {
    if (flag == 0) {
        printf("FORWARD TRAVLE\n");
        for (StackNode *temp = stack->head; temp != NULL; temp = temp->next) printf("%d->", temp->symbol);
        printf("NULL\n");
    } else {
        printf("BACKWARD TRAVLE\n");
        for (StackNode *temp = stack->tail; temp != NULL; temp = temp->previous) printf("%d->", temp->symbol);
        printf("NULL\n");
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
        .push       = push,
        .pop        = pop,
        .freeStack  = freeStack,
        .printStack = printStack
    };
}

long double evulateReversePolish(char *arrayOfSymbols[], int length) {
    Stack solution = initStack();

    for (int i = 0; i < length; i++) {
        if ((strcmp(arrayOfSymbols[i], "+") == 0) || (strcmp(arrayOfSymbols[i], "-") == 0) || (strcmp(arrayOfSymbols[i], "*") == 0) || (strcmp(arrayOfSymbols[i], "/") == 0)) {
            StackNode *firstOperand = solution.pop(&solution);
            StackNode *secondOperand = solution.pop(&solution);

            switch (arrayOfSymbols[i][0]) {
                case '+':
                    solution.push(&solution, (firstOperand->symbol + secondOperand->symbol));
                    break;
                case '-':
                    solution.push(&solution, (firstOperand->symbol - secondOperand->symbol));
                    break;
                case '*':
                    solution.push(&solution, (firstOperand->symbol * secondOperand->symbol));
                    break;
                case '/':
                    solution.push(&solution, (secondOperand->symbol / firstOperand->symbol));
                    break;
            }

            free(firstOperand);
            free(secondOperand);
        } else {
            solution.push(&solution, atoi(arrayOfSymbols[i]));
        }
    }

    StackNode *answer = solution.pop(&solution);
    long double finalAnswer = ((long double)answer->symbol);

    free(answer);
    solution.freeStack(&solution);

    return finalAnswer;
}

int main(int argc, char const *argv[]) {
    char *token[] = {"2","1","+","3","*"};
    char *tokenTwo[] = {"4","13","5","/","+"};
    char *tokenThree[] = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"};

    printf("%LF\n", evulateReversePolish(token, (sizeof(token) / sizeof(token[0]))));
    printf("%LF\n", evulateReversePolish(tokenTwo, (sizeof(tokenTwo) / sizeof(tokenTwo[0]))));
    printf("%LF\n", evulateReversePolish(tokenThree, (sizeof(tokenThree) / sizeof(tokenThree[0]))));

    return 0;
}
