#include <stdio.h>
#include <stdbool.h>

#define MAX 20  // Reasonable upper limit for backtracking

int graph[MAX][MAX];
int path[MAX];
int n, e;

// Check if the vertex v can be added to the Hamiltonian path
bool isSafe(int v, int pos) {
    // Check if adjacent
    if (graph[path[pos - 1]][v] == 0)
        return false;

    // Check if already included
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

// Recursive function to solve the Hamiltonian cycle problem
bool hamiltonianUtil(int pos) {
    // Base case: if all vertices are included in path
    if (pos == n) {
        // And if there is an edge from the last to first vertex
        if (graph[path[pos - 1]][path[0]] == 1)
            return true;
        else
            return false;
    }

    // Try different vertices as the next candidate
    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;

            // Recurse to construct the rest of the path
            if (hamiltonianUtil(pos + 1))
                return true;

            // Backtrack
            path[pos] = -1;
        }
    }
    return false;
}

// Main Hamiltonian cycle check
bool hamiltonianCycle() {
    // Initialize path
    for (int i = 0; i < n; i++)
        path[i] = -1;

    path[0] = 0; // Start from vertex 0

    if (hamiltonianUtil(1)) {
        printf("Hamiltonian Cycle exists: ");
        for (int i = 0; i < n; i++)
            printf("%d ", path[i]);
        printf("%d\n", path[0]);
        return true;
    } else {
        printf("No Hamiltonian Cycle exists.\n");
        return false;
    }
}

int main() {
    printf("Enter number of vertices (n): ");
    scanf("%d", &n);
    printf("Enter number of edges (e): ");
    scanf("%d", &e);

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter %d edges (u v):\n", e);
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }

    hamiltonianCycle();

    return 0;
}
