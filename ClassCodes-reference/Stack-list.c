#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int Data;
    struct Node *link;
};
struct Node *top;

void popStack()
{
    struct Node  *cur=top;
    if(top!=NULL)
    {
        top = top->link;
	printf("to be deleted is %d",cur->Data);
        free(cur);
    }
    else
        printf("\nStack Empty");
}

void push(int value)
{
    struct Node *temp;
    temp=(struct Node *)malloc(sizeof(struct Node));
    temp->Data=value;
    if (top == NULL)
    {
         top=temp;
         top->link=NULL;
    }
    else
    {
        temp->link=top;
        top=temp;
    }
}

void display()
{
     struct Node *cur=top;
     if(cur!=NULL)
     {
          printf("\nElements are as:\n");
          while(cur!=NULL)
          {
               printf("\t%d\n",cur->Data);
               cur=cur->link;
          }
     printf("\n");
     }
     else
     printf("\nStack is Empty");
}

int main()
{
     int i=0;
     top=NULL;
     printf(" \n1. Push to stack");
     printf(" \n2. Pop from Stack");
     printf(" \n3. Display data of Stack");
     printf(" \n4. Exit\n");
     while(1)
     {
          printf(" \nChoose Option: ");
          scanf("%d",&i);
          switch(i)
          {
               case 1:
               {
               int value;
               printf("\nEnter a value to push into Stack: ");
               scanf("%d",&value);
               push(value);
               display();
               break;
               }
               case 2:
               {
               popStack();
               display();
               break;
               }
               case 3:
               {
               display();
               break;
               }
               case 4:
               {
               exit(0);
               }
               default:
               {
               printf("\nwrong choice for operation");
               }
         }
    }
}