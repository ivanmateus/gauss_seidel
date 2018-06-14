#ifndef GAUSSSEIDEL_H_
#define GAUSSSEIDEL_H_

//-------Including libraries-------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "matrix.h"
#include "cell.h"

M *getAmatrix(M *A);	//Get the matrix of coefficients
M *getBmatrix(M *B);	//Get the matrix of independent coefficients
M *initial_array();	//Generate a column matrix with initial conditions setted to zero
M *gauss_seidel(M *A, M *B, float AllowedErr);	//Apply the Gauss-Seidel method in the matrixes
M *print_seidel(M *Matrix);	//Show the variables matrix

#endif
