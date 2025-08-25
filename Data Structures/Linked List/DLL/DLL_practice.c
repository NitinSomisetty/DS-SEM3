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

NODE Insert_Pos(NODE head, int item, int pos)
{
    NODE temp, cur=head;
    int count=1;
    MALLOC(temp, 1, struct node);
    temp->data=item;

    if(pos<=0)
    {
        printf("INvalid");
        free(temp);
        return head;
    }

    if(head==NULL && pos==1)
    {
        temp->rlink=temp->llink=NULL;
        head=temp;
        return head;
    }
    if(head==NULL && pos!=1)
    {
        printf("not possible");
        free(temp);
        return head;
    }
    if (pos==1)
    {
        temp->rlink=head;
        head->llink=temp;
        temp->llink=NULL;
        head=temp;
        return head;
    }
    while(cur!=NULL && count<pos-1)
    {
        cur=cur->rlink;
        count++;
    }
    if(cur==NULL)
    {
        printf("Position asked for is out of range, not possible!");
        free(temp);
        return head;
    }
    temp->rlink=cur->rlink;
    if(cur->rlink!=NULL)
    {
        cur->rlink->llink=temp;
    }
    temp->llink=cur;
    cur->rlink=temp;
}