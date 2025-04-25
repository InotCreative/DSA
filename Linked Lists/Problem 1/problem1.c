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

    if (*head == NULL) {
        newNode->index = 0;
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

void betterAppend(Node **head, int *data, int length) {
    for (int i = 0; i < length; i++) {
        append(head, data[i]);
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

void printList(Node *head) {
    for (Node *temp = head; temp != NULL; temp = temp->next) {
        printf("%d->", temp->data);
    }

    printf("NULL\n");
}


void removeNode(Node **head, int index) {
    Node *toDelete = NULL;

    if (index == 0) {
        toDelete = *head;
        *head = (*head)->next;

        free(toDelete);
        return;
    }

    for (Node *temp = *head; temp != NULL; temp = temp->next) {
        if (temp->next->index == index) {
            toDelete = temp->next;
            temp->next = toDelete->next;

            free(toDelete);
            return;
        }
    }
}

void removeKthList(Node **head, int k) {
    int length = 1;

    for (Node *temp = *head; temp != NULL; temp = temp->next) {
        length++;
    }

    int *indicesToRemove = (int *)malloc(length * sizeof(int));
    int arrayIndex = 0;

    for (Node *temp = *head; temp != NULL; temp = temp->next) {
        if ((temp->index + 1) % k != 0) {
            indicesToRemove[arrayIndex] = temp->index;
            arrayIndex++;
        }
    }

    for (int i = 0; i < arrayIndex; i++) {
        removeNode(head, indicesToRemove[i]);
    }

}


int main() {
    /*
        Input: LinkedList: 1 -> 2 -> 3 -> 4 -> 5 -> 6, k = 2
                           1.   2.   3.   4.   5.   6
        Output: 1 -> 3 -> 5 
        Explanation: After removing every 2nd node of the linked list, the resultant linked list will be: 1 -> 3 -> 5 .


        Input: LinkedList: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10, k = 3
                           1.   2.   3.   4.   5.   6.   7.   8.   9.   10
        Output: 1 -> 2 -> 4 -> 5 -> 7 -> 8 -> 10
        Explanation: After removing every 3rd node of the linked list, the resultant linked list will be: 1 -> 2 -> 4 -> 5 -> 7 -> 8 -> 10.
    */

    int data[] = {1, 2, 3, 4, 5, 6};
    int dataTwo[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    Node *list = NULL;
    betterAppend(&list, &data[0], (sizeof(data) / sizeof(data[0])));
    removeKthList(&list, 2);
    
    printList(list);
    freeList(&list);


    betterAppend(&list, &dataTwo[0], (sizeof(dataTwo) / sizeof(data[0])));
    removeKthList(&list, 3);

    printList(list);
    freeList(&list);

    return 0;
}