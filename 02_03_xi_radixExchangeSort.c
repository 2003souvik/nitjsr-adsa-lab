#include <stdio.h>

// Function to get the bit at a given position
int getBit(int num, int bitPos)
{
    return (num >> bitPos) & 1;
}

// Radix Exchange Sort function
void radixExchangeSort(int arr[], int left, int right, int bitPos)
{
    if (left >= right || bitPos < 0)
        return;

    int i = left;
    int j = right;

    while (i <= j)
    {
        while (i <= j && getBit(arr[i], bitPos) == 0)
            i++;
        while (i <= j && getBit(arr[j], bitPos) == 1)
            j--;

        if (i < j)
        {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    radixExchangeSort(arr, left, j, bitPos - 1);
    radixExchangeSort(arr, i, right, bitPos - 1);
}

// Function to find the maximum bit position needed
int getMaxBitPos(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    int bitPos = 0;
    while (max >> bitPos)
        bitPos++;
    return bitPos - 1;
}

// Main function to test the sorting
int main()
{
    int A[50], n;
    printf("Enter no. of terms: ");
    scanf("%d", &n);

    printf("\nEnter array elements: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }

    int maxBit = getMaxBitPos(A, n);
    radixExchangeSort(A, 0, n - 1, maxBit);

    printf("\nArray elements are: ");
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    return 0;
}
