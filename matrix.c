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

int matA[SIZE][SIZE];
int matB[SIZE][SIZE];
int matC[SIZE][SIZE];
int step_test = 0;
	
void print_Matrix(int mat[SIZE][SIZE])
{
	int i,j;
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			printf("%d\n", mat[i][j]);
}

void func(int mat[SIZE][SIZE])
{
	int i,j;
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			mat[i][j] = (rand() % (MAX_NUMBER + 1 - MIN_NUMBER) + MIN_NUMBER);
}

void *mygemm(void *vargp)
{
	int test = step_test;
	// Matrix Multiplication
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			for(int k = 0; k < SIZE; k++)
				matC[i][j] += matA[i][k] * matB[k][j];
}

int main()
{
	// Instantiate some variables
	struct timeval start, stop;
	
	// Randomize the matrixes A and B
	func(matA);
	func(matB);
	
	// Start time
	gettimeofday(&start, NULL);
	
	// Create threads
	pthread_t tid[THREAD_COUNT];
	for (int i = 0; i < THREAD_COUNT; i++) 
		pthread_create(&tid[i], NULL, mygemm, (void*)&tid);
        
    for (int j = 0; j < THREAD_COUNT; j++) 
		pthread_join(tid[j], NULL);
		
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
