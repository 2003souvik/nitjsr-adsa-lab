#include <stdio.h>
#include <stdbool.h>

#define V 4  // Number of vertices in the graph

// Function to print the solution
void printSolution(int color[]) {
    printf("Coloring of vertices:\n");
    for (int i = 0; i < V; i++)
        printf("Vertex %d ---> Color %d\n", i + 1, color[i]);
}

// Function to check if the current color assignment is safe
bool isSafe(int v, bool graph[V][V], int color[], int c) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && color[i] == c)
            return false; // Adjacent vertex has the same color
    }
    return true;
}

// Recursive utility function to solve the graph coloring problem
bool graphColoringUtil(bool graph[V][V], int m, int color[], int v) {
    // Base case: If all vertices are assigned a color, return true
    if (v == V)
        return true;

    // Try assigning different colors to vertex v
    for (int c = 1; c <= m; c++) {
        if (isSafe(v, graph, color, c)) {
            color[v] = c;

            // Recur to assign colors to the rest of the vertices
            if (graphColoringUtil(graph, m, color, v + 1))
                return true;

            // If assigning color c doesn't lead to a solution, backtrack
            color[v] = 0;
        }
    }

    return false; // If no color can be assigned
}

// Main function to solve the m Coloring problem
bool graphColoring(bool graph[V][V], int m) {
    int color[V] = {0}; // Initialize all color values as 0 (unassigned)

    if (!graphColoringUtil(graph, m, color, 0)) {
        printf("No solution exists with %d colors.\n", m);
        return false;
    }

    // Print the solution
    printSolution(color);
    return true;
}

// Driver Code
int main() {
    /* Example Graph (Adjacency Matrix)
       1 -- 2
       |  / |
       | /  |
       3 -- 4
    */
    bool graph[V][V] = {
        {0, 1, 1, 1},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 0}
    };

    int m = 3; // Number of colors

    graphColoring(graph, m);

    return 0;
}
