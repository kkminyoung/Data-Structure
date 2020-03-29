#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUCKETS 10
#define DIGITS 4
#define b 24
#define r 6

void countSort(int A[], int n, int exp)
{
	int B[1000]; 
	int i, C[1000] = { 0, };

	for (i = 0; i < n; i++)
		C[(A[i] / exp) % 10]++;

	for (i = 1; i < 10; i++)
		C[i]= C[i]+C[i - 1];

	for (i = n - 1; i >= 0; i--)
	{
		B[C[(A[i] / exp) % 10] - 1] = A[i];
		C[(A[i] / exp) % 10]--;
	}

	for (i = 0; i < n; i++)
		A[i] = B[i];
}

int max_num(int A[], int n)
{
	int max = A[0];
	for (int i = 1; i < n; i++)
		if (A[i] > max)
			max = A[i];
	return max;
}


void radixsort(int A[], int n)
{
	int m = max_num(A, n);

	for (int d = 1; m / d > 0; d *= 10)
		countSort(A, n, d);

	for (int i = 0; i < n; i++)
		printf("%d\n", A[i]);
}


int main()
{
	//random number »ý¼º
	int p = 16777215; //2^24-1
	int A[1000];
	for (int i = 0; i < 1000; i++) {
		A[i] = rand() % p;
	}

	int n = sizeof(A) / sizeof(A[0]);
	radixsort(A, n);
	return 0;
}
