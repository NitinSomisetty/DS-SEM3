#include<stdio.h>

void tower_of_hanoi(int n, char src,char aux,  char dest){
    if(n == 1){
        printf("\nMove Disk %d From %c to %c", n, src, dest);
        return;
    }else{
        tower_of_hanoi(n-1, src, dest, aux);
        printf("\nMove Disk %d from %c to %c", n, src, dest);
        tower_of_hanoi(n-1, aux, src, dest);
    }
    /*Trick to remember for the 3 calls:
    move aux variable cyclically:
    src->aux->dest(header)
    src->dest->aux(1st call)
    aux->src->dest(2nd call)

    */
}

int main(){
    printf("How many Disc's do you have.\n");
    int no_of_discs;
    scanf("%d", &no_of_discs);
    tower_of_hanoi(no_of_discs, 'A', 'B', 'C');
    return 0;
}