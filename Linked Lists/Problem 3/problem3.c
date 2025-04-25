/*
Input : head: 1->2->1->2->1->3->1 , key = 1
Output : 4
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

void deleteList(Node **head) {
    Node *temp = NULL;

    while (*head != NULL) {
        temp = *head;

        *head = (*head)->next;
        free(temp);
    }

    *head = NULL;
}

void betterAppend(Node **head, int *data, int length) {
    for (int i = 0; i < length; i++) {
        append(head, data[i]);
    }
}

void countOccurances(Node **head, int key, int *count) {
    if (*head == NULL) {
        printf("Count of %d: %d\n", key, *count);
        return;
    }

    if ((*head)->data == key) (*count)++;

    countOccurances(&((*head)->next), key, count);
}

int main(int argc, char const *argv[]) {
    Node *head = NULL;
    int count = 0;
    
    int data[] = {1, 2, 1, 2, 1, 3, 1};
    int dataTwo[] = {1, 2, 1, 2, 1};

    betterAppend(&head, data, (sizeof(data) / sizeof(data[0])));
    printList(head);
    countOccurances(&head, 1, &count);
    deleteList(&head);

    count = 0;
    betterAppend(&head, dataTwo, (sizeof(dataTwo) / sizeof(dataTwo[0])));
    printList(head);
    countOccurances(&head, 3, &count);

    return 0;
}
