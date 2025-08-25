#include <stdio.h>
#include <stdlib.h>

struct Node {
	//define linked list 
    struct Node* next;
    struct Node* prev;
    int val;
    
};

int* toArray(struct Node* node, int* returnSize) 
{
    while(node->prev!=NULL){
        node=node->prev; //this node reaches until head
    }    
    int count =0;
    struct Node *temp = node;
    while(temp!=NULL){
        count++;
        temp=temp->next;
    }
    int *resarr = (int*)malloc(sizeof(int)*count);
    if (resarr==NULL)
    { 
        printf("Error in allocation");
    }
    else {
     int index=0;
     temp=node;
     while(temp!=NULL)
        {
            resarr[index]=temp-> val;
            index++;
            temp=temp->next;
        }
        *returnSize=count;
        return resarr;
    }
    
} 


//helper and main functions 
struct Node* createNode(int val) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        return NULL;  
    }
    node->val = val;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

struct Node* findNodeWithValue(struct Node* head, int targetVal) {
  	//implement this function
    struct Node* current= head;
    while (current != NULL) {
        if (current->val == targetVal) {
            return current;
        }
        current = current->next;
    }
    return NULL; 
}






int main() {
    int n, targetVal;
    scanf("%d", &n);
    
    int* values = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &values[i]);
    }
    
    scanf("%d", &targetVal);
    
    struct Node* head = createNode(values[0]);
    struct Node* current = head;
    
    for (int i = 1; i < n; i++) {
        struct Node* newNode = createNode(values[i]);
        current->next = newNode;
        newNode->prev = current;
        current = newNode;
    }
    
    struct Node* targetNode = findNodeWithValue(head, targetVal);
    
    if (targetNode == NULL) {
        free(values);
        return 0; // print nothing if not found
    }
    
    int returnSize;
    int* result = toArray(targetNode, &returnSize);
    
    for (int i = 0; i < returnSize; i++) {
        printf("%d", result[i]);
        if (i < returnSize - 1) printf(" ");
    }
    printf("\n");
    
    free(values);
    free(result);
    
    current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
    
    return 0;
}