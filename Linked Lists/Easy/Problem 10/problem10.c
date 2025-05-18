#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int index;
    struct Node *next;
} Node;

void append(Node **head, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("ERROR | MALLOC");
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

void printList(Node *head) {
    for (Node *temp = head; temp != NULL; temp = temp->next) {
        printf("%d->", temp->data);
    }

    printf("NULL\n");
}

void betterAppend(Node **head, int *data, int length) {
    for (int i = 0; i < length; i++) {
        append(head, data[i]);
    }
}

void deleteList(Node **head) {
    Node *temp = NULL;

    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;

        free(temp);
    }

    *head = NULL;
}

void partation()

int main(int argc, char *argv[]) {
    int data[] = {5, 4, 1, 3, 2};
    int length = sizeof(data) / sizeof(data[0]);

    Node *head = NULL;

    betterAppend(&head, data, length);
    printList(head);

    return 0;
}