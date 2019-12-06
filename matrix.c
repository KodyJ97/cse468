#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <time.h>
#include <unistd.h>  

// Changed to take in arguments
// Matrix column and row value. Possible sizes: 128, 256, 512, and 1024.
//#define SIZE 1024
// Thread count. Can be 1, 2, 4, 8, or 16. Defined at runtime.
//#define THREAD_COUNT 2

// MAX_NUMBER and MIN_NUMBER are specifying the range of the random numbers
// generated for matrix A and matrix B.
#define MIN_NUMBER 1
#define MAX_NUMBER 5

// Global Variables
int matA128[128][128], matA256[256][256], matA512[512][512], matA1024[1024][1024];
int matB128[128][128], matB256[256][256], matB512[512][512], matB1024[1024][1024];
int matC128[128][128], matC256[256][256], matC512[512][512], matC1024[1024][1024];
int THREAD_COUNT, SIZE;

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

void* mygemm128(void* vargp)
{
	int* thread_no = vargp;
	for (int i = 0; i < (128 / THREAD_COUNT); i++) {
		int i_index = i + ((128 / THREAD_COUNT) * *thread_no);
		if (i == 0 || i == ((128 / THREAD_COUNT) - 1)) {
		}
		for (int j = 0; j < 128; j++) {
			for (int k = 0; k < 128; k++) {
				matC128[i_index][j] += matA128[i_index][k] * matB128[k][j];
			}
		}
	}
	pthread_exit(NULL);
}

void* mygemm256(void* vargp)
{
	int* thread_no = vargp;
	for (int i = 0; i < (256 / THREAD_COUNT); i++) {
		int i_index = i + ((256 / THREAD_COUNT) * *thread_no);
		if (i == 0 || i == ((256 / THREAD_COUNT) - 1)) {
		}
		for (int j = 0; j < 256; j++) {
			for (int k = 0; k < 256; k++) {
				matC256[i_index][j] += matA256[i_index][k] * matB256[k][j];
			}
		}
	}
	pthread_exit(NULL);
}

void* mygemm512(void* vargp)
{
	int* thread_no = vargp;
	for (int i = 0; i < (512 / THREAD_COUNT); i++) {
		int i_index = i + ((512 / THREAD_COUNT) * *thread_no);
		if (i == 0 || i == ((512 / THREAD_COUNT) - 1)) {
		}
		for (int j = 0; j < 512; j++) {
			for (int k = 0; k < 512; k++) {
				matC512[i_index][j] += matA512[i_index][k] * matB512[k][j];
			}
		}
	}
	pthread_exit(NULL);
}

void* mygemm1024(void* vargp)
{
	int* thread_no = vargp;
	for (int i = 0; i < (1024 / THREAD_COUNT); i++) {
		int i_index = i + ((1024 / THREAD_COUNT) * *thread_no);
		if (i == 0 || i == ((1024 / THREAD_COUNT) - 1)) {
		}
		for (int j = 0; j < 1024; j++) {
			for (int k = 0; k < 1024; k++) {
				matC1024[i_index][j] += matA1024[i_index][k] * matB1024[k][j];
			}
		}
	}
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	// Instantiate some time variables
	clock_t startClock, endClock;

	if (argc > 1) {
		sscanf(argv[1], "%d", &THREAD_COUNT);
		sscanf(argv[2], "%d", &SIZE);
		printf("THREAD_COUNT = %d \t SIZE = %d\n", THREAD_COUNT, SIZE);

		// Randomize the matrixes A and B
		switch (SIZE) {
		case 128:
			func(matA128);
			func(matB128);
			break;
		case 256:
			func(matA256);
			func(matB256);
			break;
		case 512:
			func(matA512);
			func(matB512);
			break;
		case 1024:
			func(matA1024);
			func(matB1024);
			break;
		}

		// Start time
		startClock = clock();

		// Create threads
		printf("Creating Threads\n");
		pthread_t tid[THREAD_COUNT];
		int threadNo[THREAD_COUNT];
		for (int i = 0; i < THREAD_COUNT; i++) {
			threadNo[i] = i;
			switch (SIZE) {
			case 128:
				pthread_create(&tid[i], NULL, mygemm128, &threadNo[i]);
				break;
			case 256:
				pthread_create(&tid[i], NULL, mygemm256, &threadNo[i]);
				break;
			case 512:
				pthread_create(&tid[i], NULL, mygemm512, &threadNo[i]);
				break;
			case 1024:
				pthread_create(&tid[i], NULL, mygemm1024, &threadNo[i]);
				break;
			}
		}

		// Join threads - wait for specified thread to terminate
		printf("Terminating Threads\n");
		for (int j = 0; j < THREAD_COUNT; j++)
			pthread_join(tid[j], NULL);

		// End Time
		endClock = clock();

		// Print Matrix if needed. The output will be very long so you'll lose any other debug printouts. Just leave it commented out unless you need it.
		/*
		print_Matrix(matC);
		*/

		// Execution time formula for milliseconds
		printf("Total Execution Time = %ld ms \n", (((endClock - startClock) / 1000)));
	}
	return 0;
}
