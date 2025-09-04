// C program for array implementation of queue 
#include <stdio.h> 
#include <process.h> 

#define QUEUE_SIZE 5

void enqueue(int item,int *rear,int q[])
{
    if(*rear=QUEUE_SIZE-1)
    {
        printf("queue is full\n");
        return;
    }
    *rear=*rear+1;
    q[*rear]=item;
}

int dequeue(int *front,int *rear,int q[])
{
    if(*front>*rear)
        return -1;
    return q[(*front)++];
}
void display(int front,int rear,int q[])
{
    int i;
    if(front>rear)
        {
            printf("queue is empty\n");
            return;
        }
    for(i=front;i<=rear;i++)
        {
            printf("%d\n",q[i]);
        }
}

void main() 
{ 
	
int ch, item, front,rear,q[10];
front=0;
rear=-1;
for(;;)
  { 
    printf("\n1..Insert");
    printf("\n2..Delete");
    printf("\n3..display");
    printf("\n4..EXIT\n");
    scanf("%d",&ch);
    switch(ch)
    {
       case 1:printf("Enter the value\n");
              scanf("%d",&item);
              enqueue(item,&rear,q);
              break;
       case 2:item=dequeue(&front,&rear,q);
              if(item==-1)
              printf("Queue is empty\n");
              else
              printf("element deleted=%d\n",item);
              break;
       case 3:display(front,rear,q);
              break;
       default:exit(0); 
   }
  }
 }

 
