#include <stdio.h>
#include <ctype.h>

#define MAX 100

// Stack array and top variable
char stack[MAX];
int top = -1;

// Function to push an element onto the stack
void push(char ch) {
    if (top == MAX - 1) {
        printf("Stack overflow.\n");
    } else {
        stack[++top] = ch;
    }
}

// Function to pop an element from the stack
char pop() {
    if (top == -1) {
        return -1; // Indicate an empty stack
    } else {
        return stack[top--];
    }
}

// Function to get the precedence of operators
int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// Function to convert infix to postfix expression
void infixToPostfix(char* infix) {
    char postfix[MAX];
    int i, j = 0;

    for (i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        // If the character is an operand, add it to postfix
        if (isalnum(ch)) {
            postfix[j++] = ch;
        }
        // If the character is '(', push it to the stack
        else if (ch == '(') {
            push(ch);
        }
        // If the character is ')', pop until '(' is found
        else if (ch == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = pop();
            }
            pop(); // Pop the '(' from the stack
        }
        // If an operator is encountered
        else {
            while (top != -1 && precedence(stack[top]) >= precedence(ch)) {
                postfix[j++] = pop();
            }
            push(ch);
        }
    }

    // Pop all remaining operators from the stack
    while (top != -1) {
        postfix[j++] = pop();
    }

    postfix[j] = '\0'; // Null-terminate the postfix expression

    printf("Postfix expression: %s\n", postfix);
}

int main() {
    char infix[MAX];

    // Input: Infix expression
    printf("Enter an infix expression: ");
    fgets(infix, MAX, stdin);

    // Convert infix to postfix
    infixToPostfix(infix);

    return 0;
}
