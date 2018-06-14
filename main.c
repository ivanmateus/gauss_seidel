//-------Including libraries-------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "cell.h"

int main(int argc, char *argv[]){

	if(argc == 1){
		M *Matrix = NULL;
		Matrix = init_matrix(Matrix);
		Matrix = menu(Matrix);
	}else{
		M *A = NULL;
		M *B = NULL;
		M *X = NULL;
		double Tolerance = 0;
		A = init_matrix(A);
		B = init_matrix(B);

		printf("Enter the tolerance: ");
		scanf(" %lf", &Tolerance);

		A = getAmatrix(A);
		printf("\n");
		B = getBmatrix(B);
		X = gauss_seidel(A, B, Tolerance);

		printf("X\n");
		X = print_seidel(X);
	}
	return 0;
}