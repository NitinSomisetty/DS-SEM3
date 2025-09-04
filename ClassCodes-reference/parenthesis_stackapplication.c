#include <stdio.h>
#include <stdlib.h>

void push(char, char*, int*);
char pop(char*, int*);
int isempty(int);
int match(char*);

int main() {
    int result;
    char s[100];

    printf("Enter the expression: ");
    scanf("%s", s);

    result = match(s);

    if (result)
        printf("\nMatching succeeded\n");
    else
        printf("\nMatching failed\n");

    return 0;
}

int match(char *s) {
    char stack[100], ch, in;
    int top = -1, i = 0;

    while (s[i] != '\0') {
        ch = s[i];

        switch (ch) {
            case '(':
            case '{':
            case '[':
                push(ch, stack, &top);
                break;

            case ')':
                if (!isempty(top)) {
                    in = pop(stack, &top);
                    if (in != '(') return 0;
                } else return 0;
                break;

            case '}':
                if (!isempty(top)) {
                    in = pop(stack, &top);
                    if (in != '{') return 0;
                } else return 0;
                break;

            case ']':
                if (!isempty(top)) {
                    in = pop(stack, &top);
                    if (in != '[') return 0;
                } else return 0;
                break;
        }
        i++;
    }

    if (isempty(top))
        return 1;  // Balanced
    else
        return 0;  // Not balanced
}

void push(char x, char *stk, int *top) {
    (*top)++;
    stk[*top] = x;
}

char pop(char *stk, int *top) {
    char x = stk[*top];
    (*top)--;
    return x;
}

int isempty(int top) {
    return (top == -1);
}
