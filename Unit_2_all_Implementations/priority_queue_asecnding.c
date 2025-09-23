#include<stdio.h>
#include<stdlib.h>

#define QUEUE_SIZE 1024

typedef struct Queue{
    int data;
    int pty;
}queue;

void insert(queue * q, int * count, int data, int pty){
    int j = (*count) - 1;
    if(*count == QUEUE_SIZE){
        printf("The Queue is Full\n");
        return;
    }
    if(*count == 0){
        q[0].data = data;
        q[0].pty = pty;
        (*count)++;
        return;
    }
    while (j >= 0 && q[j].pty > pty)
    {
        q[j+1] = q[j];
        j--;
    }
    q[j+1].data = data;
    q[j+1].pty = pty;
    (*count)++;
    
}
void display(queue * q, int * count){
    if(*count == 0){
        printf("The Queue is Empty\n");
        return;
    }
    int j = 0;
    while (j < (*count))
    {
        printf("%d ", q[j].data);
        j++;
    }
    printf("\n");
    
}
/*
    Deletion is same as a queue and trivial
*/
int main(void){
    queue q[QUEUE_SIZE];
    int count = 0;
    insert(q, &count, 10, 2);
    insert(q, &count, 20, 3);
    insert(q, &count, 30, 1);
    display(q, &count);
    return 0;
}