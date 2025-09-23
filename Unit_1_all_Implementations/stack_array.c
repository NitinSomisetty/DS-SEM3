#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define STACK_SIZE 1024

typedef struct STACK{
    int arr[STACK_SIZE];
    int top;
}Stack;

void push(Stack * s, int item){
    if((s->top + 1) == STACK_SIZE){
        printf("Stack Is Full\n");
        return;
    }
    s->top++;
    s->arr[s->top] = item;

}
int pop(Stack * s){
    if(s->top == -1){
        printf("The Stack Is Empty\n");
        return -1; 
    }
    int item = s->arr[s->top];
    s->top--;
    return item;
}
int peek(Stack * s){
    if(s->top == -1){
        printf("The Stack is Empty\n");
        return -1;
    }
    return s->arr[s->top];
}

int isEmpty(Stack * s){
    return (s->top == -1)? true : false;
}

int isFull(Stack * s){
    return (s->top + 1 == STACK_SIZE)? true : false;
}

void print_stack(Stack * s){
    /*NOTE: This is not a valid stack operation. Only to check the elements.
      In A real stack you cannot do this.
    */
    for(int i = s->top; i >= 0; i--){
        printf("Element %d is %d\n", i + 1, s->arr[i]);
    }
}

int main(){
    Stack stack;
    stack.top = -1;
    if(isEmpty(&stack)) printf("The Stack Is Empty\n");
    push(&stack, 20);
    push(&stack, 30);
    push(&stack, 40);
    print_stack(&stack);
    printf("Peeking: %d\n", peek(&stack));
    pop(&stack);
    print_stack(&stack);
    printf("isFull: %d", isFull(&stack));
}