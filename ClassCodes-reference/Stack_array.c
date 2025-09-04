#include <stdio.h>
#include <stdlib.h>
#define STACK_SIZE 10

void push(int item,int *top,int s[])
{
	if(*top==STACK_SIZE-1)
	{
		printf("Stack is full\n");
		return;
	}
	s[++(*top)]=item;
}

int popStack(int *top,int s[])
{
    if(*top==-1)
	    return -1;
	 return s[(*top)--];    
}

void display(int top,int s[])
{
    int i;
    if(top==-1)
    {
       	printf("\nStack Empty");
	    return;
    }
    for(i=top;i>=0;i--)
	printf("%d\n",s[i]);
}

int main()
{
     int s[10],value,ch,item_deleted;
     int top;
     top=-1;
    
     for(;;)
     {
        printf(" \n1. Push to stack");
        printf(" \n2. Pop from Stack");
        printf(" \n3. Display data of Stack");
        printf(" \n4. Exit\n");
        printf(" \nChoose Option: ");
        scanf("%d",&ch);
          switch(ch)
          {
               case 1:
               {
               printf("\nEnter a value to push into Stack: ");
               scanf("%d",&value);
               push(value, &top, s);
               break;
               }
               case 2:
               {
               item_deleted=popStack(&top,s);
               if(item_deleted==-1)
                    printf("stack empty\n");
                else
                    printf("item deleted =%d", item_deleted);
               break;
               }
               case 3:
               {
               display(top,s);
               break;
               }
                default:
               {
               exit(0); 
               }
            
         }
    }
}