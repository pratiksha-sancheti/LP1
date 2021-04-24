#include<stdio.h>
#include <stdlib.h>

#include<omp.h>
#include<iostream>

using namespace std;
typedef long long int LLI;
void merge(LLI array[], LLI low, LLI mid, LLI high)
{
	LLI temp[1000000];
	LLI i, j, k, m;
	j = low;
	m = mid + 1;
	for (i = low; j <= mid && m <= high ; i++)
	{
		if (array[j] <= array[m])
		{
			temp[i] = array[j];
			j++;
		}
		else
		{
			temp[i] = array[m];
			m++;
		}
	}
	if (j > mid)
	{
		for (k = m; k <= high; k++)
		{
			temp[i] = array[k];
			i++;
		}
	}
	else
	{
		for (k = j; k <= mid; k++)
		{
			temp[i] = array[k];
			i++;
		}
	}
	for (k = low; k <= high; k++)
		array[k] = temp[k];
}


void mergesort(LLI array[], LLI low, LLI high)
{
	LLI mid;
	if (low < high)
	{
		mid = low + (high - low) / 2;

		#pragma omp parallel sections num_threads(2)
		{
			#pragma omp section
			mergesort(array, low, mid);
			#pragma omp section
			mergesort(array, mid + 1, high);
		}
		merge(array, low, mid, high);
	}
}

void mergesort_seq(LLI array[], LLI low, LLI high)
{
	LLI mid;
	if (low < high)
	{
		mid = low + (high - low) / 2;

		mergesort(array, low, mid);
		mergesort(array, mid + 1, high);
		merge(array, low, mid, high);
	}
}


int main()
{
	LLI i;
	for (LLI size = 100; size <= 1000000; size += 100000) {
		printf("\n--------------------------------------------------\n");
		printf("\nSize = %Ld \n", size);
		LLI *array_p = (LLI*)malloc(sizeof(LLI) * size);
		LLI *array_s = (LLI*)malloc(sizeof(LLI) * size);
		for (i = 0; i < size; i++)
		{
			array_p[i]  = rand() % size;
			array_s[i] = array_p[i];
		}

		double start = omp_get_wtime();
		mergesort(array_p, 0, size - 1);
		double end = omp_get_wtime();
		double start_s = omp_get_wtime();
		mergesort_seq(array_s, 0, size - 1);
		double end_s = omp_get_wtime();
		printf("Verification \n");
		int error = 0;
		for (i = 0; i < size; i++)
			error += array_s[i] - array_p[i];
		free(array_p);
		free(array_s);
		printf("Error = %d\n", error);
		printf("Parallel Time= %f\n", end - start);
		printf("Seqential Time= %f\n", end_s - start_s);

	}
	return 0;
}

/*
--------------------------------------------------

Size = 100
Verification
Error = 0
Parallel Time= 0.000346
Seqential Time= 0.000254

--------------------------------------------------

Size = 100100
Verification
Error = 0
Parallel Time= 0.079361
Seqential Time= 0.093147

--------------------------------------------------

Size = 200100
Verification
Error = 0
Parallel Time= 0.178580
Seqential Time= 0.154951

--------------------------------------------------

Size = 300100
Verification
Error = 0
Parallel Time= 0.249436
Seqential Time= 0.239965

--------------------------------------------------

Size = 400100
Verification
Error = 0
Parallel Time= 0.308426
Seqential Time= 0.319356

--------------------------------------------------

Size = 500100
Verification
Error = 0
Parallel Time= 0.384633
Seqential Time= 0.392506

--------------------------------------------------

Size = 600100
Verification
Error = 0
Parallel Time= 0.465667
Seqential Time= 0.461350

--------------------------------------------------

Size = 700100
Verification
Error = 0
Parallel Time= 0.513865
Seqential Time= 0.522730

--------------------------------------------------

Size = 800100
Verification
Error = 0
Parallel Time= 0.587613
Seqential Time= 0.595543

--------------------------------------------------

Size = 900100
Verification
Error = 0
Parallel Time= 0.654916
Seqential Time= 0.670216

*/