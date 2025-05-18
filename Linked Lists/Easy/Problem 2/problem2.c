/*
Input: linked list: 1->2->3->4->5
Output: 3 
Explanation: There are 5 nodes in the linked list and there is one middle node whose value is 3.


Input: linked list = 10 -> 20 -> 30 -> 40 -> 50 -> 60
Output: 40
Explanation: There are 6 nodes in the linked list, so we have two middle nodes: 30 and 40, but we will return the second middle node which is 40.
*/

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

    Node *temp = *head;

    for (; temp != NULL; temp = temp->next) {
        if (temp->next == NULL) {
            temp->next = newNode;
            return;
        }
    }
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

void printLinkedList(Node *head) {
    for (Node *temp = head; temp != NULL; temp = temp->next) {
        printf("%d->", temp->data);
    }

    printf("NULL\n");
}

void betterAppend(Node **head, int *array, int length) {
    for (int i = 0; i < length; i++) {
        append(head, array[i]);
    }
}

int getLength(Node *head) {
    int length = 0;

    for (Node *temp = head; temp != NULL; temp = temp->next) length++;
    
    return length;
}

void getMiddle(Node *head) {
    int length = getLength(head) / 2;

    for (Node *temp = head; temp != NULL; temp = temp->next) {
        if (length == 0) {
            printf("Middle: %d\n", temp->data);
        }

        length--;
    }
}

int main(int argc, char const *argv[]) {
    int data[] = {1, 2, 3, 4, 5};
    int dataTwo[] = {10, 20, 30, 40, 50, 60};

    Node *head = NULL;
    betterAppend(&head, &data[0], (sizeof(data) / sizeof(data[0])));
    printLinkedList(head);
    getMiddle(head);
    freeList(&head);

    betterAppend(&head, &dataTwo[0], (sizeof(dataTwo) / sizeof(data[0])));
    printLinkedList(head);
    getMiddle(head);
    freeList(&head);

    return 0;
}
