#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

/*

For k = 0 to n-2
If k is even then
    for i = 0 to (n/2)-1 do in parallel
        If A[2i] > A[2i+1] then
            Exchange A[2i] ↔ A[2i+1]
Else
    for i = 0 to (n/2)-2 do in parallel
        If A[2i+1] > A[2i+2] then
            Exchange A[2i+1] ↔ A[2i+2]
Next k

*/

void swap(int*, int*);

int main (int argc, char *argv[]) {
	for (int SIZE = 100; SIZE <= 1000000; SIZE += 100000) {
		int A1[SIZE], A2[SIZE];
		for (int i = 0; i < SIZE; i++)
		{
			A1[i] = rand() % SIZE;
			A2[i] = A1[i];
		}
		int N = SIZE;
		int first;
		double start, end;
		start = omp_get_wtime();
		int i, j, temp;

		#pragma omp parallel num_threads(4) default(none) shared(A1,N) private(i,temp,j)
		{
			for (i = 0; i < N; i++)
			{
				//even phase
				if (i % 2 == 0)
				{

					#pragma omp for
					for (j = 1; j < N; j += 2)
					{
						if (A1[j - 1] > A1[j])
						{
							temp = A1[j];
							A1[j] = A1[j - 1];
							A1[j - 1] = temp;
						}
					}
				}
				//odd phase
				else
				{
					#pragma omp for
					for (j = 1; j < N - 1; j += 2)
					{
						if (A1[j] > A1[j + 1])
						{
							temp = A1[j];
							A1[j] = A1[j + 1];
							A1[j + 1] = temp;
						}
					}
				}
			}
		}
		end = omp_get_wtime();
		printf("\n\n-------------------------------------------------------\n\n");
		printf("\nSIZE = %d", SIZE);
		printf("\nTime Parallel= %f", (end - start));
		start = omp_get_wtime();
		for ( i = 0; i < N - 1; i++ )
		{
			for ( j = first; j < N - 1; j += 1 )
			{
				if ( A2[ j ] > A2[ j + 1 ] )
				{
					swap( &A2[ j ], &A2[ j + 1 ] );
				}
			}
		}
		end = omp_get_wtime();
		int error  = 0;
		for (i = 0; i < N; i++)
		{
			error += A1[i] - A2[i];
		}
		printf("\nTime Sequential= %f", (end - start));
		printf("\nError %d\n", error);
	}
}

void swap(int *num1, int *num2)
{

	int temp = *num1;
	*num1 =  *num2;
	*num2 = temp;
}

/*


-------------------------------------------------------


SIZE = 100
Time Parallel= 0.007472
Time Sequential= 0.000000
Error 0


-------------------------------------------------------


SIZE = 100100
Time Parallel= 10.715249
Time Sequential= 28.013380
Error 0


-------------------------------------------------------


SIZE = 200100
Time Parallel= 46.799868
Time Sequential= 139.414257
Error 0


-------------------------------------------------------


SIZE = 300100
Time Parallel= 105.024655
Time Sequential= 400.549336
Error 0


*/
