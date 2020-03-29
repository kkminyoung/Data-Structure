#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define W 3
#define H 3
#define M 3

double *** mem_alloc_3D_double() {
	//Memory Allocation
	double ***arr = (double ***)malloc(sizeof(double**)*W);
	for (int i = 0; i < W; i++) {
		arr[i] = (double **)malloc(sizeof(double*)*H);
		for (int j = 0; j < H; j++) {
			arr[i][j] = (double*)malloc(sizeof(double)*M);
		}
	}
	//Define
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			for (int k = 0; k < M; k++) {
				*(*(*(arr + i) + j) + k) = i * H*M + j * M + k;
			}
		}
	}
	//Print
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			for (int k = 0; k < M; k++) {
				printf("%.2f ", *(*(*(arr+i)+j)+k));
			}
			printf("\n");
		}
		printf("\n");
	}

	return arr;
}

void addition_3D(double ***a, double ***b) {
	double c;
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			for (int k = 0; k < M; k++) {
				c = *(*(*(a + i) + j) + k) + *(*(*(b + i) + j) + k);
				printf("%.2f ", c);
			}
			printf("\n");
		}
		printf("\n");
	}
}


int main(void) {
	//Define two matrices A and B using 'mem_alloc_3D_double';
	printf("A\n");
	double ***A = mem_alloc_3D_double();
	printf("================\n");

	printf("B\n");
	double ***B = mem_alloc_3D_double();
	printf("================\n");

	//Perform addition of two matrices using 'addtion_3D'
	printf("A+B\n");
	addition_3D(A, B);
	printf("================\n");

	//Deallocate A and B
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			free(*(*(A + i) + j));
			free(*(*(B + i) + j));
		}
		free(*(A + i));
		free(*(B + i));
	}
	free(A);
	free(B);



	return 0;


}