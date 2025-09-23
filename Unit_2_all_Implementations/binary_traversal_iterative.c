#include <stdio.h>
#include <stdlib.h>
#define STACK_SIZE 1024



typedef struct Node{
    int data;
    struct Node * left;
    struct Node * right;
}node;

typedef struct Stack{
    struct Node * arr[STACK_SIZE];
    short top;
}stack;


node * ALLOC_NODE(void) {
    node * n = (node *)malloc(sizeof(node));
    if (!n) {
        perror("malloc failed");
        exit(1);
    }
    return n;
}

void push(stack * s, node * n){
    if(s->top == STACK_SIZE-1){
        printf("Stack is Full.\n");
        exit(1);
    }
    s->top++;
    s->arr[s->top] = n;
}

node * pop(stack * s){
    if(s->top == -1){
        printf("The Stack is empty.\n");
        exit(1);
    }
    node * temp = s->arr[s->top];
    s->top--;
    return temp;
}

int isEmpty(stack * s){
    return ((s->top == -1)? 1 : 0);
}

node * createTree(void){
    node * head = ALLOC_NODE();
    head->data = 10;

    head->left = ALLOC_NODE();
    head->right = ALLOC_NODE();
    head->left->data = 20;
    head->right->data = 30;

    head->left->left = ALLOC_NODE();
    head->left->right = ALLOC_NODE();

    head->left->left->data = 40;
    head->left->left->left = NULL;
    head->left->left->right = NULL;

    head->left->right->data = 50;
    head->left->right->left = NULL;
    head->left->right->right = NULL;

    head->right->right = ALLOC_NODE();
    head->right->left = NULL;
    head->right->right->data = 60;
    head->right->right->left = NULL;
    head->right->right->right = NULL;

    return head;
}
void inorderTraverse(stack * s, node * root){
    node * current = root;
    do{
        while (current != NULL)
        {
            /* Travel down left branches as far as possible saving pointers to
            nodes passed in the stack*/
            push(s, current);
            current = current->left;
        }//At this point, the left subtree is empty
        node * poppedElement = pop(s);
        printf("%d ", poppedElement->data);//visit the node
        current = poppedElement->right;//traverse right subtree
    }while(!isEmpty(s) || current != NULL);
}

void preorderTraverse(stack * s, node * root){
    node * current = root;
    if(current == NULL){
        printf("Root is Null\n");
        return;
    }
    push(s, current);
    while (!isEmpty(s))
    {
        current = pop(s);
        printf("%d ", current->data);
        if(current->right != NULL){
            push(s, current->right); //Push this first so that when popped left is read is first.
        }
        if(current->left != NULL){
            push(s, current->left);
        }
    }
}

void postorderTraverse(node * root){
    node * current;
    stack s1;
    stack s2;
    s1.top = -1;
    s2.top = -1;

    push(&s1, root);
    while(!isEmpty(&s1)){
        current = pop(&s1);
        push(&s2, current);
        if(current->left != NULL)
            push(&s1, current->left);
        if(current->right != NULL)
            push(&s1, current->right);
    }

    while(!isEmpty(&s2)){
        current = pop(&s2);
        printf("%d ", current->data);
    }
}

int main(void){
    node * root = createTree();
    stack s;
    s.top = -1;
    printf("Inorder: ");
    inorderTraverse(&s, root);
    printf("\n");

    printf("Preorder: ");
    preorderTraverse(&s, root);
    printf("\n");

    printf("Postorder: ");
    postorderTraverse(root);
    printf("\n");

    return 0;
}