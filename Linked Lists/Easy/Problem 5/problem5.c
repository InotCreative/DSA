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

    newNode->next = *head;
    *head = newNode;
    (*head)->next = newNode;
}

void betterAppend(Node **head, int *data, int length) {
    for (int i = 0; i < length; i++) {
        append(head, data[i]);
    }
}

void printList(Node *head) {
    for (Node *temp = head; temp != NULL; temp = temp->next) {
        printf("%d->", temp->data);

        if (temp->next == head) {
            break;
        }
    }

    printf("NULL\n");
}

void freeList(Node **head) {
    if (*head == NULL) {
        return;
    }

    Node *temp = *head;
    Node *nextNode = NULL;

    while (temp->next != head) {
        nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }

    free(temp);

    *head = NULL;
}

int main(int argc, char const *argv[]) {
    int data[] = {1, 2, 3, 4, 5, 6};
    Node *head = NULL;
    
    betterAppend(&head, data, (sizeof(data) / sizeof(data[0])));
    printList(head);
    freeList(&head);
    printList(head);

    return 0;
}
