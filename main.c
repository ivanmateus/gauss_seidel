#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXDATA 10
#define ROWS 100
#define COLS 100

typedef struct sparse_matrix{	//Esta eh a estrutura de um "no" da matriz
	int i;
	int j;
	int Data;
	struct sparse_matrix *NextRow;
	struct sparse_matrix *NextCol;
} Cell;

typedef struct matrix{	//Esta eh a estrutura que define a matriz
	Cell *Rows[ROWS];
	Cell *Cols[COLS];
} M;

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

M *init_matrix(M *Matrix){	//Esta funcao inicializa a matriz

	int k = 0;
	Matrix = (M *)malloc(sizeof(M));	//Aloca memoria para a matriz
	if(Matrix == NULL){
		printf("Memory allocation error.\n");
		return Matrix;
	}

	//Inicializa o vetor de ponteiros das linhas
	while(k < ROWS){
		Matrix->Rows[k] = NULL;
		++k;
	}

	//Inicializa o vetor de ponteiro das colunas
	k = 0;
	while(k < COLS){
		Matrix->Cols[k] = NULL;
		++k;
	}
	return Matrix;
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

M *insert_matrix(M *Matrix, Cell* New){	//Insere um novo elemento na matriz

	//Insere o novo no tanto nas linhas quanto nas colunas
	Matrix->Rows[New->i] = insert_row(Matrix->Rows[New->i], New);
	Matrix->Cols[New->j] = insert_col(Matrix->Cols[New->j], New);
	return Matrix;
}

int search(M *Matrix, int Row, int Col){	//Busca pelo elemento de uma certa posicao

	Cell *Aux = Matrix->Rows[Row];	//O auxiliar recebe o cabeca da linha dada

	while(Aux != NULL){	//Enquanto nao chegar ao fim da lista
		if(Aux->j == Col){	//Se o valor da coluna do no for igual ao valor dado
			return Aux->Data;	//Retorna o elemento do no
		}
		Aux = Aux->NextCol;	//Senao, pula pro proximo no
	}
	return 0;	//Se nao encontrar nada, significa que o elemento eh 0
}

M *create_matrix(M *Matrix, int NData){	//Funcao que cria uma matriz adicionando NData elementos nela

	int k = 0;
	int Result = 1;
	Cell *Aux = NULL;

	srand((unsigned)time(NULL));

	while(k < NData){	//Enquanto nao acabar o numero de elementos a serem adicionados
		Result = 1;	//Garante que sempre entrara no laco abaixo
		Aux = init_cell(Aux);	//Garante que o auxiliar sempre estara "novo em folha"
		while(Result){	//Enquanto a posicao estiver ocupada (busca diferente de 0)
			Aux->i = (rand() % ROWS);	//Da uma posicao pseudoaleatoria para i entre 0 e ROWS
			Aux->j = (rand() % COLS);	// -||- -||- -||- -||- -||- -||- j entre 0 e COLS
			Result = search(Matrix, Aux->i, Aux->j);	//Busca se ha elementos nessa posicao para que nao sejam sobrescritos
		}
		while(Aux->Data == 0){	//Enquanto o valor do elemento for nulo
			Aux->Data = (rand() % MAXDATA);	//Gere um pseudo-aleatorio entre 0 e MAXDATA
		}
		Matrix = insert_matrix(Matrix, Aux);	//Insere o novo no na matriz
		++k;
	}
	return Matrix;
}

M *print_matrix(M *Matrix){	//Exibe a matriz

	int k = 0;
	int Counter = 0;
	Cell *Aux = NULL;
	Aux = init_cell(Aux);

	while(k < ROWS){	//Enquanto as linhas nao acabarem
		Aux = Matrix->Rows[k];	//O auxiliar recebe o cabeca da linha
		Counter = 0;
		if(Aux == NULL){	//Se o auxiliar for NULL a linha toda esta vazia (somente elementos nulos)
			while(Counter < COLS){
				printf("0 ");
				++Counter;
			}
		}else{	//Senao, ha elementos nao nulos
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

Cell *destroy_row(Cell *Head){	//Apaga uma linha

	if(Head == NULL){	//Se o cabeca for NULL retorna ele mesmo
		return Head;
	}

	Head->NextCol = destroy_row(Head->NextCol);	//Chama a funcao para o proximo elemento da linha
	free(Head);	//Libera a memoria do cabeca
	return NULL;
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

int main(void){

	M *Matrix = NULL;
	Matrix = init_matrix(Matrix);
	Matrix = menu(Matrix);

	return 0;
}
