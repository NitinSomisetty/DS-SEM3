#include <stdio.h>
#include <stdlib.h>

#define stack_size 5
struct Node {
    int data;
    struct Node *link;
};
typedef struct Node* NODE; //pointer to a structure node, all are structure nodes here, so top is NODE type

NODE top=NULL;
//In linked list stacks, top is a pointer to a node, not an integer.
//So you don’t check *top == -1. Instead, check *top == NULL (empty stack).

/*
Why *top in functions?

In array version, top was an integer. If you pass &top, then inside function *top is the actual index.
In SLL version, top is a pointer. If you pass &top, then inside function *top is the actual node pointer.
so this is a pointer to pointer case. to access calues use **

Therefore, *top=NULL is the conditon to check for if list is empty since *top is a pointer
*/




//* TO PUSH INTO STACK (SLL)
void push(NODE *top, int item) {
    NODE temp;
    temp = (NODE)malloc(sizeof(struct Node));   // use struct Node, not struct node
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
//no need to check for full stack since memory is dynamically allocated if LL Used
    temp->data = item;
    temp->link = *top;   // link new node to old top
    *top = temp;         // move top to new node

    printf("%d pushed\n", item);
}


//* TO POP FROM STACK (SLL)
void pop(NODE *top)
{ //check if stack is empty
    if (*top == NULL) 
    {
        printf("Stack Underflow\n");
        return;
    }
    NODE temp=*top; //Memory leak – you update *top to the next node but never free the old node. The removed node should be freed to avoid memory waste.
    printf("deleted thing is %d",temp->data);
    (*top)=(*top)->link;
    free(temp);
}


//*TO DISPLAY STACK USING SLL
void display(NODE *top)
{
    if (*top == NULL) {
        printf("Stack empty\n");
        return;
    }
    NODE temp=*top;
    while(temp!=NULL)
    {
        printf("%d",temp->data);
        temp=temp->link;
    }
}

//*TO PEEK TOP ELEMENT
void peek(NODE *top)
{
    if (*top == NULL) {
        printf("Stack empty\n");
        return;
    }
    printf("top element is %d", (*top)->data); //use brackets to be safe always 
}