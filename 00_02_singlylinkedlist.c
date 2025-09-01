#include <stdio.h>
#include <stdlib.h>

// Node structure
struct ListNode {
    int value;
    struct ListNode* link;
};

struct ListNode* start = NULL;

// Add a new node at the end
void addNode(int num) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->value = num;
    newNode->link = NULL;

    if (start == NULL) {
        start = newNode;
        return;
    }
    struct ListNode* ptr = start;
    while (ptr->link != NULL) {
        ptr = ptr->link;
    }
    ptr->link = newNode;
}

// Remove node by value
void removeNode(int num) {
    if (start == NULL) {
        printf("The list is empty, nothing to remove.\n");
        return;
    }

    if (start->value == num) {
        struct ListNode* temp = start;
        start = start->link;
        free(temp);
        printf("Element %d removed from the list.\n", num);
        return;
    }

    struct ListNode* ptr = start;
    while (ptr->link != NULL && ptr->link->value != num) {
        ptr = ptr->link;
    }

    if (ptr->link != NULL) {
        struct ListNode* del = ptr->link;
        ptr->link = del->link;
        free(del);
        printf("Element %d removed from the list.\n", num);
    } else {
        printf("Element %d not present in the list.\n", num);
    }
}

// Search for a node
void findNode(int num) {
    struct ListNode* ptr = start;
    int position = 0;

    while (ptr != NULL) {
        if (ptr->value == num) {
            printf("Element %d found at index %d.\n", num, position);
            return;
        }
        ptr = ptr->link;
        position++;
    }
    printf("Element %d not found in the list.\n", num);
}

// Display the linked list
void showList() {
    if (start == NULL) {
        printf("The linked list is currently empty.\n");
        return;
    }

    struct ListNode* ptr = start;
    printf("Current Linked List: ");
    while (ptr != NULL) {
        printf("%d -> ", ptr->value);
        ptr = ptr->link;
    }
    printf("NULL\n");
}

int main() {
    int option, data;

    do {
        printf("\n--- Linked List Operations ---\n");
        printf("1. Add Node\n2. Remove Node\n3. Find Node\n4. Show List\n5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter data to add: ");
                scanf("%d", &data);
                addNode(data);
                break;
            case 2:
                printf("Enter data to remove: ");
                scanf("%d", &data);
                removeNode(data);
                break;
            case 3:
                printf("Enter data to search: ");
                scanf("%d", &data);
                findNode(data);
                break;
            case 4:
                showList();
                break;
            case 5:
                printf("Program terminated.\n");
                break;
            default:
                printf("Invalid selection, please try again.\n");
        }
    } while (option != 5);

    return 0;
}
