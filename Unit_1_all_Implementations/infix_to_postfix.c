#include<stdio.h>
#include<string.h>

#define MAX_SIZE 1024
#define IS_OPERAND(c) \
                (c) != '+' && (c) != '-' && (c) != '*' && \
                (c) != '/' && (c) != '^' && (c) != '(' && (c) != ')'

typedef struct Stack {
    char arr[MAX_SIZE];
    int top;
} Stack;

void push(Stack *s, char item) {
    if((s->top + 1) == MAX_SIZE) {
        printf("Stack Is Full\n");
        return;
    }
    s->top++;
    s->arr[s->top] = item;
}

char pop(Stack *s) {
    if(s->top == -1) {
        return '\0';  // Return null character for empty stack
    }
    char item = s->arr[s->top];
    s->top--;
    return item;
}

char peek(Stack *s) {
    if(s->top == -1) {
        return '\0';  // Return null character for empty stack
    }
    return s->arr[s->top];
}

int get_precedence(char c) {
    switch (c) {
        case '^':
            return 3;
        case '/':
        case '*':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return -1;  // For '(' and other non-operators
    }
}

int main() {
    Stack s;
    s.top = -1;
    
    printf("Enter the expression: \n");
    char user_expression[MAX_SIZE];
    char postfix_expression[MAX_SIZE];
    int count_postfix = 0;
    fgets(user_expression, MAX_SIZE, stdin);
    
    // Remove newline if present
    int len = strlen(user_expression);
    if(len > 0 && user_expression[len-1] == '\n') {
        user_expression[len-1] = '\0';
    }
    
    for(int i = 0; user_expression[i] != '\0'; i++) {
        char current = user_expression[i];
        
        // Skip spaces
        if(current == ' ') {
            continue;
        }
        
        // If it's an operand, add to postfix
        if(IS_OPERAND(current)) {
            postfix_expression[count_postfix++] = current;
        }
        // If it's opening parenthesis, push to stack
        else if(current == '(') {
            push(&s, current);
        }
        // If it's closing parenthesis, pop until opening parenthesis
        else if(current == ')') {
            char temp;
            while((temp = pop(&s)) != '(' && temp != '\0') {
                postfix_expression[count_postfix++] = temp;
            }
        }
        // If it's an operator
        else {
            // Pop operators with higher or equal precedence
            // Exception: for right associative ^ operator, only pop if strictly higher
            while(s.top != -1) {
                char top_char = peek(&s);
                
                // Don't pop '(' 
                if(top_char == '(' || get_precedence(top_char) == -1) {
                    break;
                }
                
                // For right associative ^ operator
                if(current == '^') {
                    if(get_precedence(current) < get_precedence(top_char)) {
                        postfix_expression[count_postfix++] = pop(&s);
                    } else {
                        break;
                    }
                }
                // For left associative operators
                else {
                    if(get_precedence(current) <= get_precedence(top_char)) {
                        postfix_expression[count_postfix++] = pop(&s);
                    } else {
                        break;
                    }
                }
            }
            push(&s, current);
        }
    }
    
    // Pop remaining operators from stack
    while(s.top != -1) {
        char temp = pop(&s);
        if(temp != '(' && temp != '\0') {  // Don't add parentheses to postfix
            postfix_expression[count_postfix++] = temp;
        }
    }
    
    postfix_expression[count_postfix] = '\0';
    printf("The Postfix Notation is: %s\n", postfix_expression);
    
    return 0;
}