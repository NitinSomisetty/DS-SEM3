#include<stdio.h>
#include<stdlib.h>

#define QUEUE_SIZE 20

typedef struct Queue{
    int arr[QUEUE_SIZE];
    int front;
    int rear;
}queue;
int isEmpty(queue * q){
    return(q->rear == -1 && q->front == -1)? 1:0;
}
int isFull(queue * q){
    return (q->rear == QUEUE_SIZE - 1 || q->rear < q->front)? 1:0;
}
void enqueue(queue * q, int item){
    if(isFull(q)){
        printf("The Queue is Full\n");
        return;
    }else if(isEmpty(q)){
        q->rear = q->front = 0;
        q->arr[q->rear] = item;
    }else{
        q->rear++;
        q->arr[q->rear] = item;
    }
}
void dequeue(queue * q){
    if(isEmpty(q)){
        printf("The Queue is Empty.\n");
        return;
    }else{
        q->front++;
    }
}
void display(queue * q){
    int temp = q->front;
    if(temp > q->rear){
        printf("The Queue is Empty, nothing to display:\n");
        return;
    }
    while (temp <= q->rear){
        printf("%d ", q->arr[temp]);
        temp++;
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