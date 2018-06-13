//-------Including libraries-------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

int main(void){

	M *Matrix = NULL;
	Matrix = init_matrix(Matrix);
	Matrix = menu(Matrix);

	return 0;
}
