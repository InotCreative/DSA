/*
In this article, we will learn how to delete a node from a circular linked list. In a circular linked list, the last node connects back to the first node, creating a loop.

There are three main ways to delete a node from circular linked list:

Deletion at the beginning
Deletion at specific position
Deletion at the end
Now, let’s look at the methods and steps for these three deletion operations.
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
        return NULL;
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

void printList(Node *head) {
    for (Node *temp = head; temp != NULL; temp = temp->next) {
        printf("%d->", temp->data);
        
        if (temp->next == head) {
            printf("NULL\n");
            return;
        }
    }

}

void freeList(Node **head) {
    if (*head == NULL) {
        printf("LIST EMPTY\n");
        return;
    }

    Node *temp = NULL;
    Node *current = (*head)->next;

    while (current != *head) {
        temp = current;
        current = current->next;

        free(temp);
    }

    free(*head);
    *head = NULL;
}

void deleteBeggining(Node **head) {
    if (*head == NULL) {
        printf("LIST EMPTY");
        return;
    }

    if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
        return;
    }

    Node *oldHead = *head;
    Node *newHead = (*head)->next;

    for (Node *temp = oldHead; ; temp = temp->next) {
        if (temp->next == oldHead) {
            temp->next = newHead;
            break;
        }
    }

    free(oldHead);

    (*head) = newHead;
}

void deleteEnd(Node **head) {
    if (*head == NULL) {
        printf("LIST EMPTY\n");
        return;
    }

    if ((*head)->next == *head) {
        free(*head);
        *head = NULL;

        return;
    }
 
    Node *secondToLast = NULL;

    for (Node *temp = *head; ;temp = temp->next) {
        if (temp->next->next == *head) {
            secondToLast = temp;
            free(temp->next);
            secondToLast->next = *head;

            return;
        }
    }
}

void deleteAtPosition(Node **head, int index) {
    int lengthOfList = 0;

    if (*head == NULL) {
        printf("LIST EMPTY\n");
        return;
    }

    for (Node *temp = *head; temp != NULL; temp = temp->next) {
        if (temp->next == *head) {
            break;
        }

        lengthOfList++;
    }

    if (index > lengthOfList) {
        printf("OUT OF RANGE\n");
        return;
    }

    if ((index == 0) && ((*head)->next == *head)) {
        deleteBeggining(head);
        return;
    } else if ((index == 0) && ((*head)->next != *head)) {
        deleteBeggining(head);
        return;
    } else if (lengthOfList == index) {
        deleteEnd(head);
        return;
    } else {
        int position = 0;
        Node *beforeDeletedNode = NULL;

        for (Node *temp = *head; ; temp = temp->next) {
            if (position == index) {
                beforeDeletedNode->next = temp->next;
                free(temp);
                return;
            }    

            beforeDeletedNode = temp;
            position++;
        }
    }
}

int main(int argc, char *argv[]) {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    Node *head = NULL;

    betterAppend(&head, &data[0], (sizeof(data) / (sizeof(data[0]))));
    printList(head);

    deleteBeggining(&head);

    printList(head);

    deleteBeggining(&head);
    deleteBeggining(&head);
    deleteBeggining(&head);
    deleteBeggining(&head);
    printList(head);

    deleteEnd(&head);
    printList(head);

    deleteAtPosition(&head, 4);
    printList(head);

    freeList(&head);
    printList(head);
}