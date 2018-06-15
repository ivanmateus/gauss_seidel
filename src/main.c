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

		printf("\n");
		A = getAmatrix(A);
		printf("\n");
		B = getBmatrix(B);
		X = gauss_seidel(A, B, Tolerance);

		printf("\nX\n");
		X = print_seidel(X);

		A = destroy_matrix(A);
		B = destroy_matrix(B);
		X = destroy_matrix(X);
	}
	return 0;
}
