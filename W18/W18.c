#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int vertices;           
    int adjMatrix[MAX][MAX]; 
} Graph;


void initGraph(Graph* g, int vertices) {
    g->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            g->adjMatrix[i][j] = 0;
        }
    }
}

void addEdge(Graph* g, int u, int v) {
    g->adjMatrix[u][v] = 1;
    g->adjMatrix[v][u] = 1; 
}

void printGraph(Graph* g) {
    for (int i = 0; i < g->vertices; i++) {
        for (int j = 0; j < g->vertices; j++) {
            printf("%d ", g->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

void BFS(Graph* g, int startVertex) {
    bool visited[MAX] = {false};
    int queue[MAX];
    int front = 0, rear = 0;

    visited[startVertex] = true;
    queue[rear++] = startVertex;

    printf("BFS Traversal: ");
    while (front != rear) {
        int current = queue[front++];
        printf("%d ", current);

        for (int i = 0; i < g->vertices; i++) {
            if (g->adjMatrix[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                queue[rear++] = i;
            }
        }
    }
    printf("\n");
}

void DFSUtil(Graph* g, int vertex, bool visited[]) {
    visited[vertex] = true;
    printf("%d ", vertex);

    for (int i = 0; i < g->vertices; i++) {
        if (g->adjMatrix[vertex][i] == 1 && !visited[i]) {
            DFSUtil(g, i, visited);
        }
    }
}

void DFS(Graph* g, int startVertex) {
    bool visited[MAX] = {false};
    printf("DFS Traversal: ");
    DFSUtil(g, startVertex, visited);
    printf("\n");
}

int main() {
    Graph g;
    int vertices, edges, u, v, startVertex;

    printf("Nhập số đỉnh: ");
    scanf("%d", &vertices);
    initGraph(&g, vertices);

    printf("Nhập số cạnh: ");
    scanf("%d", &edges);
    for (int i = 0; i < edges; i++) {
        printf("Nhập cạnh (u v): ");
        scanf("%d %d", &u, &v);
        addEdge(&g, u, v);
    }

    printf("Ma trận kề của đồ thị:\n");
    printGraph(&g);

    printf("Nhập đỉnh bắt đầu duyệt: ");
    scanf("%d", &startVertex);

    BFS(&g, startVertex);
    DFS(&g, startVertex);

    return 0;
}
