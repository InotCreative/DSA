#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct History {
    char *URL;

    struct History *head;
    struct History *tail;
    struct History *next;
    struct History *previous;
} History;

void visit(History **head, char *data) {
    int lengthOfUrl = strlen(data);

    char *allocatedUrl = (char *)malloc((lengthOfUrl + 1) * sizeof(char));
    strcpy(allocatedUrl, data);

    if (allocatedUrl == NULL) {
        printf("ERROR | MALLOC");
        exit(EXIT_FAILURE);
    }
    
    allocatedUrl[lengthOfUrl] = '\0';

    History *newHistory = (History *)malloc(sizeof(History));

    if (newHistory == NULL) {
        printf("ERROR | MALLOC");
        exit(EXIT_FAILURE);
    }

    newHistory->head = NULL;
    newHistory->next = NULL;
    newHistory->previous = NULL;
    newHistory->tail = NULL;
    newHistory->URL = allocatedUrl;

    if (*head == NULL) {
        *head = newHistory;
        (*head)->head = newHistory;
        (*head)->tail = newHistory;

        return;
    }

    for (History *temp = *head; temp != NULL; temp = temp->next) {
        if (temp->next == NULL) {
            temp->next = newHistory;
            newHistory->previous = temp;

            (*head)->tail = newHistory;

            return;
        }
    }
}

void back(History **head, int distance) {
    int index = distance;

    History *temp = (*head)->tail;

    for (int count = 0; count < index; count++) {
        if (temp->previous == NULL) {
            printf("%s\n", temp->URL);
            return;
        }
        
        temp = temp->previous;
    }

    printf("%s\n", temp->URL);

    (*head)->tail = temp;
}

void forward(History **head, int distance) {
    int index = distance;

    History *temp = (*head)->tail;

    for (int count = 0; count < index; count++) {
        if (temp->next == NULL) {
            printf("%s\n", temp->URL);
            return;
        } else {
            temp = temp->next;
        }
    }

    printf("%s\n", temp->URL);
    (*head)->tail = temp;
}

int main(int argc, char const *argv[]) {
    History *head = NULL;

    visit(&head, "gfg.org");
    visit(&head, "google.com");
    visit(&head, "facebook.com");
    visit(&head, "youtube.com");
    back(&head, 1);
    back(&head, 1);
    forward(&head, 1);
    visit(&head, "linkedin.com");

    forward(&head, 2);
    back(&head, 1);
    back(&head, 7);

    return 0;
}
