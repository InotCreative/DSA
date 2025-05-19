#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct LinkedList {
    struct Node *head;
    struct Node *tail;

    void (*append)(struct LinkedList *, int *, int);
    void (*printList)(struct LinkedList *);
    void (*freeList)(struct LinkedList *);
} LinkedList;

void append(LinkedList *list, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("ERROR MALLOC\n");
        return;
    }

    newNode->value = data;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        return;
    }

    for (Node *temp = list->head; temp != NULL; temp = temp->next) {
        if (temp->next == NULL) {
            temp->next = newNode;
            list->tail = newNode;
            return;
        }
    }
}

void betterAppend(LinkedList *list, int *array, int length) {
    for (int i = 0; i < length; i++) {
        append(list, array[i]);
    }
}

void printList(LinkedList *list) {
    for (Node *temp = list->head; temp != NULL; temp = temp->next) {
        printf("%d->", temp->value);
    }

    printf("NULL\n");
}

void freeList(LinkedList *list) {
    Node *temp;

    while (list->head != NULL) {
        temp = list->head;

        list->head = list->head->next;
        free(temp);
    }

    list->head = NULL;
    list->tail = NULL;  // Add this line

}

void initList(LinkedList *list) {
    list->append = betterAppend;
    list->printList = printList;
    list->freeList = freeList;
    list->head = NULL;
    list->tail = NULL;
}

int main(int argc, char const *argv[]) {
    LinkedList list;
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    initList(&list);
    list.append(&list, array, (sizeof(array) / sizeof(array[0])));
    list.printList(&list);
    list.freeList(&list);

    return 0;
}
