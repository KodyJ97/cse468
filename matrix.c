#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <sys/time.h>

// Matrix column and row value. Possible sizes: 128, 256, 512, and 1024.
#define SIZE 128
#define THREAD_COUNT 2

// MAX_NUMBER and MIN_NUMBER are specifying the range of the random numbers
// generated for matrix A and matrix B.
#define MIN_NUMBER 1
#define MAX_NUMBER 5

void func(int mat[SIZE][SIZE])
{
	int i,j;
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			mat[i][j] = (rand() % (MAX_NUMBER + 1 - MIN_NUMBER) + MIN_NUMBER);
}

void mygemm(int matA[SIZE][SIZE], int matB[SIZE][SIZE], int matC[SIZE][SIZE])
{
	// Matrix Multiplication
	int count = 0;
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
	struct timeval start, stop;
	printf("matrix.c\n");
	int matA[SIZE][SIZE];
	int matB[SIZE][SIZE];
	int matC[SIZE][SIZE];
	func(matA);
	func(matB);
	gettimeofday(&start, NULL);
	mygemm(matA, matB, matC);
	gettimeofday(&stop, NULL);
	//print_Matrix(matC);
	// Execution time
	printf("Time of execution in milliseconds: %lu\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
	return 0;
}
