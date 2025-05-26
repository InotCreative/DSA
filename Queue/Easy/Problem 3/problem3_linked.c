#include <stdbool.h>
#include "data_structures.h"

bool hasCycleBFS(DynamicArray *graphArray, int startNodeIndex) {
    Queue graphQueue = initQueue();
    bool *isVisited = (bool *)calloc(graphArray->size, sizeof(bool));
    bool *parent = (bool *)calloc(graphArray->size, sizeof(bool));
    bool hasCycle = false;

    graphQueue.enqueue(&graphQueue, graphArray->array[startNodeIndex]);
    isVisited[((GraphNode *)graphArray->array[startNodeIndex])->index] = true;

    while (graphQueue.length > 0) {
        QueueNode *currentQueueNode = (QueueNode *)graphQueue.dequeue(&graphQueue);
        GraphNode *currentGraphNode = (GraphNode *)currentQueueNode->address;

        for (GraphNode *temp = currentGraphNode->next; temp != NULL; temp = temp->next) {
            int neighborIndex = temp->index;

            if (isVisited[temp->index] == false) {
                isVisited[temp->index] = true;
                parent[neighborIndex] = currentGraphNode->index;
                graphQueue.enqueue(&graphQueue, graphArray->array[neighborIndex]);
            } else if (parent[currentGraphNode->index] != neighborIndex) {
                hasCycle = true;
                break;
            }
        }

        free(currentQueueNode);
    }

    graphQueue.freeQueue(&graphQueue);
    return hasCycle;
}

int main(int argc, char const *argv[]) {
    DynamicArray graphArray = initArray();

    newVertex(&graphArray, 0);
    newVertex(&graphArray, 1);
    newVertex(&graphArray, 2);
    newVertex(&graphArray, 3);
    newVertex(&graphArray, 4);

    addEdge(&graphArray, 0, 1);
    addEdge(&graphArray, 0, 2);
    addEdge(&graphArray, 0, 3);

    bool hasCycle = false;
    for (int i = 0; i < graphArray.size; i++) {
        hasCycle = hasCycleBFS(&graphArray, i);

        if (hasCycle == true) {
            printf("CYCLE EXISTS\n");
            break;
        }
    }

    if (hasCycle == false) printf("CYCLE DOESNT EXIT\n");

    graphArray.freeArray(&graphArray);
    return 0;
}
