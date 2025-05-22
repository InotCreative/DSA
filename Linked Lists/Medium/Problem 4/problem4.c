#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define INITAL_CAPACITY 8
#define TEST(ptr,comp,message) {if (ptr == comp) {perror(message); return;}}

typedef struct BinaryTreeNode {
    int data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} BinaryTreeNode;

typedef struct LinkedListNode {
    BinaryTreeNode *binaryTreeNode;
    struct LinkedListNode *next;
} LinkedListNode;

void inorder(BinaryTreeNode* root, LinkedListNode **head) {
    if (root != NULL) {
        LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));

        inorder(root->left, head);
        newNode->binaryTreeNode = root->left;

        if (*head == NULL) *head = newNode;
        inorder(root->right, head);
        newNode->next = root->right;
    }
}

int main(int argc, char const *argv[]) {
    LinkedListNode *head = NULL;

    BinaryTreeNode *nodeOne = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    nodeOne->data = 1;
    nodeOne->right = NULL;
    nodeOne->left = NULL;

    BinaryTreeNode *nodeTwo = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    nodeTwo->data = 2;
    nodeTwo->left = NULL;
    nodeTwo->right = NULL;

    BinaryTreeNode *nodeThree = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    nodeThree->data = 3;
    nodeThree->left = NULL;
    nodeThree->right = NULL;

    nodeOne->left = nodeThree;
    nodeOne->right = nodeTwo;

    inorder(nodeOne, &head);
    printf("\n");

    free(nodeOne);
    free(nodeTwo);
    free(nodeThree);
}
