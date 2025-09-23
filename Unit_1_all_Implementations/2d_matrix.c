#include<stdio.h>
#include<stdlib.h>
typedef struct MATRIX_A
{
    int row;
    int col;
    int ** matrix;
}mat_a;
typedef struct MATRIX_B
{
    int row;
    int col;
    int ** matrix;
}mat_b;
typedef struct MATRIX_C
{
    int row;
    int col;
    int ** matrix;
}mat_c;
void malloc_error(){
    printf("Malloc Failed\n");
    exit(1);
}
void allocate(int *** mat, int row, int col){
    *mat = (int **)malloc(row * sizeof(int *));
    if(!*mat) malloc_error();
    for(int i = 0; i < row; i++){
        *((*mat) + i) = (int *)malloc(col * sizeof(int));
        if(!(*((*mat)+i))) malloc_error();
    }
}
void take_input(int ** mat, int row, int col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            printf("Enter the input for row: %d and column: %d: ", i+1, j+1);
            scanf("%d", (((*mat)+i)+j));

        }
    }
}

void compute_matrix(int **A, int **B, int **C, int rowA, int colA, int colB) {
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colB; j++) {
            C[i][j] = 0; // initialize
            for (int k = 0; k < colA; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


int main(void){
    mat_a ma;
    mat_b mb;
    mat_c mc;
    printf("Enter the no. of rows and columns of Matrix A\n");
    scanf("%d %d", ma.row, ma.col);
    printf("Enter the no. of rows and columns of Matrix B\n");
    scanf("%d %d", mb.row, mb.col);
    if(!(ma.col == mb.row)){
        printf("Invalid Matrix Specification. Matrix Order Incompatible.\n");
    }
    mc.row = ma.row;
    mc.col = mb.col;
    allocate(&ma.matrix, ma.row, ma.col);
    allocate(&mb.matrix, mb.row, mb.col);
    allocate(&mc.matrix, mc.row, mc.col);
    printf("Enter the elements for Matrix A:\n");
    take_input(&ma.matrix, ma.row, ma.col);
    printf("Enter the elements for Matrix B:\n");
    take_input(&mb.matrix, mb.row, mb.col);
    compute_matrix(&ma.matrix, &mb.matrix, &mc.matrix, ma.row, ma.col, mb.row);
    return 0;
}