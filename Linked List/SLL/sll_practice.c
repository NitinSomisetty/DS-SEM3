#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* link;
};
typedef struct node * NODE;

#define MALLOC(ptr, n, type) \
    ptr = (type *)malloc(n*sizeof(type)); \
    if (ptr==NULL) \
    { \
        printf("Memory not allocated"); \
        exit(1); \
    } \



NODE InsertFront(NODE head, int item)
{
    NODE temp;
    MALLOC(temp, 1, struct node);
    temp->data=item;

    if(head==NULL)
    {
        head=temp;
        head->link= NULL;
        return head;    
    }

    else
    {
        temp->link=head;
        head=temp;
        return head;
    }
}


NODE Insert_Rear(NODE head, int item)
{
    NODE cur = head;
    NODE temp;
    MALLOC(temp,1,struct node);

    temp->data=item;
    temp->link=NULL;

    if(head==NULL)
    {
        head=temp;
        return head;
    }

    else
    {
        while(cur->link!=NULL)
        {
            cur=cur->link;
        }
        cur->link=temp;
        return head;
    }
    
}

NODE Insert_Pos(NODE head, int item, int pos)
{
    NODE temp;
    NODE cur = head;
    MALLOC(temp,1,struct node);
    temp->data=item;
    temp->link=NULL;

        if (pos <= 0) {
        printf("Invalid position\n");
        return head;
    }



    if(head==NULL && pos==1)
    {
        head=temp;
        return head;
    }

    if (head==NULL && pos!=1)
    {
        printf("WHAT ARE YOU DOING?! THE LIST IS EMPTY");
        free(temp);
        return head;
    }

    if(pos==1)
    {
        temp->link=head;
        head=temp;
        return head;
    }
    //--------------//
    int count =1;
    while(cur!=NULL && count<pos-1)
    {
        cur=cur->link;
        count++;
    }

    if (cur==NULL)
    {
        printf("position is too high, outside the range of list");
        free(temp);
        return head;
    }
    else
    {
        temp->link=cur->link;
        cur->link=temp;
        return head;
    }

}


NODE delete_front(NODE head)
{
    NODE cur = head;

    if (head == NULL)   
    {
        printf("List is empty\n");
        return NULL;   
    }
    else
    {
        head = head->link;    // move head to 2nd node, this case accounts for when only 1 node also. Because head becomes NULL
        printf("Deleted info is %d\n", cur->data);
        free(cur);            // free old head
        return head;          // return updated head
    }
}



NODE delete_rear(NODE head)
{
    if (head == NULL) 
    {
        printf("List is empty\n");
        return NULL;
    }

    if (head->link == NULL) 
    {
        printf("Deleted info is %d\n", head->data);
        free(head);
        return NULL;
    }

    NODE cur = head;
    while (cur->link->link != NULL) 
    {
        cur = cur->link;
    }

    printf("Deleted info is %d\n", cur->link->data);
    free(cur->link);        
    cur->link = NULL;    
    return head;
}


NODE delete_pos(NODE head, int pos)
{
    NODE cur, prev;
    int count=1;
    if(head==NULL){
        printf("Empty list");
    }
    if(pos==1){
        cur=head;
        printf("item deleted is %d",cur->data);
        head=head->link;
        free(cur);
        return head;

    }
    prev=head;
    cur=head->link;
    while(cur!=NULL && count<pos-1)
    {
        prev=cur;
        cur=cur->link;
        count++;
    }
    if(cur==NULL)
    {
        printf("INVALID POSITION GIVEN, out of range");
        return head;
    }
    else
    {
        prev->link=cur->link;
        printf("Deleted is %d",cur->data);
        free(cur);
        return head;
    }
}

NODE to_search(NODE head, int key)
{
    NODE curr=head;
    if(head==NULL)
    {
        printf("Empty list");
        return NULL;
    }

    else
    {
        while(curr!=NULL && curr->data!=key)
        {
            curr=curr->link;
        }
        return curr;
    }
}

void display(NODE head)
{
    NODE curr = head;

    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    printf("Linked List: ");
    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->link;
    }
    printf("NULL\n");
}

NODE destroy (NODE head)
{
    NODE temp, curr=head;
    while(curr!=NULL)
    {
        temp=curr;
        curr=curr->link;
        free(temp);
    }
    return NULL;
}