#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXDATA 10
#define M 5
#define N 4

typedef struct sparse_matrix{
	int i;
	int j;
	int Data;
	struct sparse_matrix *NextRow;
	struct sparse_matrix *NextCol;
} Cell;

typedef struct matrix{
	struct sparse_matrix *Rows[M];
} M;

M *init_matrix(M *Matrix){

	int k = 0;

	while(k < M){
		Matrix->Rows[k] = NULL;
		++k;
	}
	return Matrix;
}

M *create_matrix(M *Matrix, int NData){

	int Row = -1;
	int Col = -1;
	int k = 0;
	Cell *Aux1 = NULL;

	srand((unsigned)time(NULL));

	while(k < NData){
		Row = (rand() % M);
		Col = (rand() % N);
		Aux1 = Matrix->Rows[i];
		Aux1->i = Row;
		Aux1->j = Col;
		Aux1->Data = (rand() % MAXDATA);
	}
}

int main(void){


	return 0;
}
