#include <stdio.h>
#include <stdlib.h>

#define stack_size 5

int top=-1;
int stack[stack_size];

//* TO  PUSH INTO A STACK
void push(int *top, int stack[], int item)  //Same as int *stack as it decays to a pointer
{
    if (*top == stack_size - 1) //comes as its 0 based indexing
    { //check for full list
        printf("Stack Overflow\n");
    }
    *top = *top + 1; //changes top to 0. top=0 is for when theres one element
    stack[*top] = item;
}



//* TO POP FROM A STACK
void pop(int *top, int stack[], int item)
{ //check for empty list
    if(*top==-1)
    {
        printf("Empty stack");
        return;
    }
    printf("Item popped is %d", stack[*top]);
    (*top)--;
    //Decrement the pointer top (because -- has higher precedence than *).
    //Then dereference the old pointer location.
}

//*TO DISPLAY LIST
void display(int*top,int stack[])
{
    if(*top==-1)
    {
        printf("Empty stack");
        return;
    }
    for(int i=*top;i>=0;i--)
    {
        printf("%d",stack[i]);
    }
}
//* TO PEEK TOP ELEMENT 
void peek(int *top, int stack[]) {
    if (*top == -1) 
    {
        printf("Stack is empty\n");
        return;
    }
    printf("Top element is %d\n", stack[*top]);
}
