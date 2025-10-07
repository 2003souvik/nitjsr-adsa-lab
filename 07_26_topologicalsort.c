#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// -------- Graph Representation (Adjacency List) --------
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adj[MAX]; // adjacency list
int V;

// -------- Stack for Topological Sort --------
int stack[MAX], top = -1;

void push(int v) {
    stack[++top] = v;
}

// -------- Add Edge --------
void addEdge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = adj[u];
    adj[u] = newNode;
}

// -------- DFS Utility Function --------
void dfs(int v, int visited[]) {
    visited[v] = 1;

    Node* temp = adj[v];
    while (temp) {
        if (!visited[temp->vertex])
            dfs(temp->vertex, visited);
        temp = temp->next;
    }

    // push current vertex to stack after visiting its neighbors
    push(v);
}

// -------- Function to Perform Topological Sort --------
void topologicalSort() {
    int visited[MAX] = {0};

    for (int i = 0; i < V; i++) {
        if (!visited[i])
            dfs(i, visited);
    }

    printf("\nTopological Sort Order: ");
    while (top != -1)
        printf("%d ", stack[top--]);
    printf("\n");
}

// -------- Main Function --------
int main() {
    int E, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);

    for (int i = 0; i < E; i++) {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    topologicalSort();

    return 0;
}
