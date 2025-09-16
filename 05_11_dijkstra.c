#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAXV 100   // maximum number of vertices

// Find vertex with minimum distance
int minDistance(int dist[], bool visited[], int V) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Print solution
void printSolution(int dist[], int V) {
    printf("\nVertex \t Distance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

// Dijkstra’s algorithm
void dijkstra(int graph[MAXV][MAXV], int V, int src) {
    int dist[MAXV];
    bool visited[MAXV];

    // Initialize distances
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        if (u == -1) break; // no reachable vertex left
        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printSolution(dist, V);
}

int main() {
    int V, E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);

    int graph[MAXV][MAXV] = {0};

    printf("Enter edges in format: u v w\n");
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;  // remove if directed graph
    }

    int source;
    printf("Enter source vertex: ");
    scanf("%d", &source);

    dijkstra(graph, V, source);

    return 0;
}
