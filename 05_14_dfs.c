#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

int timeCounter;

void DFSVisit(int u, int V, int graph[V][V], int color[], int disc[], int fin[]) {
    color[u] = GRAY;
    disc[u] = ++timeCounter;

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) { // if edge u->v exists
            if (color[v] == WHITE) {
                printf("Tree Edge: %d -> %d\n", u, v);
                DFSVisit(v, V, graph, color, disc, fin);
            }
            else if (color[v] == GRAY) {
                printf("Back Edge: %d -> %d\n", u, v);
            }
            else if (color[v] == BLACK) {
                if (disc[u] < disc[v])
                    printf("Forward Edge: %d -> %d\n", u, v);
                else
                    printf("Cross Edge: %d -> %d\n", u, v);
            }
        }
    }

    color[u] = BLACK;
    fin[u] = ++timeCounter;
}

void DFS(int V, int graph[V][V]) {
    int *color = (int*)malloc(V * sizeof(int));
    int *disc = (int*)malloc(V * sizeof(int));
    int *fin = (int*)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        color[i] = WHITE;
        disc[i] = fin[i] = 0;
    }

    timeCounter = 0;

    for (int u = 0; u < V; u++) {
        if (color[u] == WHITE)
            DFSVisit(u, V, graph, color, disc, fin);
    }

    free(color);
    free(disc);
    free(fin);
}

int main() {
    int V;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    int graph[V][V];
    printf("Enter adjacency matrix (%d x %d):\n", V, V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("\nDFS Edge Classification:\n");
    DFS(V, graph);

    return 0;
}
