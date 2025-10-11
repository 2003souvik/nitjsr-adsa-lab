#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX 20  // for reasonable runtime

int graph[MAX][MAX];
int n, e, m;

// Function to check if the vertices in subset form a clique
bool isClique(int subset[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (graph[subset[i]][subset[j]] == 0)
                return false;
        }
    }
    return true;
}

// Generate all subsets of size m using bitmasking
bool containsClique() {
    int total = 1 << n;  // 2^n subsets
    for (int mask = 0; mask < total; mask++) {
        int subset[MAX], size = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i))
                subset[size++] = i;
        }
        if (size == m && isClique(subset, size))
            return true;
    }
    return false;
}

int main() {
    printf("Enter number of vertices (n): ");
    scanf("%d", &n);
    printf("Enter number of edges (e): ");
    scanf("%d", &e);
    printf("Enter clique size (m): ");
    scanf("%d", &m);

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

    if (containsClique())
        printf("Graph contains a clique of size %d.\n", m);
    else
        printf("Graph does NOT contain a clique of size %d.\n", m);

    return 0;
}
