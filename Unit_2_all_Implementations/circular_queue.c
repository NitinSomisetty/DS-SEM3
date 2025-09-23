#include<stdio.h>
#include<stdlib.h>
/*Circular Queue using Array*/
#define QUEUE_SIZE 16
typedef struct Queue
{
    int arr[QUEUE_SIZE];
    int front;
    int rear;
}queue;
int isEmpty(queue * q){
    return (q->rear == -1 && q->front == -1)? 1:0;
}
int isFull(queue * q){
    return ((q->rear + 1) % QUEUE_SIZE == q->front)? 1:0;
}
void enqueue(queue * q,  int item){
    if(isEmpty(q)){
        q->front = q->rear = 0;
        q->arr[q->rear] = item;
    }else if(isFull(q)){
        printf("The Queue is Full\n");
        return;
    }else{
        q->rear = (q->rear + 1) % QUEUE_SIZE;
        q->arr[q->rear] = item;
    }
}

void dequeue(queue * q){
    if((isEmpty(q))){
        printf("The Queue is Empty.\n");
        return;
    }else if(q->front == q->rear){
        q->front = q->rear = -1;
    }else{
        q->front = (q->front + 1) % QUEUE_SIZE;
    }
}
void display(queue * q){
    if(isEmpty(q)){
        printf("The Queue is Empty.\n");
        return;
    }
    int temp = q->front;
    while(1){
        printf("%d ", q->arr[temp]);
        if(temp == q->rear) break; 
        temp = (temp + 1) % QUEUE_SIZE; 
    }
    printf("\n");
}


int main(){
    queue q;
    q.front = q.rear = -1;
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);
    dequeue(&q);
    display(&q);
    return 0;
}