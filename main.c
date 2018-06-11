#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXDATA 10
#define ROWS 1000000
#define COLS 1000000

typedef struct sparse_matrix{
	int i;
	int j;
	int Data;
	struct sparse_matrix *NextRow;
	struct sparse_matrix *NextCol;
} Cell;

typedef struct matrix{
	Cell *Rows[ROWS];
	Cell *Cols[COLS];
} M;

Cell *init_cell(Cell *Reg){

	Reg = (Cell *)malloc(sizeof(Cell));
	if(Reg == NULL){
		printf("Memory allocation error.\n");
		return Reg;
	}

	Reg->i = 0;
	Reg->j = 0;
	Reg->Data = 0;
	Reg->NextRow = NULL;
	Reg->NextCol = NULL;

	return Reg;
}

M *init_matrix(M *Matrix){

	int k = 0;
	Matrix = (M *)malloc(sizeof(M));
	if(Matrix == NULL){
		printf("Memory allocation error.\n");
		return Matrix;
	}

	while(k < ROWS){
		Matrix->Rows[k] = NULL;
		++k;
	}

	k = 0;
	while(k < COLS){
		Matrix->Cols[k] = NULL;
		++k;
	}
	return Matrix;
}

Cell *insert_row(Cell *Head, Cell *New){

	Cell *Aux = NULL;
	Aux = init_cell(Aux);

	if(Head == NULL){
		return New;
	}
	if(Head->j < New->j){
		Head->NextCol = insert_row(Head->NextCol, New);
		return Head;
	}
	if(Head->j > New->j){
		Aux = Head;
		Head = New;
		New->NextCol = Aux;
		return Head;
	}
	free(Aux);
	return Head;
}

Cell *insert_col(Cell *Head, Cell *New){

	Cell *Aux = NULL;
	Aux = init_cell(Aux);

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

M *insert_matrix(M *Matrix, Cell* New){

	Matrix->Rows[New->i] = insert_row(Matrix->Rows[New->i], New);
	Matrix->Cols[New->j] = insert_col(Matrix->Cols[New->j], New);
	return Matrix;
}

int search(M *Matrix, int Row, int Col){

	Cell *Aux = Matrix->Rows[Row];

	while(Aux != NULL){
		if(Aux->j == Col){
			return Aux->Data;
		}
		Aux = Aux->NextCol;
	}
	return 0;
}

M *create_matrix(M *Matrix, int NData){

	int k = 0;
	int Result = 1;
	Cell *Aux = NULL;

	srand((unsigned)time(NULL));

	while(k < NData){
		Result = 1;
		Aux = init_cell(Aux);
		while(Result){
			Aux->i = (rand() % ROWS);
			Aux->j = (rand() % COLS);
			Result = search(Matrix, Aux->i, Aux->j);
		}
		while(Aux->Data == 0){
			Aux->Data = (rand() % MAXDATA);
		}
		Matrix = insert_matrix(Matrix, Aux);
		++k;
	}
	return Matrix;
}

M *print_matrix(M *Matrix){

	int k = 0;
	int Counter = 0;
	Cell *Aux = NULL;
	Aux = init_cell(Aux);

	while(k < ROWS){
		Aux = Matrix->Rows[k];
		Counter = 0;
		if(Aux == NULL){
			while(Counter < COLS){
				//printf("(%d, %d) 0 ", k + 1, Counter + 1);
				printf("0 ");
				++Counter;
			}
		}else{
			while(Aux != NULL){
				while(Counter != Aux->j){
					//printf("(%d, %d) 0 ", k + 1, Counter + 1);
					printf("0 ");
					++Counter;
				}
				++Counter;
				//printf("(%d, %d) %d ", k + 1, (Aux->j + 1), Aux->Data);
				printf("%d ", Aux->Data);
				Aux = Aux->NextCol;
				if(Aux == NULL){
					while(Counter < COLS){
						//printf("(%d, %d) 0 ", k + 1, Counter + 1);
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

Cell *destroy_row(Cell *Head){

	if(Head == NULL){
		return Head;
	}

	Head->NextCol = destroy_row(Head->NextCol);
	free(Head);
	return NULL;
}

M *destroy_matrix(M *Matrix){

	int k = 0;

	while(k < COLS){
		Matrix->Cols[k] = NULL;
		++k;
	}
	k = 0;
	while(k < ROWS){
		Matrix->Rows[k] = destroy_row(Matrix->Rows[k]);
		++k;
	}
	free(Matrix);
	return NULL;
}

M *sum_row(M *Matrix){

	int k = 0;
	int Result = 0;
	Cell *Aux = NULL;
	Aux = init_cell(Aux);

	while(k < ROWS){
		Result = 0;
		Aux = Matrix->Rows[k];
		while(Aux != NULL){
			Result = Result + Aux->Data;
			Aux = Aux->NextCol;
		}
		printf("Row %d: %d\n", k + 1, Result);
		++k;
	}
	return Matrix;
}

M *sum_col(M *Matrix){

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

M* set_value(M *Matrix, int NewValue, int Row, int Col){

	Cell *New = NULL;
	New = init_cell(New);
	New->i = Row;
	New->j = Col;
	New->Data = NewValue;

	Matrix = insert_matrix(Matrix, New);
	return Matrix;
}

void wait(){
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
		printf("1. Create %d x %d matrix (can be changed in the constant definition section);\n", ROWS, COLS);
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
				Matrix = init_matrix(Matrix);
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
				if(Matrix == NULL){
					printf("The matrix hasn't been created yet.\n");
					wait();
				}else{
					Matrix = destroy_matrix(Matrix);
					printf("\nDone!\n");
					wait();
				}
				break;
			case 3:
				if(Matrix == NULL){
					printf("The matrix hasn't been created yet.\n");
					wait();
				}else{
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
				}
				break;
			case 4:
				if(Matrix == NULL){
					printf("The matrix hasn't been created yet.\n");
					wait();
				}else{
					printf("The sum of each row is:\n");
					Matrix = sum_row(Matrix);
					printf("\nMatrix: \n");
					Matrix = print_matrix(Matrix);
					printf("\n");
					wait();
				}
				break;
			case 5:
				if(Matrix == NULL){
					printf("The matrix hasn't been created yet.\n");
					wait();
				}else{
					printf("The sum of each column is:\n");
					Matrix = sum_col(Matrix);
					printf("\nMatrix: \n");
					Matrix = print_matrix(Matrix);
					printf("\n");
					wait();
				}
				break;
			case 6:
				if(Matrix == NULL){
					printf("The matrix hasn't been created yet.\n");
					wait();
				}else{
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
				}
				break;
			case 7:
				if(Matrix == NULL){
					printf("The matrix hasn't been created yet.\n");
					wait();
				}else{

					printf("Matrix: \n");
					Matrix = print_matrix(Matrix);
					printf("\n");
					wait();
				}
				break;
			case 0:
				if(Matrix == NULL){
					return Matrix;
				}
				Matrix = destroy_matrix(Matrix);
				return Matrix;
			default:
				printf("Invalid option.\n");
				wait();
				break;
		}
	}
}

int main(void){

	M *Matrix = NULL;
	Matrix = menu(Matrix);

	return 0;
}
