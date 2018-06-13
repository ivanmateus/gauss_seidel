#ifndef CELL_H_
#define CELL_H_

//-------Including libraries-------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

//----Defining the struct of a node----
typedef struct sparse_matrix{	//Structure of a node
	int i;
	int j;
	int Data;
	struct sparse_matrix *NextRow;
	struct sparse_matrix *NextCol;
} Cell;

Cell *init_cell(Cell *Reg);	//Initialize a node
Cell *insert_row(Cell *Head, Cell *New);	//Insert a new node in a row
Cell *insert_col(Cell *Head, Cell *New);	//Insert a new node in a columns
Cell *destroy_row(Cell *Head);	//Erase a row

#endif