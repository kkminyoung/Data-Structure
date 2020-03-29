#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101

typedef struct {
	int row;
	int col;
	int value;
} element;

typedef struct SparseMatrix {
	element data[MAX_TERMS];
	int rows;
	int cols;
	int terms;
}SparseMatrix;

SparseMatrix sparse_matrix_T(SparseMatrix a) {
	SparseMatrix b;
	int bind; //v

	b.rows = a.cols;
	b.cols = a.rows;
	b.terms = a.terms;

	if (a.terms > 0) {
		bind = 0;
		for (int i = 0; i < b.rows; i++) {
			for (int j = 0; j < b.terms; j++) {
				if (a.data[j].col == i) {
					b.data[bind].row = a.data[j].col;
					b.data[bind].col = a.data[j].row;
					b.data[bind].value = a.data[j].value;
					bind++;
				}
			}
		}
	}
	return b;
}


int main(void) {
	//Add B as an input.
	SparseMatrix B = { {{0,3,7},{1,0,9},{1,5,8},{3,0,6},{3,1,5},{4,5,1},{5,2,2}} ,  6,6,7 };
	SparseMatrix B_T;

	//Perform the transpose operation
	B_T = sparse_matrix_T(B);

	//Print out B and B^T in a dense matrix from to check
	//whether the operation works correctly.

	printf("***B*** \n");
	
	for (int i = 0; i < B.terms; i++) {
		printf("(%d,%d,%d) \n", B.data[i].row, B.data[i].col, B.data[i].value);
	}
	printf("==check==\n");
	int t = 0;
	for (int i = 0; i < B.rows; i++) {
		for (int j = 0; j < B.cols; j++) {
			if (B.data[t].row == i && B.data[t].col == j) {
				printf("%d", B.data[t].value);
				t++;
			}
			else {
				printf("0");
			}
		}
		printf("\n");
	}
	printf("=========\n");
	printf("\n");

	printf("***B_T*** \n");
	for (int i = 0; i < B_T.terms; i++) {
		printf("(%d,%d,%d) \n", B_T.data[i].row, B_T.data[i].col, B_T.data[i].value);
	}
	printf("===check===\n");
	int tt = 0;
	for (int i = 0; i < B_T.rows; i++) {
		for (int j = 0; j < B_T.cols; j++) {
			if (B_T.data[tt].row == i && B_T.data[tt].col == j) {
				printf("%d", B_T.data[tt].value);
				tt++;
			}
			else {
				printf("0");
			}
		}
		printf("\n");
	}
	printf("=========");


	return 0;
}