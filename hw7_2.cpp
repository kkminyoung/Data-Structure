#include <stdio.h>

#define n 8

//for j=n-1 downto 1
void countingSort(int A[], int B[], int k)
{
	int C[10];
	for (int i = 0; i < k; ++i)
		C[i] = 0;
	for (int i = 0; i < n; i++)
		C[A[i]]++;
	for (int i = 1; i < k; i++)
		C[i] += C[i - 1];

	for (int j = n - 1; j > 0; j--) {
		B[C[A[j]] - 1] = A[j];
		C[A[j]]--;
	}

	for (int i = 0; i < n; ++i)
	{
		printf("%d  ", B[i]);
	}
	printf("\n");
}

// for j=0 to n-1
// 이렇게 코드를 짜는 것도 가능하다.
// 다만 unstable 하다.

void countingSort2(int A[], int B[], int k)
{
	int C[10];
	for (int i = 0; i <= k;i++)
		C[i] = 0;
	for (int j= 0; j < n; j++)
		C[A[j]]++;
	for (int i = 1; i <= k; i++)
		C[i] += C[i - 1];

	for (int j = 0; j < n; j++) {
		B[C[A[j]] - 1] = A[j];
		C[A[j]]--;
	}

	for (int i = 1; i < n; i++) {
		printf("%d  ", B[i]);
	}
	printf("\n");
}


int main()
{
	int A[] = { 2, 5, 3, 0, 2, 3, 0,3 };
	int B[10];
	int k = 5;
	countingSort2(A, B, k);
}