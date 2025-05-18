#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *newNode(int data) {
    Node *createdNode = (Node *)malloc(sizeof(Node));

    createdNode->data = data;
    createdNode->next = NULL;

    return createdNode;
}

bool cycleExists(Node *head) {
    Node *fastPtr = NULL;

    for (Node *slowPtr = head; slowPtr != NULL; slowPtr = slowPtr->next) {
        if (slowPtr->next == NULL || slowPtr->next->next == NULL) {
            return false;
        }

        fastPtr = slowPtr->next->next;

        if (slowPtr == fastPtr) {
            return true;
        }
    }

    return false;
}

int main(int argc, char const *argv[]) {
    Node *nodeOne = newNode(1);
    Node *nodeTwo = newNode(3);
    Node *nodeThree = newNode(4);
    Node *nodeFour = NULL;

    nodeOne->next = nodeTwo;
    nodeTwo->next = nodeThree;
    nodeThree->next = nodeTwo;

    (cycleExists(nodeOne)) ? printf("CYCLE EXISTS\n") : printf("CYCLE DOESN'T EXIST");

    free(nodeOne);
    free(nodeTwo);
    free(nodeThree);

    nodeOne = newNode(1);
    nodeTwo = newNode(8);
    nodeThree = newNode(3);
    nodeFour = newNode(4);

    nodeOne->next = nodeTwo;
    nodeTwo->next = nodeThree;
    nodeThree->next = nodeFour;
    nodeFour->next = NULL;

    (cycleExists(nodeOne)) ? printf("CYCLE EXISTS\n") : printf("CYCLE DOESN'T EXIST\n");

    free(nodeOne);
    free(nodeTwo);
    free(nodeThree);
    free(nodeFour);

    return 0;
}
