#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void append(Node **head, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));

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

void betterAppend(Node **head, int *data, int length) {
    for (int i = 0; i < length; i++) {
        append(head, data[i]);
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

void reverseList(Node **head) {

    if (*head == NULL) {
        printf("LIST EMPTY");
        return;
    }

    if ((*head)->next == NULL) {
        printf("ONLY ONE NODE | REVERSE NO POSSIBLE");
        return;
    }

    Node *previous = NULL;
    Node *next = NULL;
    
    for (Node *current = *head; current != NULL; current = next) {
        next = current->next;
        current->next = previous;
        previous = current;
    }

    *head = previous;
}

int main(int argc, char const *argv[]) {
    Node *head = NULL;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    betterAppend(&head, &data[0], (sizeof(data) / sizeof(int)));
    printList(head);

    reverseList(&head);
    printList(head);
    freeList(&head);

    return 0;
}

