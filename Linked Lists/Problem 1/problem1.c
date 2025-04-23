#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int index;
    struct Node *next;
} Node;


void append(Node **head, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    int index = 0;

    newNode->data = data;
    newNode->next = NULL;
    newNode->index = index;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node *temp = *head;

    for (; temp != NULL; temp=temp->next) {
        index++;

        if (temp->next == NULL) {
            newNode->index = index;
            
            temp->next = newNode;
            return;
        }
    }
}

void printList(Node *head) {
    for (Node *temp = head; temp != NULL; temp = temp->next) {
        printf("[Value: %d | Index: %d]->", temp->data, temp->index);
    }

    printf("NULL\n");
}

void freeLinkedList(Node **head) {
    Node *temp;

    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *head = NULL;
}

int main() {
    /*
        Input: LinkedList: 1 -> 2 -> 3 -> 4 -> 5 -> 6, k = 2
        Output: 1 -> 3 -> 5 
        Explanation: After removing every 2nd node of the linked list, the resultant linked list will be: 1 -> 3 -> 5 .


        Input: LinkedList: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10, k = 3
        Output: 1 -> 2 -> 4 -> 5 -> 7 -> 8 -> 10
        Explanation: After removing every 3rd node of the linked list, the resultant linked list will be: 1 -> 2 -> 4 -> 5 -> 7 -> 8 -> 10.
    */

    Node *head = NULL;
    
    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);
    append(&head, 5);
    append(&head, 6);

    printList(head);
    freeLinkedList(&head);
    printList(head);

    return 0;
}