//-------Including libraries-------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "matrix.h"
#include "cell.h"

M *init_matrix(M *Matrix){	//Initialize the matrix

	int k = 0;
	Matrix = (M *)malloc(sizeof(M));	//Allocate memory for the matrix
	if(Matrix == NULL){
		printf("Memory allocation error.\n");
		return Matrix;
	}

	//Initialize the row array of pointers
	while(k < ROWS){
		Matrix->Rows[k] = NULL;
		++k;
	}

	//Initialize the column array of pointers
	k = 0;
	while(k < COLS){
		Matrix->Cols[k] = NULL;
		++k;
	}
	return Matrix;
}

M *insert_matrix(M *Matrix, Cell* New){	//Insert a new node in the matrix

	//Insert the new node both arrays
	Matrix->Rows[New->i] = insert_row(Matrix->Rows[New->i], New);
	Matrix->Cols[New->j] = insert_col(Matrix->Cols[New->j], New);
	return Matrix;
}

int search(M *Matrix, int Row, int Col){	//Search for the element of a certain position

	Cell *Aux = Matrix->Rows[Row];	//The aux node receives the head element of a row

	while(Aux != NULL){	//While the end of the list isnt reached
		if(Aux->j == Col){	//If the value of the column in the node is equal to the given value
			return Aux->Data;	//Return the element in the node
		}
		Aux = Aux->NextCol;	//Else, go to the next node
	}
	return 0;	//If nothing is returned, then the element is 0
}

M *create_matrix(M *Matrix, int NData){	//Create a matrix by adding NData elements into it

	int k = 0;
	int Result = 1;
	Cell *Aux = NULL;

	srand((unsigned)time(NULL));

	while(k < NData){	//While the # of elements to be added isnt reached
		Result = 1;	//Guarantee that it will always enter the loop
		Aux = init_cell(Aux);	//Guarantee aux node is always "brand new"
		while(Result){	//While the position is still occupied
			Aux->i = (rand() % ROWS);	//Generate a pseudorandom row position from 0 to ROWS
			Aux->j = (rand() % COLS);	// -||- -||- -||- -||- -||- -||- column position from 0 to COLS
			Result = search(Matrix, Aux->i, Aux->j);	//Check if the position is ocuupied
		}
		while(Aux->Data == 0){	//While the aux element is 0
			Aux->Data = (rand() % MAXDATA);	//Generate a new value from 0 to MAXDATA
		}
		Matrix = insert_matrix(Matrix, Aux);	//Insert the new node into the matrix
		++k;
	}
	return Matrix;
}

M *print_matrix(M *Matrix){	//Show the matrix

	int k = 0;
	int Counter = 0;
	Cell *Aux = NULL;
	Aux = init_cell(Aux);

	while(k < ROWS){	//While the # of rows isnt reached
		Aux = Matrix->Rows[k];	//Aux receives the head of the row
		Counter = 0;
		if(Aux == NULL){	//If Aux == NULL, then all elements are 0
			while(Counter < COLS){
				printf("0 ");
				++Counter;
			}
		}else{	//Else
			while(Aux != NULL){	//While the end of the list isnt reached
				while(Counter != Aux->j){	//While Counter is different from the Aux's column position, print the 0's
					printf("0 ");
					++Counter;
				}
				++Counter;
				printf("%d ", (int)Aux->Data);	//When the Aux's column position is reached, print its element
				Aux = Aux->NextCol;	//Then go to the next non-null element
				if(Aux == NULL){	//But if the next "non-null" is null (Aux == NULL)
					while(Counter < COLS){	//Then print 0 until the list is over
						printf("0 ");
						++Counter;
					}
				}
			}
		}
		printf("\n");
		++k;
	}
	return Matrix;
}

M *destroy_matrix(M *Matrix){	//Erase the matrix

	int k = 0;

	while(k < COLS){	//Set all column pointers to null
		Matrix->Cols[k] = NULL;
		++k;
	}
	k = 0;
	while(k < ROWS){	//Erase all rows
		Matrix->Rows[k] = destroy_row(Matrix->Rows[k]);
		++k;
	}
	free(Matrix);	//Then free the matrix
	return NULL;
}

M *sum_row(M *Matrix){	//Sum each row's elements and show the result

	int k = 0;
	int Result = 0;
	Cell *Aux = NULL;
	Aux = init_cell(Aux);

	while(k < ROWS){	//While the rows arent over
		Result = 0;	//Set the initial value to 0
		Aux = Matrix->Rows[k];	//Receive the head of the row
		while(Aux != NULL){	//While the end of the row isnt reached
			Result = Result + Aux->Data;	//Sum the element with the initial value
			Aux = Aux->NextCol;	//Then go to the next node
		}
		printf("Row %d: %d\n", k + 1, Result);	//Print the result
		++k;
	}
	return Matrix;
}

M *sum_col(M *Matrix){	//Sum each column's elements and show the result

	//The same algorithm used to the rows,
	//but now with columns
	int k = 0;
	int Result = 0;
	Cell *Aux = NULL;
	Aux = init_cell(Aux);

	while(k < COLS){
		Result = 0;
		Aux = Matrix->Cols[k];
		while(Aux != NULL){
			Result = Result + Aux->Data;
			Aux = Aux->NextRow;
		}
		printf("Column %d: %d\n", k + 1, Result);
		++k;
	}
	return Matrix;
}

M* set_value(M *Matrix, int NewValue, int Row, int Col){	//Set a value in a certain position (not occupied yet)

	Cell *New = NULL;
	New = init_cell(New);	//Initialize a new node
	//Receive all the necessary data
	New->i = Row;
	New->j = Col;
	New->Data = NewValue;

	Matrix = insert_matrix(Matrix, New);	//Then put it into the matrix
	return Matrix;
}

void wait(){	//Wait for the user to press ENTER
	printf("Press ENTER to continue.\n");
	getchar();
}

void clean_stdin(void){		//Clean the stdin buffer
	int c;
	while(c != '\n' && c != EOF){
		c = getchar();
	}
}

M *menu(M *Matrix){	//Show the menu

	int Elements = 0;
	int Row = 0;
	int Col = 0;
	int Value = 0;
	int Option = 0;

	while(1){

		Option = 0;

		printf("\e[1;1H\e[2J");
		printf("============================================\n");
		printf("                    Menu\n");
		printf("============================================\n\n");
		printf("Choose an option: \n");
		printf("1. Create %d x %d matrix (it can be changed in the code);\n", ROWS, COLS);
		printf("2. Erase the matrix;\n");
		printf("3. Consult the data in a position (i,j) in the matrix;\n");
		printf("4. Consult the sum of each row;\n");
		printf("5. Consult the sum of each column;\n");
		printf("6. Set a value in an unoccupied position (i,j);\n");
		printf("7. Show matrix;\n");
		printf("0. Exit the program.\n");
		printf("Type in the option: ");
		scanf("%d", &Option);
		clean_stdin();
		printf("\n\n");

		switch(Option) {
			case 1:
				printf("P.S.: If your matrix has been created already, this option will only add new numbers to it. ");
				printf("If you want to create a new matrix, erase the current one with option #2, then choose the #1 again.\n\n");
				printf("How many non-null elements do you want in the matrix? A: ");
				scanf("%d", &Elements);
				Matrix = create_matrix(Matrix, Elements);
				printf("\nNew matrix: \n");
				Matrix = print_matrix(Matrix);
				printf("\n");
				clean_stdin();
				wait();
				break;
			case 2:
				Matrix = destroy_matrix(Matrix);
				Matrix = init_matrix(Matrix);
				printf("\nDone!\n");
				wait();
				break;
			case 3:
				printf("Which position do you want to consult?\n");
				printf("Row: ");
				scanf("%d", &Row);
				printf("\nColumn: ");
				scanf("%d", &Col);
				printf("\nThe element in this position is: %d\n", search(Matrix, Row - 1, Col - 1));
				printf("\nMatrix: \n");
				Matrix = print_matrix(Matrix);
				printf("\n");
				clean_stdin();
				wait();
				break;
			case 4:
				printf("The sum of each row is:\n");
				Matrix = sum_row(Matrix);
				printf("\nMatrix: \n");
				Matrix = print_matrix(Matrix);
				printf("\n");
				wait();
				break;
			case 5:
				printf("The sum of each column is:\n");
				Matrix = sum_col(Matrix);
				printf("\nMatrix: \n");
				Matrix = print_matrix(Matrix);
				printf("\n");
				wait();
				break;
			case 6:
				printf("Which value do you want to set? A: ");
				scanf("%d", &Value);
				printf("\nIn which position do you want to set?\n");
				printf("Row: ");
				scanf("%d", &Row);
				printf("\nColumn: ");
				scanf("%d", &Col);
				Matrix = set_value(Matrix, Value, Row - 1, Col - 1);
				printf("\n\nMatrix: \n");
				Matrix = print_matrix(Matrix);
				printf("\n");
				clean_stdin();
				wait();
				break;
			case 7:
				printf("Matrix: \n");
				Matrix = print_matrix(Matrix);
				printf("\n");
				wait();
				break;
			case 0:
				Matrix = destroy_matrix(Matrix);
				return Matrix;
			default:
				printf("Invalid option.\n");
				wait();
				break;
		}
	}
}
