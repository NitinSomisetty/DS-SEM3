#include <stdio.h>
#include <stdlib.h>

struct Term{
    int coeff;
    int exp;
    struct Term * next;
    struct Term * prev;
};
typedef struct Term term;

void create_list(term ** head, int no_terms);

void enter_data(term ** head);

void print_data(term ** head);

void print_data_adv(term **head);

void sort_polynomial(term ** head);

void add_polynomials(term ** poly1, term ** poly2, term ** poly3);

term * allocate_node(void);

int main(void){
    int poly1_no_terms = 0, poly2_no_terms = 0;
    term * poly1 = NULL, * poly2 = NULL, *poly3 = NULL;
    printf("Enter the number of terms for the first Polynomial: \n");
    scanf("%d", &poly1_no_terms);
    create_list(&poly1, poly1_no_terms);

    printf("Enter the number of terms for the second Polynomial: \n");
    scanf("%d", &poly2_no_terms);
    create_list(&poly2, poly2_no_terms);

    printf("Enter the information for terms of the first Polynomial: \n");
    enter_data(&poly1);
    printf("Enter the information for terms of the second Polynomial: \n");
    enter_data(&poly2);

    sort_polynomial(&poly1);
    sort_polynomial(&poly2);

    printf("Adding: \n");
    add_polynomials(&poly1, &poly2, &poly3);
    print_data_adv(&poly3);

    
}

void create_list(term ** head, int no_terms){
    if(!no_terms){
        printf("Invalid Number of terms.\n");
        exit(1);
    }
    (*head) = (term *)malloc(sizeof(term));
    (*head)->prev = NULL;
    term * curr = (*head);
    for(int i = 1; i<no_terms; i++){
        curr->next = (term *)malloc(sizeof(term));
        curr->next->prev = curr;
        curr = curr->next;
    }
    curr->next = NULL;
    return;
}

void enter_data(term ** head){
    term * curr  = (*head);
    int val, exp;
    for(int i = 0;curr != NULL; i++){
        printf("Enter the value and the exponent for the term %d:\n", i+1);
        scanf("%d %d", &val, &exp);
        curr->coeff = val;
        curr->exp = exp;
        curr = curr->next;
    }

}

void print_data(term ** head){
    term * curr  = (*head);
    int val, exp;
    for(int i = 0;curr != NULL; i++){
        printf(" +(%d)X^(%d) ", curr->coeff, curr->exp);
        curr = curr->next;
    }
    printf("\n");
}

void sort_polynomial(term ** head){
    if (head == NULL || *head == NULL) return;
    term *i, *j;
    for (i = *head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->exp < j->exp) {
                int temp_coeff = i->coeff;
                int temp_exp = i->exp;
                i->coeff = j->coeff;
                i->exp = j->exp;
                j->coeff = temp_coeff;
                j->exp = temp_exp;
            }
        }
    }
}

term * allocate_node(void){return ((term *)malloc(sizeof(term)));}



void add_polynomials(term ** poly1, term ** poly2, term ** poly3){
    term *p1 = *poly1, *p2 = *poly2;
    term *p3 = NULL, *current = NULL;
    
    while(p1 != NULL || p2 != NULL) {
        term * newNode = allocate_node();
        newNode->next = NULL;
        newNode->prev = current;
        
        if(p3 == NULL) {
            p3 = newNode;
        } else {
            current->next = newNode;
        }
        current = newNode;
        
        if(p1 == NULL) {
            current->coeff = p2->coeff;
            current->exp = p2->exp;
            p2 = p2->next;
        } else if(p2 == NULL) {
            current->coeff = p1->coeff;
            current->exp = p1->exp;
            p1 = p1->next;
        } else if(p1->exp == p2->exp) {
            current->coeff = p1->coeff + p2->coeff;
            current->exp = p1->exp;
            p1 = p1->next;
            p2 = p2->next;
        } else if(p1->exp > p2->exp) {
            current->coeff = p1->coeff;
            current->exp = p1->exp;
            p1 = p1->next;
        } else {
            current->coeff = p2->coeff;
            current->exp = p2->exp;
            p2 = p2->next;
        }
    }
    *poly3 = p3;
}


//This is just to make the printing nice thats it, adds nothing to the program.
void print_data_adv(term ** head) {
    term *curr = *head;
    int first = 1; // flag for the first term

    while (curr != NULL) {
        int coeff = curr->coeff;
        int exp   = curr->exp;

        // Print sign properly
        if (coeff >= 0 && !first) {
            printf(" + ");
        } else if (coeff < 0) {
            printf(" - ");
            coeff = -coeff; // make coeff positive for printing
        }

        // Handle coefficient printing
        if (exp == 0) {
            printf("%d", coeff); // constant
        } else if (exp == 1) {
            if (coeff == 1)
                printf("x");
            else
                printf("%dx", coeff);
        } else {
            if (coeff == 1)
                printf("x^%d", exp);
            else
                printf("%dx^%d", coeff, exp);
        }

        first = 0;
        curr = curr->next;
    }
    printf("\n");
}
