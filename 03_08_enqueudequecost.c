#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Queue structure
struct Queue {
    int arr[MAX];
    int front, rear;
};

// Initialize queue
void init(struct Queue* q) {
    q->front = q->rear = -1;
}

// Check empty
int isEmpty(struct Queue* q) {
    return (q->front == -1);
}

// Check full
int isFull(struct Queue* q) {
    return (q->rear == MAX - 1);
}

// Enqueue
void enqueue(struct Queue* q, int val) {
    if (isFull(q)) {
        printf("Queue Overflow!\n");
        return;
    }
    if (q->front == -1)
        q->front = 0;
    q->arr[++q->rear] = val;
}

// Dequeue
int dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow!\n");
        return -1;
    }
    int val = q->arr[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return val;
}

/* ------------------ Method 1 (Push costly) ------------------ */
struct Stack1 {
    struct Queue q1, q2;
};

void initS1(struct Stack1* s) {
    init(&s->q1);
    init(&s->q2);
}

void push1(struct Stack1* s, int val) {
    // Step 1: Enqueue new element into q2
    enqueue(&s->q2, val);

    // Step 2: Move all from q1 → q2
    while (!isEmpty(&s->q1))
        enqueue(&s->q2, dequeue(&s->q1));

    // Step 3: Swap q1 and q2
    struct Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;

    printf("Pushed %d\n", val);
}

void pop1(struct Stack1* s) {
    if (isEmpty(&s->q1)) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Popped %d\n", dequeue(&s->q1));
}

/* ------------------ Method 2 (Pop costly) ------------------ */
struct Stack2 {
    struct Queue q1, q2;
};

void initS2(struct Stack2* s) {
    init(&s->q1);
    init(&s->q2);
}

void push2(struct Stack2* s, int val) {
    enqueue(&s->q1, val);
    printf("Pushed %d\n", val);
}

void pop2(struct Stack2* s) {
    if (isEmpty(&s->q1)) {
        printf("Stack is empty!\n");
        return;
    }

    // Move until one element left
    while (s->q1.front != s->q1.rear)
        enqueue(&s->q2, dequeue(&s->q1));

    // Pop last element
    printf("Popped %d\n", dequeue(&s->q1));

    // Swap q1 and q2
    struct Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;
}

/* ------------------ Main ------------------ */
int main() {
    struct Stack1 s1;
    struct Stack2 s2;

    initS1(&s1);
    initS2(&s2);

    printf("=== Method 1 (Push costly) ===\n");
    push1(&s1, 10);
    push1(&s1, 20);
    push1(&s1, 30);
    pop1(&s1);
    pop1(&s1);

    printf("\n=== Method 2 (Pop costly) ===\n");
    push2(&s2, 40);
    push2(&s2, 50);
    push2(&s2, 60);
    pop2(&s2);
    pop2(&s2);

    return 0;
}
