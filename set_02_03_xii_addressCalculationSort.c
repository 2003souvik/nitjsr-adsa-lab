#include <stdio.h>
#include <stdlib.h>

// Node for linked list inside each bucket
typedef struct Node
{
    float data;
    struct Node *next;
} Node;

// Insert in sorted order (like insertion sort)
Node *insertSorted(Node *head, float value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (head == NULL || value < head->data)
    {
        newNode->next = head;
        return newNode;
    }

    Node *current = head;
    while (current->next != NULL && current->next->data < value)
        current = current->next;

    newNode->next = current->next;
    current->next = newNode;

    return head;
}

// Address Calculation Sort (Scatter Sort)
void addressCalculationSort(float arr[], int n)
{
    Node **buckets = (Node **)malloc(n * sizeof(Node *));
    for (int i = 0; i < n; i++)
        buckets[i] = NULL;

    for (int i = 0; i < n; i++)
    {
        int index = (int)(arr[i] * n);
        if (index >= n)
            index = n - 1;
        buckets[index] = insertSorted(buckets[index], arr[i]);
    }

    int index = 0;
    for (int i = 0; i < n; i++)
    {
        Node *current = buckets[i];
        while (current != NULL)
        {
            arr[index++] = current->data;
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(buckets);
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

    addressCalculationSort(A, n);

    printf("\nArray elements are: ");
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    return 0;
}
