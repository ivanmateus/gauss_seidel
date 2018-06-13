#ifndef MATRIX_H_
#define MATRIX_H_

//-------Including libraries-------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cell.h"

//-------Constants' definition section-------
#define MAXDATA 10
#define ROWS 100
#define COLS 100

//----Defining the struct of a matrix----
typedef struct matrix{	//Structure of a matrix
	Cell *Rows[ROWS];
	Cell *Cols[COLS];
} M;

M *init_matrix(M *Matrix);	//Initialize the matrix
M *insert_matrix(M *Matrix, Cell* New);	//Insert a new node in the matrix
int search(M *Matrix, int Row, int Col);	//Search for the element of a certain position
M *create_matrix(M *Matrix, int NData);	//Create a matrix by adding NData elements in it
M *print_matrix(M *Matrix);	//Show the matrix
M *destroy_matrix(M *Matrix);	//Erase the matrix
M *sum_row(M *Matrix);	//Sum the rows
M *sum_col(M *Matrix);	//Sum the columns
M* set_value(M *Matrix, int NewValue, int Row, int Col);	//Set a new value in a certain position
void wait();	//Wait for the user to press ENTER
void clean_stdin(void);		//Clean the stdin
M *menu(M *Matrix);	//Show the menu

#endif