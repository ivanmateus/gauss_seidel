//-------Including libraries-------
#include <stdio.h>
#include <stdlib.h>

//----Defining constants----
#define N1A 50
#define N1B 100
#define N2 500
#define EPSILON 0.00000001

//----Defining the struct of a node----
typedef struct node{	//Structure of a node
	int i;
	int j;
	long double data;
	struct node *nextRow;
	struct node *nextCol;
} node;

//----Defining the struct of a row and a column----
typedef struct node* list;

//----Defining the struct of a matrix----
typedef struct sparse_matrix{	//Structure of a matrix
	list *rows;
	list *cols;
} matrix;

node *init_node(int i, int j, long double data){	//Initialize a node

	node *new = (node *)malloc(sizeof(node));	//Allocate memory for the node
	if(new == NULL){
		printf("Memory allocation error.\n");
		return new;
	}

	//Set each variable's value to null values
	new->i = i;
	new->j = j;
	new->data = data;
	new->nextRow = NULL;
	new->nextCol = NULL;
	return new;
}

list *init_list(int n){	//Initialize a row or a column
	list *new = (list *)malloc(n * sizeof(list));

	if(new != NULL){
		*new = NULL;
	}
	return new;
}

matrix *init_matrix(int n, int m){	//Initialize the matrix
	matrix *A = (matrix *)malloc(sizeof(matrix));
	
	//Initialize the row array of pointers
	A->rows = init_list(n);
	
	//Initialize the column array of pointers
	A->cols = init_list(m);
	
	return A;
}

void insert_row(list *head, node *new){	//Insert a new node in a row
	
	if(*head == NULL){	//If the row is empty (or if it's the end of it), just insert
		*head = new;
		return;
	}
	if((*head)->j < new->j){
	//If the row head's position is less than new node's position, keep going until
	//find a node which position is greater than the new node's one
		node *aux = *head;
		while(aux->j < new->j && aux->nextCol != NULL){
			aux = aux->nextCol;
		}
		if(aux->nextCol == NULL){
			aux->nextCol = new;
			return;
		}
		new->nextCol = aux->nextCol;
		aux->nextCol = new;
		return;
	}
	if((*head)->j > new->j){
	//If the row head's position is greater than new node's position, the new node turns into
	//the head and then points to the previous one
		new->nextCol = *head;
		*head = new;
		return;
	}
}

void insert_col(list *head, node *new){		//Insert a new node in a column
	//Same algorithm used for the rows, except
	//for the pointers (here they are the ones appropriate to columns)
	
	if(*head == NULL){
		*head = new;
		return;
	}
	if((*head)->i < new->i){
		node *aux = *head;
		while(aux->i < new->i && aux->nextRow != NULL){
			aux = aux->nextRow;
		}
		if(aux->nextRow == NULL){
			aux->nextRow = new;
			return;
		}
		new->nextRow = aux->nextRow;
		aux->nextRow = new;
		return;
	}
	if((*head)->i > new->i){
		new->nextRow = *head;
		*head = new;
		return;
	}
}

void insert_matrix(matrix *A, node* new, int i, int j){	//Insert a new node in the matrix
	//Insert the new node both arrays
	insert_row(&(A->rows[i]), new);
	insert_col(&(A->cols[j]), new);
}

matrix *initial_array(int n){	//Generate a column matrix with initial conditions setted to zero
	node *new = NULL;
	matrix *initArray = init_matrix(n, 1);

	for(int k = 0; k < n; ++k){
		new = init_node(k, 0, 0);
		insert_matrix(initArray, new, k, 0);
	}
	return initArray;
}

long double test_matrix_A_values(int i, int j){	//Return the matrix of coefficients’ values
	if(i == j){
		return 5;
	}
	if(j == i + 1 || j == i - 1 || j == i + 3 || j == i - 3){
		return -1;
	}
	return 0;
}

matrix *create_test_matrix_A(int n){	//Create test matrix of coefficients A
	node *new = NULL;
	matrix *A = init_matrix(n, n);

	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			int value = test_matrix_A_values(i, j);
			if(value != 0){
				new = init_node(i, j, value);
				insert_matrix(A, new, i, j);
			}
		}
	}
	return A;
}

long double test_matrix_b_values(matrix *A, int i, int test){	//Return test matrix b values
	if(test == 1){
		long double bi = 0; 
		node *aux = A->rows[i];
		while(aux != NULL){
			bi += aux->data;
			aux = aux->nextCol;
		}
		return bi;
	}
	return 1.0 / (i + 1);
}

matrix *create_test_matrix_b(matrix *A, int n, int test){	//Create test matrix b
	node *new = NULL;
	matrix *b = init_matrix(n, 1);

	for(int i = 0; i < n; ++i){
		new = init_node(i, 0, test_matrix_b_values(A, i, test));
		insert_matrix(b, new, i, 0);
	}
	return b;
}

matrix *subtract_arrays(matrix *x1, matrix *x2, int n){	//Subtract two arrays
	matrix *x3 = init_matrix(n, 1);
	node *aux1 = NULL;
	node *aux2 = NULL;
	node *aux3 = NULL;

	for(int i = 0; i < n; ++i){
		aux1 = x1->rows[i];
		aux2 = x2->rows[i];
		aux3 = init_node(i, 0, aux1->data - aux2->data);
		insert_matrix(x3, aux3, i, 0);
	}
	return x3;
}

long double abs_value(long double n){	//Return abs value of long double variable
	if(n < 0){
		return n * (-1.0);
	}
	return n;
}

long double inf_norm(matrix *x, int n){	//Calculate infinity norm of an array
	long double max = abs_value((x->rows[0])->data);
	for(int i = 1; i < n; ++i){
		if(max < abs_value((x->rows[i])->data)){
			max = abs_value((x->rows[i])->data);
		}
	}
	return max;
}

void copy_array(matrix *x1, matrix *x2, int n){	//Copy an array into other
	for(int i = 0; i < n; ++i){
		(x1->rows[i])->data = (x2->rows[i])->data;
	}
}

matrix *gauss_seidel(matrix *A, matrix *b, long double epsilon, int itmax, int n){	//Execute the Gauss-Seidel method
	int k = 0;
	long double bi = 0;
	long double aij = 0;
	long double x_kplusj = 0;
	long double x_kj = 0;
	long double sum1 = 0;
	long double sum2 = 0;
	long double aii = 0;
	node *aux = NULL;
	matrix *x_k = initial_array(n);
	matrix *x_kplus = initial_array(n);

	do{
		for(int i = 0; i < n; ++i){
			copy_array(x_k, x_kplus, n);
			sum1 = 0;
			sum2 = 0;
			bi = (b->rows[i])->data;
			aux = A->rows[i];
			while(aux != NULL && aux->j < i){
				aij = aux->data;
				x_kplusj = (x_kplus->rows[aux->j])->data;
				sum1 += aij * x_kplusj;
				aux = aux->nextCol;
			}
			aux = aux->nextCol;
			while(aux != NULL && aux->j < n){
				aij = aux->data;
				x_kj = (x_k->rows[aux->j])->data;
				sum2 += aij * x_kj;
				aux = aux->nextCol;
			}
			aux = A->rows[i];
			while(aux->j != i && aux != NULL){
				aux = aux->nextCol;
			}
			aii = aux->data;
			(x_kplus->rows[i])->data = (bi - sum1 - sum2)/aii;
		}
		++k;
	}while(inf_norm(subtract_arrays(x_kplus,x_k,n), n) > epsilon && (k + 1) <= itmax);
	if(k + 1 > itmax && inf_norm(subtract_arrays(x_kplus,x_k,n), n) > epsilon) {
		printf("METODO GAUSS-SEIDEL DIVERGIU\n");
	}
	return x_kplus;
}
void destroy_matrix(matrix *A, int n){	//Erase the matrix from memory
	if(A == NULL){
		return;
	}
	
	node *aux = NULL;
	for (int i = 0; i < n; ++i){
		A->cols[i] = NULL;
		free(A->cols[i]);
		aux = A->rows[i];
		while(aux != NULL){
			A->rows[i] = aux->nextCol;
			free(aux);
			aux = A->rows[i];
		}
	}
}

int main(int argc, char *argv[]){

	int option = -1;
	int matrixDim = 0;
	matrix *A = NULL;
	matrix *b = NULL;
	matrix *x = NULL;
	node *aux = NULL;

	while(option != 0){
		printf("Type in the test you'd like to execute:\n");
		printf("1. n = 50\n");
		printf("2. n = 100\n");
		printf("3. n = 500\n");
		printf("0. Exit the program\n");
		printf("Option: ");
		scanf("%d", &option);

		switch (option){
			case 1:
				A = create_test_matrix_A(N1A);
				b = create_test_matrix_b(A, N1A, 1);
				x = gauss_seidel(A, b, EPSILON, 5*N1A, N1A);
				
				printf("\nTEST 1a\n");
				aux = x->cols[0];
				while(aux != NULL){
					printf("i: %d | j: %d | ", aux->i + 1, aux->j + 1);
					printf("data: %.10Lf\n", aux->data);
					aux = aux->nextRow;
				}
				matrixDim = N1A;
				break;
			case 2:
				A = create_test_matrix_A(N1B);
				b = create_test_matrix_b(A, N1B, 1);
				x = gauss_seidel(A, b, EPSILON, 5*N1B, N1B);
				
				printf("\nTEST 1b\n");
				aux = x->cols[0];
				while(aux != NULL){
					printf("i: %d | j: %d | ", aux->i + 1, aux->j + 1);
					printf("data: %.10Lf\n", aux->data);
					aux = aux->nextRow;
				}
				matrixDim = N1B;
				break;
			case 3:
				A = create_test_matrix_A(N2);
				b = create_test_matrix_b(A, N2, 2);
				x = gauss_seidel(A, b, EPSILON, 5*N2, N2);
				
				printf("\nTEST 2\n");
				aux = x->cols[0];
				while(aux != NULL){
					printf("i: %d | j: %d | ", aux->i + 1, aux->j + 1);
					printf("data: %.10Lf\n", aux->data);
					aux = aux->nextRow;
				}
				matrixDim = N2;
				break;
			default:
				destroy_matrix(A, matrixDim);
				destroy_matrix(b, matrixDim);
				destroy_matrix(x, matrixDim);
				break;
		}
		printf("\n");
	}
	return 0;
}
