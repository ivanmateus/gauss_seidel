#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
			while(Aux != NULL){	//Enquanto o auxiliar for diferente de nulo
				while(Counter != Aux->j){	//Enquanto o contador for diferente da posicao do auxiliar, imprime os zeros
					printf("0 ");
					++Counter;
				}
				++Counter;
				printf("%d ", Aux->Data);	//Quando chegar na posicao do auxiliar, imprime o valor dele
				Aux = Aux->NextCol;	//Passa pro proximo elemento nao nulo
				if(Aux == NULL){	//Mas se o proximo "nao nulo" for nulo (Aux == NULL)
					while(Counter < COLS){	//Imprime zero ate acabar a linha
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

M *destroy_matrix(M *Matrix){	//Apaga a matriz

	int k = 0;

	while(k < COLS){	//Seta todos os ponteiros das colunas para NULL
		Matrix->Cols[k] = NULL;
		++k;
	}
	k = 0;
	while(k < ROWS){	//Apaga todas as linhas
		Matrix->Rows[k] = destroy_row(Matrix->Rows[k]);
		++k;
	}
	free(Matrix);	//Por fim libera a matriz
	return NULL;
}

M *sum_row(M *Matrix){	//Soma as linhas e exibe

	int k = 0;
	int Result = 0;
	Cell *Aux = NULL;
	Aux = init_cell(Aux);

	while(k < ROWS){	//Enquanto as linhas nao acabarem
		Result = 0;	//Zera o valor inicial
		Aux = Matrix->Rows[k];	//Recebe o cabeca da linha 
		while(Aux != NULL){	//Enquanto nao acabar a linha
			Result = Result + Aux->Data;	//Soma o valor de cada elemento
			Aux = Aux->NextCol;	//Pula pro proximo elemento
		}
		printf("Row %d: %d\n", k + 1, Result);	//Imprime o valor da soma
		++k;
	}
	return Matrix;
}

M *sum_col(M *Matrix){	//Soma as colunas e exibe

	//Mesmo algoritmo da soma das linhas, mas com os ponteiros das colunas
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

M* set_value(M *Matrix, int NewValue, int Row, int Col){	//Seta um valor em uma posicao definida

	Cell *New = NULL;
	New = init_cell(New);	//Inicia um novo no
	//Recebe os dados do novo no
	New->i = Row;	
	New->j = Col;
	New->Data = NewValue;

	Matrix = insert_matrix(Matrix, New);	//Insere na matriz
	return Matrix;
}

void wait(){	//Espera pela entrada do usuario
	printf("Press ENTER to continue.\n");
	getchar();
}

void clean_stdin(void){		//Função que limpa stdin
	int c;
	while(c != '\n' && c != EOF){
		c = getchar();
	}
}

M *menu(M *Matrix){	//Função que exibe as opções do menu e as executam

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
		printf("6. Set a value in a position (i,j);\n");
		printf("7. Show matrix;\n");
		printf("0. Exit the program.\n");
		printf("Type in the option: ");
		scanf("%d", &Option);
		clean_stdin();
		printf("\n\n");

		switch(Option) {
			case 1:
				printf("P.S.: If your matrix has been created already, this option will only add new numbers to it.\n");
				printf("How many non-null elements do you want in the matrix? A: ");
				scanf("%d", &Elements);
				Matrix = create_matrix(Matrix, Elements);	//Cria a matriz ou adiciona numeros novos
				printf("\nNew matrix: \n");
				Matrix = print_matrix(Matrix);	//Imprime a matriz
				printf("\n");
				clean_stdin();
				wait();
				break;
			case 2:
				Matrix = destroy_matrix(Matrix);	//Destroi a matriz
				printf("\nDone!\n");
				wait();
				break;
			case 3:
				printf("Which position do you want to consult?\n");
				printf("Row: ");
				scanf("%d", &Row);
				printf("\nColumn: ");
				scanf("%d", &Col);
				printf("\nThe element in this position is: %d\n", search(Matrix, Row - 1, Col - 1));	//Exibe o elemento da busca
				printf("\nMatrix: \n");
				Matrix = print_matrix(Matrix);	//Exibe a matriz
				printf("\n");
				clean_stdin();
				wait();
				break;
			case 4:
				printf("The sum of each row is:\n");
				Matrix = sum_row(Matrix);	//Soma e exibe as linhas
				printf("\nMatrix: \n");
				Matrix = print_matrix(Matrix);	//Exibe a matriz
				printf("\n");
				wait();
				break;
			case 5:
				printf("The sum of each column is:\n");	
				Matrix = sum_col(Matrix);	//Soma e exibe as colunas
				printf("\nMatrix: \n");
				Matrix = print_matrix(Matrix);	//Imprime a matriz
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
				Matrix = set_value(Matrix, Value, Row - 1, Col - 1);	//Seta um valor em uma dada posicao
				printf("\n\nMatrix: \n");
				Matrix = print_matrix(Matrix);	//Imprime a matriz
				printf("\n");
				clean_stdin();
				wait();
				break;
			case 7:
				printf("Matrix: \n");
				Matrix = print_matrix(Matrix);	//Imprime a matriz
				printf("\n");
				wait();
				break;
			case 0:
				Matrix = destroy_matrix(Matrix);	//Destroi a matriz e finalmente sai do programa retornando NULL
				return Matrix;
			default:
				printf("Invalid option.\n");
				wait();
				break;
		}
	}
}