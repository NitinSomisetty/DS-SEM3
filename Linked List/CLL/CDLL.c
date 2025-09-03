//! ADD CODES FOR HEAD POINTER IMPLEMENTAITION TOO!!

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
NODE Insert_front(NODE tail, int value)
{
    
}