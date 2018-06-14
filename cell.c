//-------Including libraries-------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "cell.h"

Cell *init_cell(Cell *Reg){	//Initialize a node

	Reg = (Cell *)malloc(sizeof(Cell));	//Allocate memory for the node
	if(Reg == NULL){
		printf("Memory allocation error.\n");
		return Reg;
	}

	//Set each variable's value to null values
	Reg->i = 0;
	Reg->j = 0;
	Reg->Data = 0;
	Reg->NextRow = NULL;
	Reg->NextCol = NULL;

	return Reg;
}

Cell *insert_row(Cell *Head, Cell *New){	//Insert a new node in a row

	Cell *Aux = NULL;
	Aux = init_cell(Aux);

	if(Head == NULL){	//If the row is empty (or if it's the end of it), just insert
		return New;
	}
	if(Head->j < New->j){	
	//If the row head's position is less than new node's position, call the function recursively
	//with the next node of the row as the head
		Head->NextCol = insert_row(Head->NextCol, New);
		return Head;
	}
	if(Head->j > New->j){
	//If the row head's position is greater than new node's position, the new node turns into
	//the head and then points to the previous one
		Aux = Head;
		Head = New;
		New->NextCol = Aux;
		return Head;
	}
	free(Aux);
	return Head;
}

Cell *insert_col(Cell *Head, Cell *New){	//Insert a new node in a column

	Cell *Aux = NULL;
	Aux = init_cell(Aux);

	//Same algorithm used for the rows, except
	//for the pointers, that are those appropriate to columns
	if(Head == NULL){
		return New;
	}
	if(Head->i < New->i){
		Head->NextRow = insert_col(Head->NextRow, New);
		return Head;
	}
	if(Head->i > New->i){
		Aux = Head;
		Head = New;
		New->NextRow = Aux;
		return Head;
	}
	free(Aux);
	return Head;
}

Cell *destroy_row(Cell *Head){	//Erase a row

	if(Head == NULL){	//If the head is NULL, return itself, since it's NULL
		return Head;
	}

	Head->NextCol = destroy_row(Head->NextCol);	//Call the function recursively as the next node as head
	free(Head);	//Free the memory allocated to the head
	return NULL;
}