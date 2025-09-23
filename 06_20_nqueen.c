#include <stdio.h>
#include <stdlib.h>

int N;
int board[20];  // board[i] = column position of queen in row i

// Check if placing a queen at (row, col) is safe
int isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
            return 0; // same column or diagonal clash
    }
    return 1;
}

// Print the board
void printBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i] == j)
                printf(" Q ");
            else
                printf(" . ");
        }
        printf("\n");
    }
    printf("\n");
}

// Backtracking function
void solve(int row) {
    if (row == N) {
        printBoard();
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row] = col;   // place queen
            solve(row + 1);     // solve next row
        }
    }
}

int main() {
    printf("Enter the value of N (size of chessboard): ");
    scanf("%d", &N);

    if (N < 1 || N > 20) {
        printf("Please enter N between 1 and 20.\n");
        return 0;
    }

    printf("\nSolutions for %d-Queens Problem:\n\n", N);
    solve(0);

    return 0;
}
