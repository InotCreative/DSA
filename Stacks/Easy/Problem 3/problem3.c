/*
Write a program to convert an Infix expression to Postfix form.

Infix expression: The expression of the form "a operator b" (a + b) i.e., when an operator is in-between every pair of operands.
Postfix expression: The expression of the form "a b operator" (ab+) i.e., When every pair of operands is followed by an operator.

Examples:

Input: s = "A*(B+C)/D"
Output: ABC+*D/

Input: s = "a+b*(c^d-e)^(f+g*h)-i"
Output: abcd^e-fgh*+^*+i- 
*/

/* TO-DO: IMPLEMENT A STR TOKENIZER */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TEST(comp, message) {if (comp) {printf(message); exit(EXIT_FAILURE);}}

typedef struct QueueNode {
    char operator;
    int precedent;

    struct QueueNode *next;
    struct QueueNode *previous;
} QueueNode;

typedef struct Deque {
    QueueNode *head;
    QueueNode *tail;

    size_t length;

    void (* enqueue)(struct Deque *, char);
    void (* push)(struct Deque *, char);
    QueueNode *(* pop)(struct Deque *);
    int (* peek)(struct Deque *);
    void (* printDeque)(struct Deque *, int);
    void (* freeDeque)(struct Deque *);
} Deque;

void enqueue(Deque *queue, char operator) {
    QueueNode *newQueueNode = (QueueNode *)malloc(sizeof(QueueNode));
    TEST((newQueueNode == NULL), "MALLOC ERROR @ LINE 45");

    newQueueNode->operator = operator;

    switch (operator) {
        case '(':
        case ')':
            newQueueNode->precedent = 4;
            break;
        case '^':
            newQueueNode->precedent = 3;
            break;
        case '*':
        case '/':
            newQueueNode->precedent = 2;
            break;
        case '+':
        case '-':
            newQueueNode->precedent = 1;
            break;
    }

    if (queue->head == NULL) {
        queue->head = newQueueNode;
        queue->tail = newQueueNode;
        newQueueNode->next = NULL;
        newQueueNode->previous = NULL;
        queue->length++;
        return;
    }

    queue->tail->next = newQueueNode;
    newQueueNode->previous = queue->tail;
    queue->tail = newQueueNode;
    queue->length++;
}

int getPrecedence(char operator) {
    switch (operator) {
        case '(':
        case ')':
            return 4;
            break;
        case '^':
            return 3;
            break;
        case '*':
        case '/':
            return 2;
            break;
        case '+':
        case '-':
            return 1;
            break;
    }
}

void push(Deque *queue, char operator) {
    QueueNode *newQueueNode = (QueueNode *)malloc(sizeof(QueueNode));
    TEST((newQueueNode == NULL), "MALLOC ERROR @ LINE 45");

    newQueueNode->operator = operator;
    newQueueNode->precedent = getPrecedence(operator);

    if (queue->head == NULL) {
        queue->head = newQueueNode;
        queue->tail = newQueueNode;
        newQueueNode->next = NULL;
        newQueueNode->previous = NULL;
        queue->length++;
        return;
    }

    newQueueNode->next = queue->head;
    queue->head->previous = newQueueNode;
    queue->head = newQueueNode;
    queue->length++;
}

void printDeque(Deque *queue, int flag) {
    if (flag == 0) {
        for (QueueNode *temp = queue->head; temp != NULL; temp = temp->next) {
            printf("\'%c\'->", temp->operator);
        }

        printf("NULL\n");
    } else if (flag == 1) {
        for (QueueNode *temp = queue->tail; temp != NULL; temp = temp->previous) {
            printf("\'%c\'->", temp->operator);
        }

        printf("NULL\n");
    }
}

void freeQueue(Deque *queue) {
    QueueNode *temp = NULL;

    while (queue->head != NULL) {
        temp = queue->head;
        queue->head = queue->head->next;

        free(temp);
    }

    queue->head = NULL;
    queue->tail = NULL;
}

int peek(Deque *queue) {
    return queue->head->precedent;
}
QueueNode *pop(Deque *queue) {
    TEST((queue->head == NULL), "QUEUE EMPTY @ LINE 159");

    QueueNode *returnAddress = queue->head;

    queue->head = queue->head->next;
    if (queue->head != NULL) {
        queue->head->previous = NULL;
    } else {
        queue->tail = NULL;
    }

    queue->length--;

    return returnAddress;
}

Deque initDeque() {
    return (Deque){
        .head       = NULL,
        .tail       = NULL,
        .length     = 0,
        .enqueue    = enqueue,
        .push       = push,
        .pop        = pop,
        .printDeque = printDeque,
        .freeDeque  = freeQueue,
        .peek       = peek
    };
}

char *converyQueueToString(Deque *queue) {
    char *string = (char *)malloc((queue->length + 1) * sizeof(char));
    int i = 0;

    for (QueueNode *temp = queue->head; temp != NULL; temp = temp->next) {
        string[i] = temp->operator;
        i++;
    }

    string[queue->length] = '\0';
    return string;
}

char *infixToPostfix(char *infixExpression) {
    Deque operators = initDeque();
    Deque output = initDeque();

    for (int i = 0; i < strlen(infixExpression); i++) {
        if (isalnum(infixExpression[i])) {
            output.enqueue(&output, infixExpression[i]);
        } else if (infixExpression[i] == '+' || infixExpression[i] == '-' || infixExpression[i] == '*' || infixExpression[i] == '/') {
            if (operators.length == 0) {
                operators.push(&operators, infixExpression[i]);
                continue;
            }

            int previousPrecedent = operators.peek(&operators);
            int currentPrecedent = getPrecedence(infixExpression[i]);

            if (currentPrecedent <= previousPrecedent) {
                QueueNode *nodeToDelte = operators.pop(&operators);
                
                output.enqueue(&output, nodeToDelte->operator);

                operators.push(&operators, infixExpression[i]);
                free(nodeToDelte);
            } else if (currentPrecedent >= previousPrecedent) {
                operators.push(&operators, infixExpression[i]);
            }

        } else if (infixExpression[i] == ' ') continue;
    }

    for (QueueNode *temp = operators.head; temp != NULL; temp = temp->next) {
        QueueNode *toDelete = operators.pop(&operators);
        output.enqueue(&output, toDelete->operator);

        free(toDelete);
    }

    char *postfix = converyQueueToString(&output);
    
    operators.freeDeque(&operators);
    output.freeDeque(&output);

    return postfix;

}

int main(int argc, char const *argv[]) {
    char *postfix = infixToPostfix("3 + 2 * 3 / 3 * 2 * 2 / 3 + 2 - 8");
    printf("%s\n", postfix);

    free(postfix);
    return 0;
}
