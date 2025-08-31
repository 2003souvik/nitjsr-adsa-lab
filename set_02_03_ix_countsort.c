#include <stdio.h>


int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

// Normal Counting Sort
void countSort(int arr[], int n) {
    int max = getMax(arr, n);    // Find maximum value
    int count[max + 1];          // Count array
    int output[n];               // Output array

    // Initialize count[] with 0
    for (int i = 0; i <= max; i++)
        count[i] = 0;

    // Count occurrences
    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    // Cumulative count
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];


    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

  
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}


int main() {
    int n;
    printf("Enter no of elements: ");
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        printf("Enter the value arr[%d]: ", i);
        scanf("%d", &arr[i]);
    }

    countSort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}
