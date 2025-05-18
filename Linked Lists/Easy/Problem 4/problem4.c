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
        (*head)->next = *head;
        return;
    }

    for (Node *temp = *head; temp != NULL; temp = temp->next) {
        if (temp->next == *head) {
            temp->next = newNode;
            newNode->next = *head;
            return;
        }
    }
}

void betterAppend(Node **head, int *data, int length) {
    for (int i = 0; i < length; i++) {
        append(head, data[i]);
    }
}

void printArray(Node *head) {
    for (Node *temp = head; temp != NULL; temp = temp->next) {
        printf("%d->", temp->data);

        if (temp->next == head) {
            break;
        }
    }

    printf("NULL\n");
}

int main(int argc, char const *argv[]) {
    Node *head = NULL;

    int data[] = {1, 2, 3, 4, 5, 6};
    betterAppend(&head, &data[0], (sizeof(data) / sizeof(data[0])));
    printArray(head);

    return 0;
}
