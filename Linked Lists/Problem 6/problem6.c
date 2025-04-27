#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LENGTH(array) sizeof(array) / sizeof(array[0])

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void linearAppend(Node **head, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    for (Node *temp = *head; temp != NULL; temp = temp->next) {
        if (NULL == temp->next) {
            temp->next = newNode;
            return;
        }
    }
}

void circularAppend(Node **head, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));

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

void betterAppend(Node **head, int *data, int length, int falg) {
    for (int i = 0; i < length; i++) {
        if (falg == 0) {
            linearAppend(head, data[i]);
        } else {
            circularAppend(head, data[i]);
        }
    }
}

void printLinkedList(Node *head, int flag) {
    if (flag == 0) {
        for (Node *temp = head; temp != NULL; temp = temp->next) {
            printf("%d->", temp->data);
        }

        printf("NULL\n");
    } else {
        for (Node *temp = head; temp != NULL; temp = temp->next) {
            printf("%d->", temp->data);
            
            if (temp->next == head) {
                break;
            }
        }

        printf("NULL\n");
    }
}

Node *linearToCircularList(Node *linearHead) {
    Node *head = linearHead;

    for (Node *temp = linearHead; temp != NULL; temp = temp->next) {
        if (temp->next == NULL) {
            temp->next = head;
            return head;
        }
    }

    return NULL;
}

int main(int argc, char const *argv[]) {
    Node *linear = NULL;
    Node *circular = NULL;

    int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
    betterAppend(&linear, data, ARRAY_LENGTH(data), 0);
    printLinkedList(linear, 0);

    circular = linearToCircularList(linear);
    printLinkedList(circular, 1);


    return 0;
}
