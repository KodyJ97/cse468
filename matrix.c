#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <time.h>
#include <unistd.h>  

// Matrix column and row value. Possible sizes: 128, 256, 512, and 1024.
#define SIZE 128
#define THREAD_COUNT 2

// MAX_NUMBER and MIN_NUMBER are specifying the range of the random numbers
// generated for matrix A and matrix B.
#define MIN_NUMBER 1
#define MAX_NUMBER 5

// Global Variables
int matA[SIZE][SIZE];
int matB[SIZE][SIZE];
int matC[SIZE][SIZE];
int step_test = 0;

void print_Matrix(int mat[SIZE][SIZE])
{
	int i, j, rowcount = 0;
	printf("Printing Matrix\n");
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			printf("Index [%d][%d]: %d\t", i, j, mat[i][j]);
			rowcount++;
			if (rowcount == 5) {
				printf("\n");
				rowcount = 0;
			}
		}
	}
}

void func(int mat[SIZE][SIZE])
{
	int i, j;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			mat[i][j] = (rand() % (MAX_NUMBER + 1 - MIN_NUMBER) + MIN_NUMBER);
}

void* mygemm(void* vargp)
{
	// Geeks for geeks does a weird thing here with steps i dont think
	// we do it this way
	printf("Thread %ld: Starting mygemm\n", pthread_self());
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			for (int k = 0; k < SIZE; k++)
				matC[i][j] += matA[i][k] * matB[k][j];
	printf("Thread %ld: Ending mygemm and terminating threads\n", pthread_self());
	// Terminate thread here?
	pthread_exit(NULL);
}

int main()
{
	// Instantiate some time variables
	clock_t startClock, endClock;

	// Randomize the matrixes A and B
	func(matA);
	func(matB);

	// Start time
	startClock = clock();
	printf("Starting Time = %ld \n", startClock);

	// Create threads
	printf("Creating Threads\n");
	pthread_t tid[THREAD_COUNT];
	for (int i = 0; i < THREAD_COUNT; i++)
		pthread_create(&tid[i], NULL, mygemm, (void*)& tid);

	// Join threads - wait for specified thread to terminate
	printf("Terminating Threads\n");
	for (int j = 0; j < THREAD_COUNT; j++)
		pthread_join(tid[j], NULL);


	// End Time
	endClock = clock();
	printf("Ending Time = %ld \n", endClock);

	// Print Matrix if needed. The output will be very long so you'll lose any other debug printouts. Just leave it commented out unless you need it.
	//print_Matrix(matC);

	// Execution time formula for milliseconds
	printf("Total Execution Time = %f secs \n", ((double) (endClock - startClock) / CLOCKS_PER_SEC));
	return 0;
}
