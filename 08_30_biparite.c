#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a maximum number of vertices for array allocation
#define MAX_VERTICES 100

// Structure for an Adjacency List Node
typedef struct Node {
    int dest;
    struct Node* next;
} Node;

// Structure for the Graph
typedef struct Graph {
    // Array of pointers to Node to represent the adjacency list
    Node* adj[MAX_VERTICES];
    int numVertices;
} Graph;

// --- Helper Functions for Graph Management ---

/**
 * @brief Creates a new adjacency list node.
 * @param dest The destination vertex index.
 * @return A pointer to the newly created Node.
 */
Node* createNode(int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Failed to allocate memory for node");
        exit(EXIT_FAILURE);
    }
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

/**
 * @brief Adds an undirected edge between vertices u and v.
 * @param graph The graph structure.
 * @param u The first vertex index.
 * @param v The second vertex index.
 */
void addEdge(Graph* graph, int u, int v) {
    // Add v to u's list
    Node* newNode = createNode(v);
    newNode->next = graph->adj[u];
    graph->adj[u] = newNode;

    // Add u to v's list (for undirected graph)
    newNode = createNode(u);
    newNode->next = graph->adj[v];
    graph->adj[v] = newNode;
}

// --- Main Bipartite Check Function ---

/**
 * @brief Checks if the graph is bipartite using Breadth-First Search (BFS) and 2-coloring.
 * @param graph The graph structure.
 * @return true if the graph is bipartite, false otherwise.
 */
bool isBipartite(Graph* graph) {
    int V = graph->numVertices;
    
    // 0: Uncolored (default), 1: Color A, 2: Color B
    int color[MAX_VERTICES];
    for (int i = 0; i < V; i++) {
        color[i] = 0;
    }

    // Since the graph might be disconnected, we iterate through all vertices
    for (int start_node = 0; start_node < V; start_node++) {
        
        // Only start BFS if the current component hasn't been colored yet
        if (color[start_node] == 0) {
            
            // --- BFS Implementation (using a simple array as a Queue) ---
            int queue[MAX_VERTICES];
            int front = 0, rear = 0;

            // Start coloring the first node of the component with color 1
            color[start_node] = 1;
            queue[rear++] = start_node;

            while (front != rear) {
                int u = queue[front++];

                // Check all neighbors of u
                Node* current = graph->adj[u];
                while (current != NULL) {
                    int v = current->dest;

                    if (v >= V) { // Safety check for valid vertex index
                        current = current->next;
                        continue;
                    }

                    // If 'v' is uncolored, color it with the opposite color
                    if (color[v] == 0) {
                        // The opposite color is 3 - current color (3 - 1 = 2, 3 - 2 = 1)
                        color[v] = 3 - color[u];
                        queue[rear++] = v;
                    } 
                    // If 'v' has the same color as 'u', then we found an odd-length cycle
                    else if (color[v] == color[u]) {
                        return false; // Not bipartite
                    }

                    current = current->next;
                }
            }
        }
    }

    // If BFS completes without conflict, the graph is bipartite
    return true;
}

// --- Main Program ---

int main() {
    Graph graph = { .numVertices = 0 };
    int n, e; // n vertices, e edges

    printf("Enter the number of vertices (n <= %d): ", MAX_VERTICES);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_VERTICES) {
        printf("Invalid number of vertices.\n");
        return 1;
    }
    graph.numVertices = n;
    
    // Initialize adjacency list pointers to NULL
    for (int i = 0; i < n; i++) {
        graph.adj[i] = NULL;
    }

    printf("Enter the number of edges (e): ");
    if (scanf("%d", &e) != 1 || e < 0) {
        printf("Invalid number of edges.\n");
        return 1;
    }

    printf("Enter the edges (u v, where u and v are 0-indexed vertices from 0 to %d):\n", n - 1);
    
    for (int i = 0; i < e; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2) {
            printf("Failed to read edge %d.\n", i + 1);
            return 1;
        }

        if (u < 0 || u >= n || v < 0 || v >= n) {
            printf("Invalid vertex index (%d or %d). Indices must be between 0 and %d.\n", u, v, n - 1);
            return 1;
        }

        addEdge(&graph, u, v);
    }

    // Perform the bipartite check
    if (isBipartite(&graph)) {
        printf("\nThe graph is a Bipartite Graph.\n");
    } else {
        printf("\nThe graph is NOT a Bipartite Graph (it contains an odd-length cycle).\n");
    }

    // --- Cleanup (Freeing allocated memory for adjacency list) ---
    for (int i = 0; i < n; i++) {
        Node* current = graph.adj[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}