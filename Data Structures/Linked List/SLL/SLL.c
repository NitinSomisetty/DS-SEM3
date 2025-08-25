#include <stdio.h>
#include <stdlib.h>


struct node
{
    int data;
    struct node *link;   //like int * ptr, Here it points to struct node insteasd of int and link is just like ptr ( a variable/name )
//This does not create a node. It just creates a pointer variable that can point to a struct node.

};
typedef struct node * NODE;

//struct node n1; -> Here n1 is an actual struct node in memory, with space for an int and a struct node*.


//  Type tells the type of element like int or float or struct
#define MALLOC(ptr,n,type) \
    ptr = (type *)malloc(n * sizeof(type)); \
    if(ptr == NULL) { \
        printf("Memory allocation failed\n"); \
        exit(1); \
    }


// *To insert at a front of a Linked List
NODE Insert_Front (NODE head, int item)  //its a function like int main(). Here it returns a pointer to struct node type
{ //take parameters as a head poniter and the item to be inserted.

    NODE temp; //temp is a pointer to struct node.
    MALLOC(temp ,1 ,struct node); //call the macro, MALLOC allocates memory for 1 struct node, assigns it to temp, and checks for NULL.
    temp->data = item;

    if (head==NULL)   //If the list is empty (head == NULL),
    //head is a parameter from the function itself, its head
    {
        head = temp; //make 'head' point to this new node.
        temp->link=NULL; //set its link to NULL
        return head; //return the new head pointer
    }

    else
    {
        temp->link= head; //draw and see
        head=temp;
        return head; //we are returning so that we can use it in int main() like Head = NODE Insert_Front
    }


    /*
    All this if-else could be replaced by:
    temp->link=head;
    return temp
    */
}



//*To insert at rear of a Linked List

NODE Insert_Rear(NODE head, int item) //need a pointer called cur to traverse the list upto last node
{
    NODE cur=head;  // temp → new node, cur → to traverse
    NODE temp;

    MALLOC(temp, 1, struct node);
    temp->data = item;
    temp->link = NULL; //wasnt used before but now anyway need to insert at end where it has to be NULL

    if (head == NULL)   // if list is empty
    {
        head = temp;    // new node becomes the head
        return head;
    }

    else
    {
        // cur = head; already done before

        while (cur->link != NULL)   // move to the last node
        {
            cur = cur->link;
        }
        cur->link = temp;   // attach new node at end
        return head;        // head doesn’t change
    }
}

//*To insert at a given postion
NODE Insert_Pos(NODE head, int item, int pos) //1 based indexing
{
    NODE temp, cur;
    int count = 1; //keeps track of current position while traversing

    MALLOC(temp, 1, struct node);
    temp->data = item;
    temp->link = NULL;

    // 🔹 CHANGE: Added a guard for invalid pos
    if (pos <= 0) {
        printf("Invalid position\n");
        return head;
    }

/*
pos=1 tells us that its first node that is being inserted, nothing is there before this.

For any other position (pos != 1):
We just traverse until the previous node (pos - 1) and link the new node in.
The head doesn’t change.
*/

    // Case 1: empty list + valid pos = 1
    if (head == NULL && pos == 1)
    {
        head = temp;
        return head;
    }

    // Case 2: invalid request → list empty but pos ≠ 1
    if (head == NULL && pos != 1) //list is empty, pos cant be more than 1
    {
        printf("Invalid Position\n");
        free(temp); //FREES TEMP SINCE CANT INSERT ANYWHERE
        return head;   // no change
    }

    // Case 3: insert at beginning (pos = 1) but list not empty i.e head!=NULL
    if (pos == 1)
    {
        temp->link = head;
        head = temp;
        return head;
    }

    // Case 4: insert at middle or end
    cur = head;
    while (cur != NULL && count < pos - 1)
    {
        cur = cur->link;
        count++;
    }
    //we stop cur at the (pos-1)th node, i.e. the node just before the position where the new node (temp) will be inserted.
    if (cur == NULL)   //ran out of nodes before reaching pos-1
    {
        printf("Invalid Position\n");
        free(temp); //! imp
        return head;
    }

    temp->link = cur->link;  // link new node to next node
    cur->link = temp;        // link prev node to new node
    return head;
}

/*
------------------------------------------------------------------------------------------------------------------
! DELETE OPERATIONS
------------------------------------------------------------------------------------------------------------------

*/

//* DELETE IN THE FRONT
NODE delete_front(NODE head)
{
    NODE cur=head;
    if(head==NULL)
    {
        printf("empty list ");
    }
    else
    {
        head=head->link;
        free(cur); 
         
//? free() works in such a way that whatever it points to is freed?
return head;
}
}
/*

cur is a pointer to a node (say node with data = 10).
free(cur) tells the OS:
“The memory block starting at address in cur is no longer needed, please release it back."

Suppose a list is: (cur / head) → [10|*] → [20|*] → [30|NULL]

The pointer to [20|*] (cur->link) was used once to update head.
After that, the whole node [10|*] (including its link field) is destroyed by free().
So cur->link no longer exists — we must never try to access it after freeing.


*/



//* DELETE IN THE REAR
NODE delete_rear(NODE head)
{
    if (head == NULL)  // case 1: empty list
    {
        printf("List is empty\n");
        return NULL;
    }

    if (head->link == NULL) //! imp 
    // case 2: only one node
    {
        printf("Deleted info is %d\n", head->data);
        free(head);
        return NULL; //as nothing exists now
    }

    NODE cur = head;
    while (cur->link->link != NULL) // stop at 2nd last node
    {
        cur = cur->link;
    }

    printf("Deleted info is %d\n", cur->link->data);
    free(cur->link);        // free last node
    cur->link = NULL;       // set 2nd last node → NULL

    return head;
}


//* DELETE AT A GIVEN POSITION
NODE delete_pos(NODE head, int pos)
{
    NODE cur, prev;
    int count = 1;

    if (head == NULL)  // case 1: empty list
    {
        printf("List is empty\n");
        return NULL;
    }

    if (pos == 1)  // case 2: delete first node
    {
        cur = head;
        head = head->link;            // move head forward
        printf("Deleted info is %d\n", cur->data);
        free(cur);                    // free old head
        return head;
    }

    // case 3: delete node at position > 1
    prev = head;
    cur = head->link;
    while (cur != NULL && count < pos-1) // move prev until (pos-1)th
    { //This approach works in SLL because you need prev to point to the node BEFORE the one to delete, so you can reconnect the list.


        prev = cur;
        cur = cur->link;
        count++;
    }

    if (cur == NULL)  // pos is out of range
    {
        printf("Invalid position\n");
        return head;
    }

    // cur is the node to delete
    prev->link = cur->link;   // unlink it
    printf("Deleted info is %d\n", cur->data);
    free(cur);                // free memory

    return head;
}

/*
------------------------------------------------------------------------------------------------------------------
! OTHER OPERATIONS
------------------------------------------------------------------------------------------------------------------
*/

//* TO SEARCH FOR A GIVEN ELEMENT
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
/*
First checks curr != NULL (so you never dereference a null pointer).
Stops either when you reach the end of list OR when the key is found.
*/
        {
            curr=curr->link;
        }
        return curr;
    }
}

//* To Display list
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



//* To destroy all contents of a sll
NODE destroy(NODE head)
{
    NODE curr = head, temp;

    while (curr != NULL) {
        temp = curr;           // store current node
        curr = curr->link;     // move to next
        free(temp);            // free the old one
    }

    printf("List destroyed\n");
    return NULL;   // return NULL since list is now empty
}
