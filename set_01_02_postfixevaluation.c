#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Operator stack
char stack[MAX];
int top = -1;

void push(char c) {
    if (top >= MAX - 1) {
        printf("Stack overflow\n");
        exit(1);
    }
    stack[++top] = c;
}

char pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

char peek() {
    if (top == -1)
        return '\0';
    return stack[top];
}

// Precedence
int prec(char c) {
    if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// -------- Infix → Postfix --------
void infixToPostfix(char* exp, char postfix[][MAX], int *n) {
    int len = strlen(exp);
    int j = 0;

    for (int i = 0; i < len; i++) {
        char c = exp[i];

        if (isspace(c)) continue;

        if (isdigit(c)) {
            // multi-digit numbers
            char num[MAX];
            int k = 0;
            while (i < len && isdigit(exp[i])) {
                num[k++] = exp[i++];
            }
            num[k] = '\0';
            strcpy(postfix[j++], num);
            i--; // adjust
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (top != -1 && peek() != '(') {
                char op[2] = {pop(), '\0'};
                strcpy(postfix[j++], op);
            }
            pop(); // remove '('
        }
        else { // operator
            while (top != -1 && prec(c) <= prec(peek())) {
                char op[2] = {pop(), '\0'};
                strcpy(postfix[j++], op);
            }
            push(c);
        }
    }

    while (top != -1) {
        char op[2] = {pop(), '\0'};
        strcpy(postfix[j++], op);
    }

    *n = j;
}

// -------- Postfix Evaluation --------
int evaluatePostfix(char postfix[][MAX], int n) {
    int valStack[MAX];
    int topVal = -1;

    for (int i = 0; i < n; i++) {
        if (isdigit(postfix[i][0])) {
            valStack[++topVal] = atoi(postfix[i]);
        } else {
            int b = valStack[topVal--];
            int a = valStack[topVal--];
            int res;
            switch (postfix[i][0]) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
            }
            valStack[++topVal] = res;
        }
    }
    return valStack[topVal];
}

// -------- Main --------
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s \"<expression>\"\n", argv[0]);
        return 1;
    }

    // Join command line args into one expression string
    char expr[MAX*10] = "";
    for (int i = 1; i < argc; i++) {
        strcat(expr, argv[i]);
        strcat(expr, " ");
    }

    char postfix[MAX][MAX];
    int n;

    infixToPostfix(expr, postfix, &n);

    int result = evaluatePostfix(postfix, n);
    printf("%d\n", result);
    
    return 0;
}