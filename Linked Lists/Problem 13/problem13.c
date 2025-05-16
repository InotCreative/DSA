/*
Deletion at the Beginning in Doubly Linked List
Deletion after a given node in Doubly Linked List
Deletion before a given node in Doubly Linked List
Deletion at a specific position in Doubly Linked List
Deletion at the End in Doubly Linked List
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;

    struct Node *next;
    struct Node *previous;
    struct Node *tail;
} Node;

void append(Node **head, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("ERROR | MALLOC");
        return;
    }

    newNode->data     = data;
    newNode->next     = NULL;
    newNode->previous = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    for (Node *temp = *head; temp != NULL; temp = temp->next) {
        if (temp->next == NULL) {
            temp->next = newNode;
            newNode->previous = temp;

            (*head)->tail = newNode;
            return;
        }
    }
}

void printList(Node *head) {
    if (head == NULL) {
        return;
    }

    printf("FORWARD\n");

    for (Node *temp = head; temp != NULL; temp = temp->next) {
        printf("%d->", temp->data);
    }

    printf("NULL\n");

    printf("\nBACKWARD\n");
    for (Node *temp = head->tail; temp != NULL; temp = temp->previous) {
        printf("%d->", temp->data);
    }

    printf("NULL\n\n");
}

void betterAppend(Node **head, int *array, int length) {
    for (int i = 0; i < length; i++) {
        append(head, array[i]);
    }
}

void freeList(Node **head) {
    Node *temp = NULL;

    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        
        free(temp);
    }

    free(*head);

    *head = NULL;
}

void deleteBeggining(Node **head) {
    if (*head == NULL) {
        printf("LIST EMPTY\n");
        return;
    }

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    Node *temp = *head;
    *head = (*head)->next;

    (*head)->tail = temp->tail;
    (*head)->previous = NULL;

    temp->next = NULL;
    temp->previous = NULL;
    temp->tail = NULL;

    free(temp);
}

void deleteEnd(Node **head) {
    if (*head == NULL) {
        printf("EMPTY LIST\n");
        return;
    }

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    for (Node *temp = *head; temp != NULL; temp = temp->next) {
        if (temp->next != NULL && temp->next->next == NULL) {
            Node *toDelete = temp->next;
            temp->next = NULL;

            (*head)->tail = temp;

            toDelete->previous = NULL;
            toDelete->next = NULL;
            toDelete->tail = NULL;

            free(toDelete);

            return;
        }
    }
}

int main(int argc, char const *argv[]) {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    Node *head = NULL;

    betterAppend(&head, data, (sizeof(data) / sizeof(data[0])));
    printList(head);

    deleteBeggining(&head);
    printList(head);

    deleteEnd(&head);
    printList(head);

    freeList(&head);
    printList(head);

    return 0;
}
