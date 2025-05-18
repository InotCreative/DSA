#include <iostream>
using namespace std;

typedef struct Node {
    int data;
    struct Node *next;
} Node;

class LinkedList {
    Node *head;

public:
    LinkedList() : head(NULL) {}

    void append(int value) {
        Node *newNode = new Node();
        newNode->data = value;
        newNode->next = nullptr;

        if (head == NULL) {
            head = newNode;
            return;
        }

        Node *temp = head;

        for (; temp != nullptr; temp = temp->next) {
            if (temp->next == nullptr) {
                temp->next = newNode;
                return;
            }
        }
    }

    void printLinkedList() {
        for (Node *temp = head; temp != NULL; temp = temp->next) {
            printf("%d->", temp->data);
        }

        printf("NULL\n");
    }

    void betterAppend(int *data, int length) {
        for (int i = 0; i < length; i++) {
            append(data[i]);
        }
    }

    int getLength() {
        int length = 0;

        for (Node *temp = head; temp != NULL; temp = temp->next) {
            length++;
        }

        return length;
    }

    void getMiddle() {
        int middle = getLength() / 2;

        Node *temp = head;

        while (middle != 0) {
            temp = temp->next;
            middle -= 1;
        }

        printf("%d\n", temp->data);
    }

    ~LinkedList() {
        Node *temp = nullptr;

        while (head != NULL) {
            temp = head;
            head = head->next;

            delete temp;
        }
    }

};

int main(int argc, char const *argv[]) {
    int dataOne[] = {1, 2, 3, 4, 5};
    int dataTwo[] = {10, 20, 30, 40, 50, 60};

    LinkedList listOne;
    listOne.betterAppend(&dataOne[0], (sizeof(dataOne) / sizeof(dataOne[0])));
    listOne.printLinkedList();
    listOne.getMiddle();
    
    LinkedList listTwo;
    listTwo.betterAppend(&dataTwo[0], (sizeof(dataTwo) / sizeof(dataTwo[0])));
    listTwo.printLinkedList();
    listTwo.getMiddle();

    return 0;
}
