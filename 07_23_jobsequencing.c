#include <stdio.h>

#define MAX 20

// Structure for Job
typedef struct {
    char id;       // Job ID (e.g., A, B, C, ...)
    int deadline;  // Deadline (integer)
    int profit;    // Profit for completing the job
} Job;

// Function to sort jobs by profit in descending order
void sortByProfit(Job jobs[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (jobs[j].profit < jobs[j + 1].profit) {
                Job temp = jobs[j];
                jobs[j] = jobs[j + 1];
                jobs[j + 1] = temp;
            }
        }
    }
}

// Function to find the maximum deadline
int findMaxDeadline(Job jobs[], int n) {
    int max = jobs[0].deadline;
    for (int i = 1; i < n; i++) {
        if (jobs[i].deadline > max)
            max = jobs[i].deadline;
    }
    return max;
}

// Function to implement Job Sequencing with Deadline
void jobSequencing(Job jobs[], int n) {
    sortByProfit(jobs, n);  // Sort jobs in descending order of profit

    int maxDeadline = findMaxDeadline(jobs, n);
    int slot[MAX] = {0};   // To track free time slots
    char sequence[MAX];    // To store selected job IDs
    int totalProfit = 0;

    for (int i = 0; i < n; i++) {
        // Try to assign job[i] to the latest available slot before its deadline
        for (int j = jobs[i].deadline; j > 0; j--) {
            if (slot[j] == 0) { // If slot is free
                slot[j] = 1;
                sequence[j] = jobs[i].id;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    // Print the result
    printf("\nJob sequence for maximum profit:\n");
    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i])
            printf("%c ", sequence[i]);
    }

    printf("\nTotal Profit = %d\n", totalProfit);
}

// Driver code
int main() {
    Job jobs[] = {
        {'A', 2, 100},
        {'B', 1, 19},
        {'C', 2, 27},
        {'D', 1, 25},
        {'E', 3, 15}
    };

    int n = sizeof(jobs) / sizeof(jobs[0]);
    jobSequencing(jobs, n);

    return 0;
}
