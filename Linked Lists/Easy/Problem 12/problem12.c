/*
Exchange first and last nodes in Circular Linked List
Given Circular linked list exchange the first and the last node. The task should be done with only one extra node,
you can not declare more than one extra node, and also you are not allowed to declare any other temporary variable. 
*/

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
        newNode->next = *head;

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

void betterAppend(Node **head, int *array, int length) {
    for (int i = 0; i < length; i++) {
        append(head, array[i]);
    }
}

void printArray(Node *head) {
    for (Node *temp = head; temp != NULL; temp = temp->next) {
        printf("%d->", temp->data);
        
        if (temp->next == head) {
            printf("NULL\n");
            return;
        }
    }
}

void swapFirstAndLast(Node **head) {
    Node *restOfList = (*head)->next;
    Node *headPtr = *head;

    for (Node *temp = *head; ; temp = temp->next) {
        if (temp->next->next == *head) {
            Node *lastNode = temp->next;
            Node *beforeLastNode = temp;

            beforeLastNode->next = headPtr;
            headPtr->next = lastNode;
            lastNode->next = restOfList;

            *head = lastNode;
            return;
        }
    }
}

int main(int argc, char const *argv[]) {
    Node *head = NULL;

    int data[] = {5, 1, 2, 3, 4, 19};
    betterAppend(&head, &data[0], (sizeof(data) / sizeof(data[0])));

    printArray(head);

    swapFirstAndLast(&head);
    printArray(head);

    return 0;
}
