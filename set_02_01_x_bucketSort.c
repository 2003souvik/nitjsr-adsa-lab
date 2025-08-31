#include <stdio.h>
#include <stdlib.h>

// Node for linked list in each bucket
typedef struct Node
{
    float data;
    struct Node *next;
} Node;

// Function to insert an element into a sorted linked list (for bucket)
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

// Bucket Sort function
void bucketSort(float arr[], int n)
{
    Node **buckets = (Node **)malloc(n * sizeof(Node *));
    for (int i = 0; i < n; i++)
        buckets[i] = NULL;

    for (int i = 0; i < n; i++)
    {
        int bucketIndex = (int)(n * arr[i]);
        buckets[bucketIndex] = insertSorted(buckets[bucketIndex], arr[i]);
    }

    int index = 0;
    for (int i = 0; i < n; i++)
    {
        Node *node = buckets[i];
        while (node != NULL)
        {
            arr[index++] = node->data;
            Node *temp = node;
            node = node->next;
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

    bucketSort(A, n);

    printf("\nArray elements are: ");
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    return 0;
}