#include<stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* rlink;
    struct node* llink;
};
typedef struct node* NODE;

#define MALLOC(ptr, n, type) \
    ptr = (type *)malloc(n*sizeof(type)); \
    if (ptr==NULL) \
    { \
        printf("Memory not allocated"); \
        exit(1); \
    } 


/*
------------------------------------------------------------------------------------------------------------------
! INSERT OPERATIONS
------------------------------------------------------------------------------------------------------------------
*/

//* Insert in the front of a DLL
NODE Insert_Front(NODE head, int item)
{
    NODE temp;
    MALLOC(temp, 1, struct node);
    temp->data=item;
    temp->llink=NULL;

    if(head==NULL)
    {
        temp->rlink=NULL;
        head=temp;
        // return head;
    }
    else
    {
        temp->rlink=head;
        head->llink=temp;
        // head=temp;
    }
    return head;    
}

//* Insert at rear of dll
NODE Insert_Rear(NODE head, int item)
{
    NODE temp, cur=head;
    MALLOC(temp, 1, struct node);
    temp->data=item;
    temp->rlink=NULL;

    if(head==NULL)
    {
        temp->llink=NULL;
        head=temp;
        // return head;
    }
    else
    {
        while(cur->rlink!=NULL)
        {
            cur=cur->rlink;
        }
        cur->rlink=temp;
        temp->llink=cur;
        // return head;
    }
    return head;
}


//* Insert at a position of dll

NODE Insert_Pos(NODE head, int item, int pos)
{
    NODE temp, cur=head;
    int count=1;
    MALLOC(temp, 1, struct node);
    temp->data=item;
//! If its invalid free it. always return a pointer 

    if (pos <= 0) {
        printf("Invalid position\n");
        free(temp);
        return head;
    } //case where pos itself is invalid or some negative number



    if(head==NULL && pos==1) //empty and the inserted node will be the first node.
    {
        temp->llink=NULL;
        temp->rlink=NULL;
        head=temp;
        return head;
    }

    if(head==NULL && pos!=1) //not a valid case
    {
        printf("Invalid");
        free(temp);
        return head;
    }
    
    if(pos==1){ //maybe a list exists, but idc, we are inserting at the front. Comes after it checks for head==NULL 2 cases i.e a list already exists and we want to make temp the first node.
        temp->rlink=head;
        head->llink=temp;
        temp->llink=NULL;
        head=temp;
        return head;
    }

    while(cur!=NULL && count<pos-1){
        cur=cur->rlink;
        count++; //to keep track of our position.
    }
    if(cur==NULL){
        printf("Position out of range");
        free(temp);
        return head;
    }
temp->rlink = cur->rlink;     // 1. temp points to old next
if (cur->rlink != NULL)       // 2. fix old next’s llink if not end
    {
        cur->rlink->llink = temp;
    }
temp->llink = cur;            // 3. temp points back to cur
cur->rlink = temp;            // 4. cur points forward to temp
}

/*
-----------------------------------------------------------------------------------------------------
!DELETE OPERATIONS
------------------------------------------------------------------------------------------------------
*/


//* TO delete front of DLL
NODE delete_front(NODE head)
{
    NODE cur=head;

    if (head == NULL)   // empty list
    {
        printf("List is empty\n");
        return NULL;    // return NULL explicitly
    }
    else
    {
        head=head->rlink;
        free(cur); // Free the memory of the old head
        if (head != NULL)        // IF the list is not empty after deletion
        {
            head->llink = NULL;  // Set the new head's llink to NULL
        }
        return head;
    }
}

//* TO DELETE FROM REAR OF A DLL
NODE delete_rear(NODE head)
{
    NODE cur=head;
    if (head == NULL)   // empty list
    {
        printf("List is empty\n");
        return NULL;    // return NULL explicitly
    }

    // only one node
    if (head->rlink == NULL) //need this condition as if we did not use this and did cur->llink->rlink, we would be derefing a null pointer
    {
        free(head);
        return NULL;    // list becomes empty
    }

    else{
        while(cur->rlink!=NULL)
        {
            cur=cur->rlink;
        }
        cur->llink->rlink = NULL;     // unlink the last node

        free(cur);
        return head;
    }
}

//* TO DELETE FROM A GIVEN POSITION IN DLL
NODE delete_pos(NODE head, int pos)
{
    NODE cur, prev;
    int count; //tells which position the prev pointer is at

    if (head == NULL)   // Empty list
    {
        printf("List is empty\n");
        return NULL;
    }

    // Case 1: delete first node
    if (pos == 1)
    {
        cur = head;
        printf("Item deleted is %d\n", cur->data);
        head = head->rlink;
        if (head != NULL)        // more nodes remain
            head->llink = NULL;
        free(cur);
        return head;
    }

    // Case 2: delete at pos > 1
    cur = head->rlink;   // cur is at position 2
    prev = head;         // prev is at position 1
    count = 2;           // count should track cur's position (2)

    while (cur != NULL && count < pos)  // Find the node at position pos
    {
        prev = cur;
        cur = cur->rlink;
        count++;
    }
/*

In contrast, your DLL delete_pos function needs different handling because:

You have bidirectional links
You're tracking position with count=2 (which matches cur's position)
You loop until count < pos (not pos-1)
*/
    if (cur == NULL) // pos out of range
    {
        printf("Invalid position given\n");
        return head;
    }

    prev->rlink=cur->rlink;
    if (cur->rlink != NULL)         // if not last node
        cur->rlink->llink=prev;

    printf("Item deleted is %d\n", cur->data);
    free(cur);

    return head;
}

//* TO DISPLAY CONTENTS OF A DLL
void display(NODE head)
{
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    else
    {
        NODE cur=head;
        while(cur!=NULL){
            printf("%d",cur->data);
            cur=cur->rlink;
        }
    }
}

//*TO DESTROY CONTENTS OF A DLL
NODE destroy (NODE head)
{
    NODE cur=head;
    NODE next;

    while(cur!=NULL)
    {
        next=cur->rlink;
        free(cur);
        cur=next;
    }
    return NULL;
}

//* TO SEARCH FOR ELEMENT
NODE search(NODE head, int key)
{
    NODE cur=head;
    if(head==NULL){
        printf("Empty list");
        return head;
    }    
    else
    {
        while(cur!=NULL && cur->data!=key)
        {
            cur=cur->rlink;
        }
    if(cur == NULL) {
        printf("Key %d not found\n", key);
        return NULL;
    }
    
    printf("Key %d found\n", key);
    return cur;
}
}

//* TO REVERSE A DLL
NODE reverse(NODE head)
{
    NODE current = head;
    NODE temp = NULL;

    // If list is empty or has only one node, nothing to do
    if (head == NULL || head->rlink == NULL)
        return head;

    // Traverse the list and swap links
    while (current != NULL)
    {
        temp = current->llink;          // Save left link
        current->llink = current->rlink; // Swap
        current->rlink = temp;

        current = current->llink;       // Move forward (since links are swapped)
    }

    // At the end, temp points to the old llink of NULL,
    // so temp->llink is the new head (old last node)
    if (temp != NULL)
        head = temp->llink;

    return head;
} //test
