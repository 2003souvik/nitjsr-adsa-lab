#include<stdio.h>
#include<stdlib.h>
#define SIZE 5
int queue[SIZE];
int rear=-1,front=-1;
int isfull(){
   return (rear+1)%SIZE==front;
}
int isempty()
{
    return front==-1;
}
void enqueue(int val)
{
    if (isfull()){
        printf("Queue is full");
    }
    else{
        if(front==-1)
        {
            front=0;
        }
        rear=(rear+1)%SIZE;
        queue[rear]=val;
    }
}
void dequeue()
{
    if( isempty())
    {
        printf("Queue is empty");
    }
    else
    {
        int x=queue[front];
        printf("The deleted element %d",x);
        if(rear==front)
        {
           rear=front=-1;
        }
        else{
            front=(front+1)%SIZE;
        }
    }

}
void display() {
    if (isempty()) {
        printf("Queue is EMPTY!\n");
    } else {
        printf("Queue elements: ");
        int i = front;
        while (1) {
            printf("%d ", queue[i]);
            if (i == rear)
                break;
            i = (i + 1) % SIZE;
        }
        printf("\n");
    }
}
int main() {
    int choice, value;
    while (1) {
        printf("\n--- Circular Queue Menu ---\n");
        printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}