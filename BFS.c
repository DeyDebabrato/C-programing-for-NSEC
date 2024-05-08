#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct Node {
    int data;
    struct Node* next;
};

struct Queue {
    int front, rear;
    int capacity;
    int* array;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

void enqueue(struct Queue* queue, int item) {
    if (queue->rear == queue->capacity - 1) {
        printf("Queue is full\n");
        return;
    }
    if (queue->front == -1)
        queue->front = 0;
    queue->rear++;
    queue->array[queue->rear] = item;
}

int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    int item = queue->array[queue->front];
    if (queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        queue->front++;
    return item;
}

void addEdge(struct Node* adjList[], int u, int v) {
    struct Node* newNode = createNode(v);
    newNode->next = adjList[u];
    adjList[u] = newNode;
}

void bfs(struct Node* adjList[], int vertices, int startNode, int visited[]) {
    struct Queue* queue = createQueue(vertices);
    visited[startNode] = 1;
    enqueue(queue, startNode);

    while (!isEmpty(queue)) {
        int currentNode = dequeue(queue);
        printf("%d ", currentNode);

        struct Node* temp = adjList[currentNode];
        while (temp != NULL) {
            int neighbor = temp->data;
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                enqueue(queue, neighbor);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int vertices;
    printf("Enter the number of vertices (maximum %d): ", MAX_VERTICES);
    scanf("%d", &vertices);

    if (vertices <= 0 || vertices > MAX_VERTICES) {
        printf("Invalid number of vertices!\n");
        return 1;
    }

    struct Node* adjList[vertices];
    for (int i = 0; i < vertices; ++i)
        adjList[i] = NULL;

    int edges;
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges (format: u v):\n");
    for (int i = 0; i < edges; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u < 0 || u >= vertices || v < 0 || v >= vertices) {
            printf("Invalid edge: %d %d\n", u, v);
            return 1;
        }
        addEdge(adjList, u, v);
    }

    int visited[vertices];
    for (int i = 0; i < vertices; ++i)
        visited[i] = 0;

    printf("Breadth First Traversal starting from vertex 0: ");
    bfs(adjList, vertices, 0, visited);

    return 0;
}
