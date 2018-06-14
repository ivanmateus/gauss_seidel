//-------Including libraries-------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "cell.h"
#include "gaussseidel.h"

M *getAmatrix(M *A){	//Get the matrix of coefficients

	int i = 0;
	int j = 0;
	int Value = 0;
	Cell *AuxCell = NULL;
	AuxCell = init_cell(AuxCell);

	while(i < ROWS){	//While the # of rows isnt reached
		j = 0;
		while(j < COLS){	//While the # of columns isnt reached
			Value = 0;
			printf("Type in the element in position (%d, %d) of matrix A: ", i + 1, j + 1); 	//Ask for the element
			scanf("%d", &Value);
			//Put the data in a new node
			AuxCell = init_cell(AuxCell);
			AuxCell->i = i;
			AuxCell->j = j;
			AuxCell->Data = Value;
			A = insert_matrix(A, AuxCell);	//Insert it in the matrix
			++j;
		}
		++i;
	}
	return A;
}

M *getBmatrix(M *B){	//Get the matrix of independent coefficients

	//Same algorithm, but the matrix is a column
	int k = 0;
	int Value = 0;
	Cell *AuxCell = NULL;
	AuxCell = init_cell(AuxCell);

	while(k < COLS){
		Value = 0;
		printf("Type in the element in position (%d, 1) of matrix B: ", k + 1);
		scanf("%d", &Value);
		AuxCell = init_cell(AuxCell);
		AuxCell->i = k;
		AuxCell->j = 0;
		AuxCell->Data = Value;
		B->Rows[k] = insert_row(B->Rows[k], AuxCell);
		++k;
	}
	return B;
}

M *initial_array(){	//Generate a column matrix with initial conditions setted to zero

	int k = 0;
	M *InitArray = NULL;
	Cell *Aux = NULL;
	InitArray = init_matrix(InitArray);

	while(k < COLS){	//While the # of columns (which is the number of variables) isnt reached
		Aux = init_cell(Aux);	//Guarantee aux node is always "brand new"
		//Set the data as said
		Aux->i = k;	
		Aux->j = 0;	
		Aux->Data = 0;
		InitArray->Rows[k] = insert_row(InitArray->Rows[k], Aux);	//And insert the node
		++k;
	}
	return InitArray;
}

M *gauss_seidel(M *A, M *B, float AllowedErr){

	int Counter1 = 0;
	int Counter2 = 0;
	float Error = 0.0;	//Store the error values of each iteration
	float AuxErr = 1000.0;	//Check when the wanted tolerance is reached
	float Sum = 0;	//Store the sums
	float AuxTemp = 0;	//Store the current value of the variable
	M *InitMat = NULL;	//Store the final and updating values of the variables
	Cell *AuxHead = NULL;
	InitMat = initial_array();

	while(AuxErr >= AllowedErr){	//Check if the tolerance was reached
		AuxErr = 0;	//Always setted to zero to guarantee that the error values will always be greater than it
		Counter1 = 0;	//Used to localize the coefficients in the matrix
		while(Counter1 < ROWS){		//While the # of rows isnt reached
			Counter2 = 0;	//Used do localize the coefficients in the matrix
			Sum = 0;	//Always setted to zero for zero is the null element of sum
			while(Counter2 < COLS){	//While the # of columns isnt reached
				if(Counter2 != Counter1){	//Will only do the sum if it's not the current variable
					AuxHead = InitMat->Rows[Counter2];	//Get the previous value of the variable
					//Sum the coefficient of the variable times its previous value with the previous sum result
					Sum = Sum + search(A, Counter1, Counter2)*(AuxHead->Data);
				}
				++Counter2;	//Go to the next column
			}
			//Calculate the current value of the variable in question
			AuxTemp = (search(B, Counter1, 0) - Sum)/search(A, Counter1, Counter1);
			AuxHead = InitMat->Rows[Counter1];	//Get the previous value of variable
			Error = fabs((AuxHead->Data) - AuxTemp);	//And calculate the error between them
			if(Error > AuxErr){	//If this error is greater than the stored one
				AuxErr = Error;	//Substitute it
			}
			(InitMat->Rows[Counter1])->Data = AuxTemp;	//Then set the current value of the variable to the new one
			++Counter1;	//Go to the next row
		}
	}
	return InitMat;	//Return the results when the tolerance is reached
}

M *print_seidel(M *Matrix){	//Show the variables matrix

	int k = 0;
	Cell *Aux = NULL;
	Aux = init_cell(Aux);
	
	while(k < COLS){	//While the # of variables isnt reached
		Aux = Matrix->Rows[k];
		printf("x[%d]: %.5f\n", k, Aux->Data);	//Continue printing their values
		++k;
	}
		
	return Matrix;
}
