#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

char stack[MAX_SIZE];
int top = -1;

// Stack Operations
void push(char c) {
    if (top >= MAX_SIZE - 1) {
        printf("\nStack Overflow");
        return;
    }
    stack[++top] = c;
}

char pop() {
    if (top == -1) {
        printf("\nStack Underflow");
        return -1;
    }
    return stack[top--];
}

char peek() {
    if (top == -1)
        return -1;
    return stack[top];
}

int isEmpty() {
    return top == -1;
}

// Function to return precedence of operators
int precedence(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return -1;
}

// Function to convert infix to postfix
void infixToPostfix(char* infix) {
    int i, j = 0;
    char postfix[MAX_SIZE];
    int len = strlen(infix);

    push('(');
    strcat(infix, ")");

    for (i = 0; infix[i] != '\0'; i++) {
        // If operand, add to output
        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];
        }
        // If left parenthesis, push to stack
        else if (infix[i] == '(') {
            push(infix[i]);
        }
        // If operator
        else if (infix[i] == '+' || infix[i] == '-' || 
                 infix[i] == '*' || infix[i] == '/' || 
                 infix[i] == '^') {
            while (!isEmpty() && precedence(peek()) >= precedence(infix[i])) {
                postfix[j++] = pop();
            }
            push(infix[i]);
        }
        // If right parenthesis
        else if (infix[i] == ')') {
            while (!isEmpty() && peek() != '(') {
                postfix[j++] = pop();
            }
            if (!isEmpty() && peek() == '(') {
                pop();  // Remove '('
            }
        }
    }

    postfix[j] = '\0';
    printf("Postfix expression: %s\n", postfix);
}

int main() {
    char infix[MAX_SIZE];
    printf("Enter infix expression: ");
    scanf("%s", infix);
    infixToPostfix(infix);
    return 0;
}