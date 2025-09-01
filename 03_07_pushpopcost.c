#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Stack structure
struct Stack {
    int arr[MAX];
    int top;
};

// Initialize stack
void init(struct Stack* s) {
    s->top = -1;
}

// Check empty
int isEmpty(struct Stack* s) {
    return (s->top == -1);
}

// Check full
int isFull(struct Stack* s) {
    return (s->top == MAX - 1);
}

// Push into stack
void push(struct Stack* s, int val) {
    if (isFull(s)) {
        printf("Stack Overflow!\n");
        return;
    }
    s->arr[++s->top] = val;
}

// Pop from stack
int pop(struct Stack* s) {
    if (isEmpty(s)) {
        printf("Stack Underflow!\n");
        return -1;
    }
    return s->arr[s->top--];
}

// Peek stack top
int peek(struct Stack* s) {
    return (isEmpty(s)) ? -1 : s->arr[s->top];
}

/* ------------------ Method 1 (Push costly) ------------------ */
struct Queue1 {
    struct Stack s1, s2;
};

void initQ1(struct Queue1* q) {
    init(&q->s1);
    init(&q->s2);
}

void enqueue1(struct Queue1* q, int val) {
    // Move all elements from s1 to s2
    while (!isEmpty(&q->s1))
        push(&q->s2, pop(&q->s1));

    // Push new element to s1
    push(&q->s1, val);

    // Move back all elements
    while (!isEmpty(&q->s2))
        push(&q->s1, pop(&q->s2));

    printf("Enqueued %d\n", val);
}

void dequeue1(struct Queue1* q) {
    if (isEmpty(&q->s1)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Dequeued %d\n", pop(&q->s1));
}

/* ------------------ Method 2 (Pop costly) ------------------ */
struct Queue2 {
    struct Stack s1, s2;
};

void initQ2(struct Queue2* q) {
    init(&q->s1);
    init(&q->s2);
}

void enqueue2(struct Queue2* q, int val) {
    push(&q->s1, val);
    printf("Enqueued %d\n", val);
}

void dequeue2(struct Queue2* q) {
    if (isEmpty(&q->s1) && isEmpty(&q->s2)) {
        printf("Queue is empty!\n");
        return;
    }

    if (isEmpty(&q->s2)) {
        while (!isEmpty(&q->s1))
            push(&q->s2, pop(&q->s1));
    }
    printf("Dequeued %d\n", pop(&q->s2));
}

/* ------------------ Main ------------------ */
int main() {
    struct Queue1 q1;
    struct Queue2 q2;

    initQ1(&q1);
    initQ2(&q2);

    printf("=== Method 1 (Push costly) ===\n");
    enqueue1(&q1, 10);
    enqueue1(&q1, 20);
    enqueue1(&q1, 30);
    dequeue1(&q1);
    dequeue1(&q1);

    printf("\n=== Method 2 (Pop costly) ===\n");
    enqueue2(&q2, 40);
    enqueue2(&q2, 50);
    enqueue2(&q2, 60);
    dequeue2(&q2);
    dequeue2(&q2);

    return 0;
}
