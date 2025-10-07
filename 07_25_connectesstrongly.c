#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// ---------- Graph Structure ----------
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adj[MAX]; // adjacency list
Node* adjT[MAX]; // transpose graph
int V;

// ---------- Stack for DFS ----------
int stack[MAX], top = -1;

void push(int v) { stack[++top] = v; }
int pop() { return stack[top--]; }

// ---------- Utility Function ----------
void addEdge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = adj[u];
    adj[u] = newNode;

    // For transpose (for SCC)
    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = u;
    newNode->next = adjT[v];
    adjT[v] = newNode;
}

// ---------- 1. STRONGLY CONNECTED COMPONENTS (Kosaraju’s) ----------
bool visited[MAX];

void dfs1(int v) {
    visited[v] = true;
    Node* temp = adj[v];
    while (temp) {
        if (!visited[temp->vertex])
            dfs1(temp->vertex);
        temp = temp->next;
    }
    push(v);
}

void dfs2(int v) {
    printf("%d ", v);
    visited[v] = true;
    Node* temp = adjT[v];
    while (temp) {
        if (!visited[temp->vertex])
            dfs2(temp->vertex);
        temp = temp->next;
    }
}

void findSCCs() {
    for (int i = 0; i < V; i++)
        visited[i] = false;

    for (int i = 0; i < V; i++)
        if (!visited[i])
            dfs1(i);

    for (int i = 0; i < V; i++)
        visited[i] = false;

    printf("\nStrongly Connected Components:\n");
    while (top != -1) {
        int v = pop();
        if (!visited[v]) {
            dfs2(v);
            printf("\n");
        }
    }
}

// ---------- 2. ARTICULATION POINTS & BRIDGES (Tarjan’s) ----------
int timeCounter = 0;
int disc[MAX], low[MAX], parent[MAX];
bool ap[MAX]; // articulation points

void dfsAPB(int u, bool adjM[MAX][MAX]) {
    int children = 0;
    visited[u] = true;
    disc[u] = low[u] = ++timeCounter;

    for (int v = 0; v < V; v++) {
        if (adjM[u][v]) {
            if (!visited[v]) {
                children++;
                parent[v] = u;
                dfsAPB(v, adjM);
                low[u] = (low[u] < low[v]) ? low[u] : low[v];

                // Articulation point
                if (parent[u] == -1 && children > 1)
                    ap[u] = true;
                if (parent[u] != -1 && low[v] >= disc[u])
                    ap[u] = true;

                // Bridge
                if (low[v] > disc[u])
                    printf("Bridge: %d - %d\n", u, v);
            }
            else if (v != parent[u])
                low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
        }
    }
}

void findAPandBridges(bool adjM[MAX][MAX]) {
    for (int i = 0; i < V; i++) {
        visited[i] = false;
        parent[i] = -1;
        ap[i] = false;
    }

    printf("\nBridges:\n");
    for (int i = 0; i < V; i++)
        if (!visited[i])
            dfsAPB(i, adjM);

    printf("\nArticulation Points:\n");
    for (int i = 0; i < V; i++)
        if (ap[i])
            printf("%d ", i);
    printf("\n");
}

// ---------- 3. BICONNECTED COMPONENTS (Tarjan’s BCC) ----------
int timeBcc = 0;
int discBcc[MAX], lowBcc[MAX];
int stackEdge[MAX][2];
int topEdge = -1;

void pushEdge(int u, int v) {
    stackEdge[++topEdge][0] = u;
    stackEdge[topEdge][1] = v;
}

void popEdge(int u, int v) {
    while (topEdge >= 0) {
        printf("(%d-%d) ", stackEdge[topEdge][0], stackEdge[topEdge][1]);
        topEdge--;
        if (stackEdge[topEdge + 1][0] == u && stackEdge[topEdge + 1][1] == v)
            break;
    }
    printf("\n");
}

void dfsBCC(int u, bool adjM[MAX][MAX]) {
    visited[u] = true;
    discBcc[u] = lowBcc[u] = ++timeBcc;
    int children = 0;

    for (int v = 0; v < V; v++) {
        if (adjM[u][v]) {
            if (discBcc[v] == -1) {
                children++;
                parent[v] = u;
                pushEdge(u, v);
                dfsBCC(v, adjM);
                lowBcc[u] = (lowBcc[u] < lowBcc[v]) ? lowBcc[u] : lowBcc[v];

                if ((discBcc[u] == 1 && children > 1) || (discBcc[u] > 1 && lowBcc[v] >= discBcc[u])) {
                    printf("Biconnected Component: ");
                    popEdge(u, v);
                }
            }
            else if (v != parent[u] && discBcc[v] < discBcc[u]) {
                lowBcc[u] = (lowBcc[u] < discBcc[v]) ? lowBcc[u] : discBcc[v];
                pushEdge(u, v);
            }
        }
    }
}

void findBCC(bool adjM[MAX][MAX]) {
    for (int i = 0; i < V; i++) {
        discBcc[i] = -1;
        lowBcc[i] = -1;
        parent[i] = -1;
    }

    printf("\nBiconnected Components:\n");
    for (int i = 0; i < V; i++) {
        if (discBcc[i] == -1)
            dfsBCC(i, adjM);
    }
}

// ---------- MAIN ----------
int main() {
    int E, u, v;
    bool adjM[MAX][MAX] = {false};

    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);

    for (int i = 0; i < E; i++) {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        adjM[u][v] = adjM[v][u] = true; // for undirected parts
    }

    findSCCs();             // Strongly Connected Components
    findAPandBridges(adjM); // Articulation Points and Bridges
    findBCC(adjM);          // Biconnected Components

    return 0;
}
