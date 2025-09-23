#include <stdio.h>
#include <stdlib.h>

#define NODES_TO_ALLOCATE(x) x
#define NODE_BEGIN_INDEX 1

struct NODE
{
    int data;
    struct NODE *nxt_link;
    struct NODE *prev_link;
};
typedef struct NODE node;

node *allocate(int n)
{
    node *item = (node *)malloc(n * sizeof(node));
    if (!item)
    {
        printf("Malloc Failed!\n");
        exit(NODES_TO_ALLOCATE(1));
    }
    return item;
}

void display_list(node **head)
{
    if (!*head)
    {
        printf("The List is empty and uninitialised.\n");
        return;
    }
    node *curr = *head;
    int x = 0;
    do
    {
        printf("The data of Node: %d is %d.\n", ++x, curr->data);
        curr = curr->nxt_link;
    } while (curr != *head);
    printf("The length of the doubly circular list is: %d.\n", x);
}

void insert_from_front(node **head, int item)
{
    node *new_node = allocate(NODES_TO_ALLOCATE(1));
    new_node->data = item;
    
    if (!*head)
    {
        *head = new_node;
        new_node->nxt_link = new_node;
        new_node->prev_link = new_node;
        return;
    }
    
    node *last = (*head)->prev_link;
    
    new_node->nxt_link = *head;
    new_node->prev_link = last;
    (*head)->prev_link = new_node;
    last->nxt_link = new_node;
    *head = new_node;
    return;
}

void insert_at_back(node **head, int item)
{
    node *new_node = allocate(NODES_TO_ALLOCATE(1));
    new_node->data = item;
    
    if (!*head)
    {
        *head = new_node;
        new_node->nxt_link = new_node;
        new_node->prev_link = new_node;
        return;
    }
    
    node *last = (*head)->prev_link;
    
    new_node->nxt_link = *head;
    new_node->prev_link = last;
    last->nxt_link = new_node;
    (*head)->prev_link = new_node;
    return;
}

void insert_at_pos(node **head, int item, int pos)
{
    if (pos < NODE_BEGIN_INDEX)
    {
        printf("Invalid Index number. Position too small to insert.\n");
        return;
    }
    
    if (pos == NODE_BEGIN_INDEX || !*head)
    {
        insert_from_front(head, item);
        return;
    }
    
    node *new_node = allocate(NODES_TO_ALLOCATE(1));
    new_node->data = item;
    
    int count = NODE_BEGIN_INDEX;
    node *curr = *head;
    
    do {
        if (count == pos) break;
        curr = curr->nxt_link;
        count++;
    } while (curr != *head);
    
    if (count != pos)
    {
        printf("The Entered Index is not present in the list.\n");
        free(new_node);
        return;
    }
    
    node *prev = curr->prev_link;
    
    new_node->nxt_link = curr;
    new_node->prev_link = prev;
    prev->nxt_link = new_node;
    curr->prev_link = new_node;
    return;
}

void delete_list(node **head)
{
    if (!*head) return;
    
    node *curr = *head;
    node *next;
    
    // Break the circular connections first
    (*head)->prev_link->nxt_link = NULL;
    (*head)->prev_link = NULL;
    
    // Now delete all nodes
    while (curr)
    {
        next = curr->nxt_link;
        free(curr);
        curr = next;
    }
    *head = NULL;
}

void delete_from_front(node **head)
{
    if (!*head)
    {
        printf("The List Is Empty. Nothing to delete from the front.\n");
        return;
    }
    
    // If only one node
    if ((*head)->nxt_link == *head)
    {
        free(*head);
        *head = NULL;
        return;
    }
    
    node *to_delete = *head;
    node *last = (*head)->prev_link;
    node *second = (*head)->nxt_link;
    
    last->nxt_link = second;
    second->prev_link = last;
    *head = second;
    
    free(to_delete);
    return;
}

void delete_from_back(node **head)
{
    if (!*head)
    {
        printf("List is empty, nothing to delete from back.\n");
        return;
    }
    
    // If only one node
    if ((*head)->nxt_link == *head)
    {
        free(*head);
        *head = NULL;
        return;
    }
    
    node *last = (*head)->prev_link;
    node *second_last = last->prev_link;
    
    second_last->nxt_link = *head;
    (*head)->prev_link = second_last;
    
    free(last);
    return;
}

void delete_from_pos(node **head, int pos)
{
    if (pos < NODE_BEGIN_INDEX)
    {
        printf("Invalid Index number. Position too small to delete.\n");
        return;
    }
    
    if (!*head)
    {
        printf("List is empty, Nothing to delete from the list.\n");
        return;
    }
    
    if (pos == NODE_BEGIN_INDEX)
    {
        delete_from_front(head);
        return;
    }
    
    int count = NODE_BEGIN_INDEX;
    node *curr = *head;
    
    do {
        if (count == pos) break;
        curr = curr->nxt_link;
        count++;
    } while (curr != *head);
    
    if (count != pos)
    {
        printf("The Entered Index is not present in the list to delete.\n");
        return;
    }
    
    node *prev = curr->prev_link;
    node *next = curr->nxt_link;
    
    prev->nxt_link = next;
    next->prev_link = prev;
    
    free(curr);
    return;
}

void find_in_list(node **head, int needle)
{
    int found = 0;
    int *found_index = NULL;
    int len = 0;
    
    if (!*head)
    {
        printf("No List to perform search operation in.\n");
        return;
    }
    
    node *curr = *head;
    int count = 1;
    
    do
    {
        if (needle == curr->data)
        {
            found = 1;
            len++;
            int *temp = (int *)realloc(found_index, len * sizeof(int));
            if (!temp)
            {
                printf("Realloc Error: Not enough memory\n");
                free(found_index);
                return;
            }
            found_index = temp;
            found_index[len - 1] = count;
        }
        curr = curr->nxt_link;
        count++;
    } while (curr != *head);
    
    if (found)
    {
        printf("The Value: %d is found in Index: \n", needle);
        for (int i = 0; i < len; i++)
        {
            printf("Index: `%d`\n", found_index[i]);
        }
        free(found_index);
    }
    else
    {
        printf("Value: `%d` Not Found.\n", needle);
    }
}

void reverse_list(node **head)
{
    if (!*head)
    {
        printf("The List is empty. Nothing to Reverse.\n");
        return;
    }
    
    if ((*head)->nxt_link == *head)
    {
        printf("There is only one element. Nothing to reverse.\n");
        return;
    }
    
    node *curr = *head;
    node *temp;
    
    do
    {
        // Swap next and previous pointers
        temp = curr->nxt_link;
        curr->nxt_link = curr->prev_link;
        curr->prev_link = temp;
        
        // Move to next node (which is now in prev_link due to swap)
        curr = curr->prev_link;
    } while (curr != *head);
    
    // Update head to the new first node
    *head = (*head)->nxt_link;
}

void display_reverse(node **head)
{
    if (!*head)
    {
        printf("The List is empty and uninitialised.\n");
        return;
    }
    
    printf("\nDisplaying list in reverse order:\n");
    node *curr = (*head)->prev_link; // Start from last node
    int x = 0;
    
    do
    {
        printf("The data of Node: %d is %d.\n", ++x, curr->data);
        curr = curr->prev_link;
    } while (curr != (*head)->prev_link);
    printf("The length of the doubly circular list is: %d.\n", x);
}

void chain_diagram(node **head) {
    // ANSI Color codes
    #define RESET   "\033[0m"
    #define RED     "\033[31m"
    #define GREEN   "\033[32m"
    #define YELLOW  "\033[33m"
    #define BLUE    "\033[34m"
    #define MAGENTA "\033[35m"
    #define CYAN    "\033[36m"
    #define WHITE   "\033[37m"
    #define BOLD    "\033[1m"
    
    if (!*head) {
        printf(RED "╔═══════════════════════════════════╗\n");
        printf("║        No Nodes to Display        ║\n");
        printf("╚═══════════════════════════════════╝" RESET "\n");
        return;
    }

    node *curr = *head;
    int count = 1;
    
    printf(BOLD CYAN "\n╔═══════════════ DOUBLY CIRCULAR LINKED LIST ═══════════════╗\n");
    printf("║                                                           ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝" RESET "\n\n");
    
    printf(YELLOW BOLD "                    HEAD\n");
    printf("                     │\n");
    printf("                     ▼" RESET "\n");
    
    node *first = *head;
    do {
        printf(GREEN "      ╔═══════════════════════════════════╗\n");
        printf("      ║" BOLD WHITE "          NODE #%-3d               " RESET GREEN "║\n", count);
        printf("      ╠═══════════════════════════════════╣\n");
        printf("      ║" WHITE " Address:    %-14p      " GREEN "║\n", curr);
        printf("      ║" YELLOW " Data:       %-14d      " GREEN "║\n", curr->data);
        
        if (curr->prev_link == first->prev_link && count > 1) {
            printf("      ║" MAGENTA " Prev:       %-14p (LAST)" GREEN "║\n", curr->prev_link);
        } else if (curr == first) {
            printf("      ║" MAGENTA " Prev:       %-14p (LAST)" GREEN "║\n", curr->prev_link);
        } else {
            printf("      ║" BLUE " Prev:       %-14p      " GREEN "║\n", curr->prev_link);
        }
        
        if (curr->nxt_link == first && count > 1) {
            printf("      ║" MAGENTA " Next:       %-14p (HEAD)" GREEN "║\n", curr->nxt_link);
        } else {
            printf("      ║" BLUE " Next:       %-14p      " GREEN "║\n", curr->nxt_link);
        }
        
        printf("      ╚═══════════════════════════════════╝" RESET "\n");
        
        curr = curr->nxt_link;
        count++;
        
        if (curr != first) {
            printf(MAGENTA "                     │\n");
            printf("                     │ " BOLD "(Forward Link)" RESET MAGENTA "\n");
            printf("                     ▼\n");
            printf("                     ▲\n");
            printf("                     │ " BOLD "(Backward Link)" RESET MAGENTA "\n");
            printf("                     │" RESET "\n");
        } else {
            printf(MAGENTA "                     │\n");
            printf("                     │ " BOLD "(Circular Forward)" RESET MAGENTA "\n");
            printf("                     └─────────┐\n");
            printf("                               │\n");
            printf("         ┌─────────────────────┘\n");
            printf("         │\n");
            printf("         ▲\n");
            printf("         │ " BOLD "(Circular Backward)" RESET MAGENTA "\n");
            printf("         └─────────────────────┐\n");
            printf("                               │\n");
            printf("                     ┌─────────┘\n");
            printf("                     ▼" RESET "\n");
            printf(RED "              ┌────────────┐\n");
            printf("              │" BOLD "   DOUBLY   " RESET RED "│\n");
            printf("              │" BOLD "  CIRCULAR  " RESET RED "│\n");
            printf("              │" BOLD "    LOOP    " RESET RED "│\n");
            printf("              └────────────┘" RESET "\n");
        }
    } while(curr != first);
    
    printf(BOLD CYAN "\n╔═══════════════════════════════════════════════════════════╗\n");
    printf("║                 END OF DOUBLY CIRCULAR LIST               ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝" RESET "\n");
}

int main(void)
{
    node *first = NULL;
    
    printf("Creating a doubly circular linked list...\n\n");
    
    insert_from_front(&first, 20);
    insert_from_front(&first, 10);
    insert_at_back(&first, 30);
    insert_at_back(&first, 40);
    insert_at_pos(&first, 50, 5);
    insert_at_pos(&first, 60, 6);
    insert_at_pos(&first, 70, 7);
    
    printf("Original List (Forward):\n");
    display_list(&first);
    
    display_reverse(&first);
    
    printf("\n");
    chain_diagram(&first);
    
    printf("\nSearching for value 30:\n");
    find_in_list(&first, 30);
    
    printf("\nReversing the list:\n");
    reverse_list(&first);
    display_list(&first);
    
    printf("\nDeleting from front:\n");
    delete_from_front(&first);
    display_list(&first);
    
    printf("\nDeleting from back:\n");
    delete_from_back(&first);
    display_list(&first);
    
    printf("\nDeleting from position 3:\n");
    delete_from_pos(&first, 3);
    display_list(&first);
    
    // Clean up
    delete_list(&first);
    
    return 0;
}