#include <stdio.h>

int main() {
    int n, m;
    printf("Enter number of rows: ");
    scanf("%d", &n);
    printf("Enter number of columns: ");
    scanf("%d", &m);

    int matrix[n][m];

    // Initialize with 0
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            matrix[r][c] = 0;
        }
    }

    // Print initial matrix
    printf("\nInitial 2D Array:\n");
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            printf("%d ", matrix[r][c]);
        }
        printf("\n");
    }

    // Take user input
    printf("\nEnter values for the array:\n");
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            printf("Enter value for position (%d,%d): ", r, c);
            scanf("%d", &matrix[r][c]);
        }
    }

    // Print updated matrix
    printf("\nUpdated 2D Array:\n");
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            printf("%d ", matrix[r][c]);
        }
        printf("\n");
    }

    return 0;
}
