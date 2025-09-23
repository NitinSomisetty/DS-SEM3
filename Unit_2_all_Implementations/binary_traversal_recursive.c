#include <stdio.h>
#include <stdlib.h>
#define STACK_SIZE 1024



typedef struct Node{
    int data;
    struct Node * left;
    struct Node * right;
}node;



node * ALLOC_NODE(void) {
    node * n = (node *)malloc(sizeof(node));
    if (!n) {
        perror("malloc failed");
        exit(1);
    }
    return n;
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
void inorderTraverse(node * root){
    if(root == NULL){
        return;
    }
    inorderTraverse(root->left);
    printf("%d ", root->data);
    inorderTraverse(root->right);
}

void preorderTraverse(node * root){
    if(root == NULL){
        return;
    }
    printf("%d ", root->data);
    preorderTraverse(root->left);
    preorderTraverse(root->right);
}

void postorderTraverse(node * root){
    if(root == NULL){
        return;
    }
    postorderTraverse(root->left);
    postorderTraverse(root->right);
    printf("%d ", root->data);
}

int main(void){
    node * root = createTree();
    printf("Inorder: ");
    inorderTraverse(root);
    printf("\n");

    printf("Preorder: ");
    preorderTraverse(root);
    printf("\n");

    printf("Postorder: ");
    postorderTraverse(root);
    printf("\n");

    return 0;
}