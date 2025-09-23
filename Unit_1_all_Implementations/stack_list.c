#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct STACK{
    int data;
    struct STACK * next;
}Stack;

//Not Needed for Heap allocated Stack
#define STACK_SIZE 1024

//This is a variable to track the size of the stack. However as it is allocated in the heap,
// It is not a mandatory thing and actually dosent make that much sense.
unsigned short length = 0;

Stack * allocate(){
    Stack * temp = (Stack *)malloc(1 * sizeof(Stack));
    if(!temp){
        printf("Fatal Memory Allocation Error.\nProgram Terminated\n");
        exit(1);
    }
    return temp;

}
void push(Stack ** s, int item){
    if(length == STACK_SIZE){
        //Again chacking for length Dosent make much sense for Heap allocated stack.
        printf("The Stack is Full\n");
        return;
    }
    length++;
    if(!*s){
        (*s) = allocate();
        (*s)->data = item;
        (*s)->next = NULL;
    }else{
        Stack * temp = allocate();
        temp->data = item;
        temp->next = (*s);
        (*s) = temp;
    }
}
int pop(Stack ** s){
    if(!*s){
        printf("The Stack Is Empty\n");
        return -1; 
    }else if(!(*s)->next){
        free((*s));
        (*s) = NULL;
        length--;
    }else{
        Stack * temp = (*s);
        (*s) = (*s)->next;
        free(temp);
        length--;
    }
}
int peek(Stack ** s){
    if(!*s){
        printf("The Stack Is Empty\n");
    }else{
        return (*s)->data;
    }
}

int isEmpty(Stack ** s){
    if(!*s)
        return true;
    else
        return false;
}

int isFull(){
    if(length == STACK_SIZE)
        return true;
    else
        return false;
}

void print_stack(Stack ** s){
    /*NOTE: This is not a valid stack operation. Only to check the elements.
      In A real stack you cannot do this.
    */
    if(*s){
        Stack * temp = (*s);
        while(temp){
            printf("Element: %d\n", temp->data);
            temp = temp->next;
        }
    }else{
        printf("The Stack is Empty\n");
    }
}

int main(){
    Stack * stack = NULL;
    if(isEmpty(&stack)) printf("The Stack Is Empty\n");
    push(&stack, 20);
    push(&stack, 30);
    push(&stack, 40);
    print_stack(&stack);
    printf("=====================================\n");
    printf("Peeking: %d\n", peek(&stack));
    printf("=====================================\n");
    pop(&stack);
    print_stack(&stack);
    printf("=====================================\n");
    pop(&stack);
    pop(&stack);
    pop(&stack);
    printf("=====================================\n");
    printf("isFull: %d", isFull());
}