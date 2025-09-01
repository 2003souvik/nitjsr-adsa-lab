#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100


char opStack[MAX];
int opTop = -1;


int valStack[MAX];
int valTop = -1;


void pushOp(char c) {
    if (opTop >= MAX - 1) {
        printf("Operator Stack Overflow\n");
        exit(1);
    }
    opStack[++opTop] = c;
}
char popOp() {
    if (opTop == -1) return '\0';
    return opStack[opTop--];
}
char peekOp() {
    if (opTop == -1) return '\0';
    return opStack[opTop];
}


void pushVal(int v) {
    if (valTop >= MAX - 1) {
        printf("Value Stack Overflow\n");
        exit(1);
    }
    valStack[++valTop] = v;
}
int popVal() {
    if (valTop == -1) {
        printf("Value Stack Underflow\n");
        exit(1);
    }
    return valStack[valTop--];
}


int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}


int evaluate(char* expr) {
    int i;
    for (i = 0; i < strlen(expr); i++) {
        if (expr[i] == ' ')
            continue;

        else if (expr[i] == '(') {
            pushOp(expr[i]);
        }

        else if (isdigit(expr[i])) {
            int val = 0;
            while (i < strlen(expr) && isdigit(expr[i])) {
                val = (val * 10) + (expr[i] - '0');
                i++;
            }
            pushVal(val);
            i--;
        }

        else if (expr[i] == ')') {
            while (peekOp() != '(') {
                int b = popVal();
                int a = popVal();
                char op = popOp();
                pushVal(applyOp(a, b, op));
            }
            popOp();
        }

        else { 
            while (opTop != -1 && precedence(peekOp()) >= precedence(expr[i])) {
                int b = popVal();
                int a = popVal();
                char op = popOp();
                pushVal(applyOp(a, b, op));
            }
            pushOp(expr[i]);
        }
    }

    while (opTop != -1) {
        int b = popVal();
        int a = popVal();
        char op = popOp();
        pushVal(applyOp(a, b, op));
    }

    return popVal();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s \"expression\"\n", argv[0]);
        return 1;
    }

    int result = evaluate(argv[1]);
    printf("%d\n", result);

    return 0;
}
