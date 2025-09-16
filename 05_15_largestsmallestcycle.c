#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

int graph[MAX][MAX];
int V;
bool visited[MAX];
bool stackFlag[MAX];
int path[MAX];
int pathIndex = 0;

int minCycle = MAX, maxCycle = -1;

// DFS utility
void DFS(int u, int parent, int directed) {
    visited[u] = true;
    stackFlag[u] = true;
    path[pathIndex++] = u;

    for (int v = 0; v < V; v++) {
        if (!graph[u][v]) continue; // no edge

        // Ignore reverse edge in undirected graph
        if (!directed && v == parent) continue;

        if (!visited[v]) {
            DFS(v, u, directed);
        }
        else if (stackFlag[v]) {
            // Found a cycle → extract cycle length
            int cycleLen = 0;
            for (int i = pathIndex - 1; i >= 0; i--) {
                cycleLen++;
                if (path[i] == v) break;
            }
            if (cycleLen > 1) { // valid cycle
                if (cycleLen < minCycle) minCycle = cycleLen;
                if (cycleLen > maxCycle) maxCycle = cycleLen;
            }
        }
    }

    stackFlag[u] = false;
    pathIndex--;
}

// Function to find smallest and largest cycles
void findCycles(int directed) {
    for (int i = 0; i < V; i++) {
        visited[i] = false;
        stackFlag[i] = false;
    }
    minCycle = MAX;
    maxCycle = -1;

    for (int u = 0; u < V; u++) {
        if (!visited[u]) {
            DFS(u, -1, directed);
        }
    }

    if (minCycle == MAX && maxCycle == -1)
        printf("No cycles found in the graph.\n");
    else {
        printf("Smallest cycle length = %d\n", minCycle);
        printf("Largest cycle length = %d\n", maxCycle);
    }
}

int main() {
    int E, directed;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    printf("Is the graph directed? (1 = Yes, 0 = No): ");
    scanf("%d", &directed);

    // Initialize adjacency matrix
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        if (!directed) graph[v][u] = 1;
    }

    findCycles(directed);

    return 0;
}
