#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void append(Node **head, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("ERROR | MALLOC\n");
        return;
    }

    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    for (Node *temp = *head; temp != NULL; temp = temp->next) {
        if (temp->next == NULL) {
            temp->next = newNode;
            return;
        }
    }
}

void betterAppend(Node **head, int *array, int length) {
    for (int i = 0; i < length; i++) {
        append(head, array[i]);
    }
}

void printList(Node *head) {
    for (Node *temp = head; temp != NULL; temp = temp->next) {
        printf("%d->", temp->data);
    }

    printf("NULL\n");
}

void freeList(Node **head) {
    Node *temp = NULL;

    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;

        free(temp);
    }

    *head = NULL;
}

void swapPair(Node **head) {
    if (*head == NULL) {
        printf("EMPTY LIST\n");
        return;
    }

    if ((*head)->next == NULL) {
        printf("ONLY ONE NODE\n");
        return;
    }

    Node *swapOne = *head;
    Node *swapTwo = (*head)->next;
    Node *restOfList = swapTwo->next;
    Node *previousSwapOneCopy = NULL;

    swapTwo->next = swapOne;
    swapOne->next = restOfList;
    (*head) = swapTwo;
    previousSwapOneCopy = swapOne;

    for (Node *temp = restOfList; temp != NULL; ) {
        swapOne = temp;
        swapTwo = temp->next;
        
        if (restOfList->next == NULL) break;
        else restOfList = swapTwo->next;

        previousSwapOneCopy->next = swapTwo;
        swapTwo->next = swapOne;
        swapOne->next = restOfList;

        previousSwapOneCopy = swapOne;
        temp = restOfList;
    }
}

int main(int argc, char const *argv[]) {
    int array[] = {1, 2, 3, 4, 5, 6};
    int arrayTwo[] = {1, 2, 3, 4, 5};

    Node *head = NULL;

    betterAppend(&head, array, (sizeof(array) / sizeof(array[0])));
    printList(head);
    
    swapPair(&head);
    printList(head);
    
    freeList(&head);

    betterAppend(&head, arrayTwo, (sizeof(arrayTwo) / sizeof(arrayTwo[0])));
    swapPair(&head);
    printList(head);

    freeList(&head);

    return 0;
}
