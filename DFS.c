#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
	int data;
	struct Node* next;
};

struct List {
	struct Node* head;
};

struct Graph {
	int vertices;
	struct List* array;
};

struct Node* createNode(int data) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createGraph(int vertices) {
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->vertices = vertices;
	graph->array = (struct List*)malloc(vertices * sizeof(struct List));

	for (int i = 0; i < vertices; i++) {
		graph->array[i].head = NULL;
	}

	return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
	struct Node* newNode = createNode(dest);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
}

void DFS(struct Graph* graph, int vertex, bool visited[]) {
	visited[vertex] = true;
	printf("%d ", vertex);

	struct Node* currentNode = graph->array[vertex].head;
	while (currentNode) {
		int adjacentVertex = currentNode->data;
		if (!visited[adjacentVertex]) {
			DFS(graph, adjacentVertex, visited);
		}
		currentNode = currentNode->next;
	}
}

void DFSTraversal(struct Graph* graph, int startVertex) {
	bool* visited = (bool*)malloc(graph->vertices * sizeof(bool));
	for (int i = 0; i < graph->vertices; i++) {
		visited[i] = false;
	}

	DFS(graph, startVertex, visited);
	free(visited);
}

int main() {
	int vertices, edges;
	printf("Enter the number of vertices: ");
	scanf("%d", &vertices);

	struct Graph* graph = createGraph(vertices);

	printf("Enter the number of edges: ");
	scanf("%d", &edges);

	printf("Enter the edges (format: source destination):\n");
	for (int i = 0; i < edges; i++) {
		int src, dest;
		scanf("%d %d", &src, &dest);
		addEdge(graph, src, dest);
	}

	int startVertex;
	printf("Enter the starting vertex for DFS traversal: ");
	scanf("%d", &startVertex);

	printf("DFS traversal starting from vertex %d: ", startVertex);
	DFSTraversal(graph, startVertex);

	return 0;
}