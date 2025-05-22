#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode {
    void *binaryTreeNodeAddress;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    size_t length;

    QueueNode *head;
    QueueNode *tail;
} Queue;

typedef struct BinaryTreeNode {
    int data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} BinaryTreeNode;

void enqueue(Queue *queue, void *binaryTreeAddress) {
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));

    if (newNode == NULL) {
        perror("MALLOC");
        return;
    }

    newNode->binaryTreeNodeAddress = binaryTreeAddress;
    newNode->next = NULL;

    if (queue->head == NULL) {
        queue->head = newNode;
        queue->tail = newNode;
        queue->length++;
    } else {
        queue->length++;
        queue->tail->next = newNode;
        queue->tail = queue->tail->next;
    }
}

QueueNode *dequeue(Queue *queque) {
    if (queque->head == NULL) return NULL;

    QueueNode *address = queque->head;

    queque->head = queque->head->next;
    if (queque->head == NULL) {
        queque->tail = NULL;
    }

    queque->length--;
    return address;
}

void freeQueue(Queue *queue) {
    QueueNode *node = NULL;

    while (queue->head != NULL) {
        node = queue->head;
        queue->head = queue->head->next;

        free(node);
    }

    queue->head = NULL;
    queue->tail = NULL;
}

BinaryTreeNode *createBinaryTreeNode(int data) {
    BinaryTreeNode *newNode = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));

    newNode->data  = data;
    newNode->left  = NULL;
    newNode->right = NULL;

    return newNode;
}

void inorderTravle(BinaryTreeNode *root) {
    if (root != NULL) {
        inorderTravle(root->left);
        printf("%d ", root->data);
        inorderTravle(root->right);
    }
}

Queue initQueue() {
    Queue queque;

    queque.length = 0;
    queque.head = NULL;
    queque.tail = NULL;

    return queque;
}

int getMinimumLength(BinaryTreeNode *root) {
    if (root == NULL) return 0;

    Queue queue = initQueue();
    enqueue(&queue, root);

    int depth = 1;

    while (queue.length > 0) {
        int levelSize = queue.length;

        for (int i = 0; i < levelSize; i++) {
            QueueNode *node = dequeue(&queue);
            BinaryTreeNode *current = (BinaryTreeNode *)node->binaryTreeNodeAddress;
            free(node);

            if (current->left == NULL && current->right == NULL) {
                freeQueue(&queue);
                return depth;
            }

            if (current->left != NULL) {
                enqueue(&queue, current->left);
            }

            if (current->right != NULL) {
                enqueue(&queue, current->right);
            }
        }
        depth++;
    }

    return depth;
}

int main(int argc, char const *argv[]) {
    BinaryTreeNode *nodeOne   = createBinaryTreeNode(1);
    BinaryTreeNode *nodeTwo   = createBinaryTreeNode(2);
    BinaryTreeNode *nodeThree = createBinaryTreeNode(3);
    BinaryTreeNode *nodeFour  = createBinaryTreeNode(4);

    nodeOne->left = nodeTwo;
    nodeOne->right = NULL;

    nodeTwo->left = nodeThree;
    nodeTwo->right = nodeFour;

    inorderTravle(nodeOne);
    printf("\n");

    printf("MINIMUM HEIGHT: %d\n", getMinimumLength(nodeOne));

    free(nodeOne);
    free(nodeTwo);
    free(nodeThree);
    free(nodeFour);

    return 0;
}