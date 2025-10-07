#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <time.h>

#define MAX 20
#define INF 999999

int n;
int dist[MAX][MAX];
int dp[1 << MAX][MAX];  // DP table

// Function to find the minimum cost
int tsp(int mask, int pos) {
    if (mask == (1 << n) - 1)
        return dist[pos][0];  // return to start

    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    int ans = INF;
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) {
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city);
            if (newAns < ans)
                ans = newAns;
        }
    }
    return dp[mask][pos] = ans;
}

// Function to initialize distance matrix with random values
void generateGraph(int size) {
    n = size;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = rand() % 50 + 1;  // Random distance between 1 and 50
        }
    }
}

// Measure execution time for each graph size
void measureExecutionTime() {
    int sizes[] = {10, 12, 14, 16, 18}; // realistic test sizes for demo
    printf("\nProblem Size\tExecution Time (seconds)\n");
    printf("-------------\t--------------------------\n");

    for (int s = 0; s < 5; s++) {
        n = sizes[s];
        generateGraph(n);

        // Reset DP table
        for (int i = 0; i < (1 << n); i++)
            for (int j = 0; j < n; j++)
                dp[i][j] = -1;

        clock_t start = clock();
        int ans = tsp(1, 0);
        clock_t end = clock();

        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%d\t\t%.6f\n", n, time_taken);
    }
}

int main() {
    srand(time(0));

    measureExecutionTime();

    printf("\nNote: The DP TSP is computationally expensive, "
           "so for n > 20, it is impractical.\n");

    return 0;
}
