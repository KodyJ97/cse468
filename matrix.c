#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>  

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

//void *mygemm(int matA[SIZE][SIZE], int matB[SIZE][SIZE], int matC[SIZE][SIZE])
void *mygemm(int *vargp_a[SIZE][SIZE], int *vargp_b[SIZE][SIZE], int *vargp_c[SIZE][SIZE])
{
	// Matrix Multiplication
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			for(int k = 0; k < SIZE; k++)
				vargp_c[i][j] += vargp_a[i][k] * vargp_b[k][j];
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
	// Instantiate some variables
	struct timeval start, stop;
	int matA[SIZE][SIZE];
	int matB[SIZE][SIZE];
	int matC[SIZE][SIZE];
	
	// Randomize the matrixes A and B
	func(matA);
	func(matB);
	
	// Start time
	gettimeofday(&start, NULL);
	
	// Create threads
	pthread_t tid; 
    for (int i = 0; i < THREAD_COUNT; i++) 
        pthread_create(&tid, NULL, mygemm, (void *)&tid); 
	//mygemm(matA, matB, matC);
	pthread_exit(NULL);
	// End Time
	gettimeofday(&stop, NULL);
	
	// Print Matrix if needed.
	//print_Matrix(matC);
	
	// Execution time formula for milliseconds
	printf("Time of execution in milliseconds: %lu\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
	return 0;
}
