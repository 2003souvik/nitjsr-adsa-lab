#include <stdio.h>

// Function to find the minimum number of coins using Greedy method
void findMinCoins(int coins[], int n, int amount) {
    int i, count = 0;
    printf("Coins used to make amount %d:\n", amount);

    for (i = 0; i < n; i++) {
        while (amount >= coins[i]) {
            amount -= coins[i];
            printf("%d ", coins[i]);
            count++;
        }
    }

    printf("\nTotal coins used: %d\n", count);
}

int main() {
    int coins[] = {10, 5, 2, 1};   // Coin denominations (sorted in descending order)
    int n = sizeof(coins) / sizeof(coins[0]);
    int amount;

    printf("Enter the amount: ");
    scanf("%d", &amount);

    findMinCoins(coins, n, amount);

    return 0;
}
