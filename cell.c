#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "cell.h"

Cell *init_cell(Cell *Reg){	//Esta funcao inicializa cada no

	Reg = (Cell *)malloc(sizeof(Cell));	//Aloca memoria para o no
	if(Reg == NULL){
		printf("Memory allocation error.\n");
		return Reg;
	}

	//Seta os valores de cada variavel para valores nulos
	Reg->i = 0;
	Reg->j = 0;
	Reg->Data = 0;
	Reg->NextRow = NULL;
	Reg->NextCol = NULL;

	return Reg;
}

Cell *insert_row(Cell *Head, Cell *New){	//Insere um novo no em uma linha

	Cell *Aux = NULL;
	Aux = init_cell(Aux);

	if(Head == NULL){	//Se a linha estiver vazia, so insere normalmente
		return New;
	}
	if(Head->j < New->j){	
	//Se o "cabeca" da linha estiver em uma posicao menor, chama a funcao recursivamente com o prox elemento da linha
	//como sendo o cabeca	
		Head->NextCol = insert_row(Head->NextCol, New);
		return Head;
	}
	if(Head->j > New->j){
	//Se o "cabeca" estiver em uma posicao maior, o novo elemento sera o cabeca
	//e apontara para o cabeca anterior
		Aux = Head;
		Head = New;
		New->NextCol = Aux;
		return Head;
	}
	free(Aux);
	return Head;
}

Cell *insert_col(Cell *Head, Cell *New){	//Insere um novo no em uma coluna

	Cell *Aux = NULL;
	Aux = init_cell(Aux);

	//O algoritmo eh o mesmo da insercao na linha, a diferenca
	//eh que os ponteiros em questao sao os que apontam para as linhas (NextRow)
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

Cell *destroy_row(Cell *Head){	//Apaga uma linha

	if(Head == NULL){	//Se o cabeca for NULL retorna ele mesmo
		return Head;
	}

	Head->NextCol = destroy_row(Head->NextCol);	//Chama a funcao para o proximo elemento da linha
	free(Head);	//Libera a memoria do cabeca
	return NULL;
}