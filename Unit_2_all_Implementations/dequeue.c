#include<stdio.h>
#include<stdlib.h>

#define QUEUE_SIZE 20
/*DeQueue Array Implementation with Wraparound*/
typedef struct Queue{
    int arr[QUEUE_SIZE];
    int front;
    int rear;
}queue;
int isEmpty(queue * q){
    return(q->rear == -1 && q->front == -1)? 1:0;
}
int isFull(queue * q){
    return ((q->rear + 1) % QUEUE_SIZE == q->front);
}
void insertFront(queue * q, int item){
    if(isEmpty(q)){
        q->rear = q->front = 0;
        q->arr[q->rear] = item;
    }else if(isFull(q)){
        printf("The Queue is Full.\n");
        return;
    }else{
        if(q->front == 0){
            q->front = QUEUE_SIZE - 1;
            q->arr[q->front] = item;
        }else{
            q->front--;
            q->arr[q->front] = item;
        }
    }
}
void insertRear(queue * q, int item){
    if(isEmpty(q)){
        q->rear = q->front = 0;
        q->arr[q->rear] = item;
    }else if(isFull(q)){
        printf("The Queue is Full.\n");
        return;
    }else{
        q->rear = (q->rear + 1) % QUEUE_SIZE;
        q->arr[q->rear] = item;
    }
}
void deleteRear(queue * q){
    if(isEmpty(q)){
        printf("The queue is empty\n");
    }else if(q->front == q->rear){
        q->front = q->rear = -1;
    }else{
        if(q->rear == 0){
            q->rear = QUEUE_SIZE - 1;
        }else{
            q->rear--;
        }
    }
}
void deleteFront(queue * q){
    if(isEmpty(q)){
        printf("The Queue is empty\n");
        return;
    }else if(q->front == q->rear){
        q->rear = q->front = -1;
    }else{
        if(q->front == QUEUE_SIZE - 1){
            q->front = 0;
        }else{
            q->front++;
        }
    }
}
void display(queue *q) {
    if(isEmpty(q)){
        printf("The queue is empty\n");
        return;
    }

    printf("Queue elements: ");
    int i = q->front;
    while(1){
        printf("%d ", q->arr[i]);
        if(i == q->rear) break;           
        i = (i + 1) % QUEUE_SIZE;         
    }
    printf("\n");
}

int main(){
    queue q;
    q.front = q.rear = -1;
    insertRear(&q, 10);
    insertRear(&q, 20);
    insertFront(&q, 5);
    display(&q); // Expected: 5 10 20
    deleteFront(&q);
    display(&q); // Expected: 10 20
    deleteRear(&q);
    display(&q); // Expected: 10

    // Test wrap-around
    insertRear(&q, 30);
    insertRear(&q, 40);
    insertRear(&q, 50); // Queue should be full now
    display(&q); // Expected: 10 30 40 50
    insertRear(&q, 60); 
    insertFront(&q, 0); 
    return 0;
}