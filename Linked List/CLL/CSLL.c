//! ADD CODES FOR HEAD POINTER IMPLEMENTAITION TOO!!

#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node* link;
};
typedef struct node* NODE;

#define MALLOC(ptr, n, type) \
    ptr = (type *)malloc(n*sizeof(type)); \
    if (ptr==NULL) \
    { \
        printf("Memory not allocated"); \
        exit(1); \
    } 

//* TO INSERT AT BEGINNING
NODE Insert_front(NODE tail, int value)
{
    NODE temp;
    MALLOC(temp,1,struct node);
    temp->data=value;
    if(tail==NULL)
    {
        temp->link=temp;
        tail=temp;
        return tail;
    }
    temp->link=tail->link;
    tail->link=temp;
    return tail;
}

//*TO INSERT FROM REAR
NODE Insert_rear(NODE tail, int value)
{
    NODE temp;
    MALLOC(temp,1,struct node);
    temp->data=value;
    if(tail==NULL)
    {
        temp->link=temp;
        tail=temp;
        return tail;
    }
    temp->link=tail->link;
    tail->link=temp;
    tail=temp;
    return tail;
}

//* TO INSERT AT A POSITION
NODE Insert_pos(NODE tail, int value, int pos)
{
    NODE temp;
    MALLOC(temp,1,struct node);
    temp->data=value;
    if(tail==NULL && pos==1)
    {
        temp->link=temp;
        tail=temp;
        return tail;
    }
    if (tail==NULL && pos!=1)
    {
        printf("Invalid");
        free(temp);
        return NULL;
    }
    if(pos==1)
    {
        temp->link=tail->link;
        tail->link=temp;
        return tail; 
    }
    int count=1;
    NODE curr=tail->link;
    while(curr!=tail && count<pos-1)
    {
        curr=curr->link;
        count++;
    }

//cant use conventional logic as we will go back to the first node from tail
    if (curr == tail && count < pos - 1) //if curr is at tail pointer and still the count<pos-1, then do this
    {
        printf("Invalid position\n");
        free(temp);
        return tail;
    }
    temp->link=curr->link;
    curr->link=temp;

    if(curr==tail)//for insertion in the last node, old logic works but just update tail
    {
        tail=temp;
    }

    return tail;
}

/*
-----------------------------------------------------------------------------------------------------
!DELETE OPERATIONS
------------------------------------------------------------------------------------------------------
*/

//*TO DELETE FROM FRONT OF DLL
NODE Delete_front(NODE tail)
{
    if(tail==NULL)
    {
        printf("cant do it, list is empty");
        return NULL;
    }
    NODE cur=tail->link;
    if(tail==cur) //tail->link =tail itself. NEED a seperate one node condition
    {
        free(cur);
        return NULL;
    }
    tail->link=cur->link; //if used for one node conditon we woud have a tangling pointer of tail
    free(cur);
    return tail;
}


//* TO DELETE FROM REAR OF CLL
NODE Delete_rear(NODE tail)
{
    NODE cur=tail->link;

    // Case 1: Empty list
    if(tail == NULL)
    {
        printf("List is empty\n");
        return NULL;
    }

    // Case 2: Only one node
    if(tail->link == tail)
    {
        free(tail);
        return NULL; // list becomes empty
    }

    // Case 3: More than one node

    while(cur->link != tail) // stop at the node before tail
    {
        cur = cur->link;
    }

    cur->link = tail->link; // link last-but-one node to first
    free(tail);             // free old tail
    tail = cur;             // update tail

    return tail;
}

//* TO DELETE AT A POSITION IN CLL
NODE delete_pos(NODE tail, int pos)
{
    NODE cur = tail->link; // first
    NODE prev = tail;
    int count = 1;

    // Case 1: Empty list
    if(tail == NULL)
    {
        printf("List is empty\n");
        return NULL;
    }

    // Case 2: Only one node
    if(tail->link == tail && pos == 1)
    {
        free(tail);
        return NULL;
    }

    // Case 3: Delete at front
    if(pos == 1)
    {
        cur = tail->link;         // first
        tail->link = cur->link;   // skip first
        free(cur);
        return tail;
    }

    // Case 4: Traverse to (pos-1)th node
    while(count < pos && cur != tail)
    {
        prev = cur;
        cur = cur->link;
        count++;
    }

    // Invalid position check
    if(count < pos) //reached the end but still pos greater than count(length of list) then its invalid
    {
        printf("Invalid position\n");
        return tail;
    }

    // Relink and delete
    prev->link = cur->link;
    if(cur == tail) // if deleting tail
        tail = prev;

    free(cur);
    return tail;
}

//* TO DELETE A NODE WITH A GIVEN VALUE IN CLL
NODE delete_value(NODE tail, int key)
{
    NODE cur, prev;

    // Case 1: Empty list
    if(tail == NULL)
    {
        printf("List is empty\n");
        return NULL;
    }

    cur = tail->link; // first node
    prev = tail;

    // Case 2: Only one node
    if(tail->link == tail && tail->data == key)
    {
        free(tail);
        return NULL;
    }

    // Traverse list
    while(cur != tail)
    {     // checks every node except tail

        if(cur->data == key)
        {
            prev->link = cur->link;
            free(cur);
            return tail;
        }
        prev = cur;
        cur = cur->link;
    }

    // Check the tail node separately
    if(cur->data == key)
    {
        prev->link = cur->link;
        free(cur);
        tail = prev; // update if deleting tail
        return tail;
    }

    // Not found
    printf("Value %d not found\n", key);
    return tail;
}

/*
-----------------------------------------------------------------------------------------------------
! OTHER OPERATIONS
------------------------------------------------------------------------------------------------------
*/



//* TO DISPLAY A CLL
NODE display(NODE tail)
{
    if (tail == NULL)
    {
        printf("List is empty\n");
        return NULL;
    }

    NODE cur = tail->link; // start from head
    while (cur!=tail)
    {
        printf("%d ", cur->data);
        cur = cur->link;
    }
    printf("%d ", cur->data);
    return tail;
}
 

/*
! Look through: 

Ordered Insertion
reversing of a dll
concatenation of dll
*/