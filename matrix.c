#include <stdio.h> 
#include <stdlib.h> 

// Matrix column and row value. Possible sizes: 128, 256, 512, and 1024.
#define SIZE 128

// MAX_NUMBER and MIN_NUMBER are specifying the range of the random numbers
// generated for matrix A and matrix B.
#define MIN_NUMBER 1
#define MAX_NUMBER 10

void func(int mat[SIZE][SIZE])
{
	int i,j;
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			mat[i][j] = (rand() % (MAX_NUMBER + 1 - MIN_NUMBER) + MIN_NUMBER);
}

int mygemm(int matA[SIZE][SIZE], int matB[SIZE][SIZE], int matC[SIZE][SIZE])
{
	// Matrix Multiplication
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			for(int k = 0; k < SIZE; k++)
				matC[i][j] += matA[i][k] * matB[k][j];
}

void print_Matrix(int mat[SIZE][SIZE])
{
	int i,j;
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			printf("%d\n", mat[i][j]);
}


int main()
{
	printf("matrix.c\n");
	int matA[SIZE][SIZE];
	int matB[SIZE][SIZE];
	int matC[SIZE][SIZE];
	func(matA);
	func(matB);
	mygemm(matA, matB, matC);
	print_Matrix(matC);
	return 0;
}
