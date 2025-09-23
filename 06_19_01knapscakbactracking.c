#include <stdio.h>

int n;              // number of items
int W;              // capacity of knapsack
int weight[50];     // weights
int value[50];      // values

int maxProfit = 0;
int bestSet[50];    // best chosen items
int currentSet[50]; // current chosen items

// Backtracking function
void knapsack(int i, int currentWeight, int currentValue) {
    if (currentWeight > W) return; // invalid branch
    
    if (i == n) {
        // Reached end, check if this solution is better
        if (currentValue > maxProfit) {
            maxProfit = currentValue;
            for (int j = 0; j < n; j++) {
                bestSet[j] = currentSet[j];
            }
        }
        return;
    }

    // Include item i
    currentSet[i] = 1;
    knapsack(i + 1, currentWeight + weight[i], currentValue + value[i]);

    // Exclude item i
    currentSet[i] = 0;
    knapsack(i + 1, currentWeight, currentValue);
}

int main() {
    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    printf("Enter weights of items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &weight[i]);
    }

    printf("Enter values of items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &value[i]);
    }

    // Run backtracking
    knapsack(0, 0, 0);

    // Print result
    printf("\nMaximum Profit = %d\n", maxProfit);
    printf("Items selected: ");
    for (int i = 0; i < n; i++) {
        if (bestSet[i] == 1)
            printf("%d ", i + 1);
    }
    printf("\n");

    return 0;
}
