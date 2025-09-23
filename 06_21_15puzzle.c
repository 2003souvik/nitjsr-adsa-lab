#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4   // 4x4 board for 15-puzzle

// Structure for a puzzle state
typedef struct Node {
    int mat[N][N];       // board
    int x, y;            // blank tile coordinates
    int cost;            // heuristic cost
    int level;           // depth level
    struct Node* parent; // parent node
} Node;

// Goal state
int goal[N][N] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}
};

// Directions for moving the blank tile
int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};

// Utility to allocate a new node
Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));

    memcpy(node->mat, mat, sizeof(node->mat));

    // move blank tile
    int temp = node->mat[x][y];
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = temp;

    node->x = newX;
    node->y = newY;
    node->level = level;
    node->parent = parent;
    node->cost = 0;

    return node;
}

// Calculate Manhattan distance heuristic
int calculateCost(int mat[N][N]) {
    int cost = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] && mat[i][j] != goal[i][j]) {
                int val = mat[i][j] - 1;
                int targetX = val / N;
                int targetY = val % N;
                cost += abs(i - targetX) + abs(j - targetY);
            }
        }
    }
    return cost;
}

// Print the board
void printMatrix(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] == 0)
                printf("   ");
            else
                printf("%2d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Priority Queue node (min-heap by cost+level)
typedef struct {
    Node* arr[100000];
    int size;
} MinHeap;

void push(MinHeap* heap, Node* node) {
    heap->arr[heap->size++] = node;
    int i = heap->size - 1;
    while (i && (heap->arr[(i - 1) / 2]->cost + heap->arr[(i - 1) / 2]->level >
                 heap->arr[i]->cost + heap->arr[i]->level)) {
        Node* temp = heap->arr[i];
        heap->arr[i] = heap->arr[(i - 1) / 2];
        heap->arr[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

Node* pop(MinHeap* heap) {
    if (heap->size <= 0) return NULL;
    Node* root = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];
    int i = 0;
    while (1) {
        int smallest = i;
        int l = 2 * i + 1, r = 2 * i + 2;
        if (l < heap->size &&
            (heap->arr[l]->cost + heap->arr[l]->level < heap->arr[smallest]->cost + heap->arr[smallest]->level))
            smallest = l;
        if (r < heap->size &&
            (heap->arr[r]->cost + heap->arr[r]->level < heap->arr[smallest]->cost + heap->arr[smallest]->level))
            smallest = r;
        if (smallest == i) break;
        Node* temp = heap->arr[i];
        heap->arr[i] = heap->arr[smallest];
        heap->arr[smallest] = temp;
        i = smallest;
    }
    return root;
}

// Print path from root to goal
void printPath(Node* root) {
    if (root == NULL) return;
    printPath(root->parent);
    printMatrix(root->mat);
}

// Branch and Bound solver
void solve15Puzzle(int initial[N][N], int x, int y) {
    MinHeap heap = {.size = 0};
    Node* root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = calculateCost(initial);
    push(&heap, root);

    while (heap.size) {
        Node* min = pop(&heap);

        if (min->cost == 0) {
            printf("Solution found!\n\n");
            printPath(min);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int newX = min->x + row[i];
            int newY = min->y + col[i];

            if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
                Node* child = newNode(min->mat, min->x, min->y, newX, newY, min->level + 1, min);
                child->cost = calculateCost(child->mat);
                push(&heap, child);
            }
        }
    }
}

int main() {
    int initial[N][N];
    int x, y;

    printf("Enter the initial 4x4 puzzle configuration (use 0 for blank):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &initial[i][j]);
            if (initial[i][j] == 0) {
                x = i;
                y = j;
            }
        }
    }

    printf("\nSolving the puzzle...\n\n");
    solve15Puzzle(initial, x, y);

    return 0;
}
