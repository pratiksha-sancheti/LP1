#include<omp.h>
#include<mpi/mpi.h>
#include<stdio.h>
#include<math.h>
#include<iostream>
typedef long long int LLI;
using namespace std;
void binarySearchP(int *arr, int start, int end, int key, int rank)
{
	while (start <= end)
	{
		int mid = (start + end) / 2;
		if (arr[mid] == key)
		{
			cout << "\nElement is  Found by processor " << rank << " .\n";
			return;
		}
		else if (arr[mid] < key)
		{
			start = mid + 1;
		}
		else
		{
			end = mid - 1;
		}
	}
	printf("Element not Found\n");
}
int main(int argc, char** argv) {
	int n = 4000;
	int *arr = new int[n];
	double start, end;
	for (int i = 0; i < n; i++)
	{
		arr[i] = i + 1;
	}
	int key = n + 2; //element to search
	printf("\n--------------------------------------Parallel Search--------------------------------\n");

	MPI_Init(&argc, &argv);
	int rank, size;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	cout << "\nProcessor rank: " << rank << "\nSize : " << size << endl;
	int blocks = 2;
	int blockSize = n / blocks;


	if (rank == 0)
	{
		double start = MPI_Wtime();
		binarySearchP(arr, rank * blockSize, (rank + 1)*blockSize - 1, key, rank);
		double end = MPI_Wtime();
		cout << "\nExecution time of Processor " << rank << " is " << (end - start) * 1000 << endl;
	}
	else if (rank == 1)
	{
		double start = MPI_Wtime();
		binarySearchP(arr, rank * blockSize, (rank + 1)*blockSize - 1, key, rank);
		double end = MPI_Wtime();
		cout << "\nExecution time of Processor " << rank << " is " << (end - start) * 1000 << endl;
	}
	else if (rank == 2)
	{
		double start = MPI_Wtime();
		binarySearchP(arr, rank * blockSize, (rank + 1)*blockSize - 1, key, rank);
		double end = MPI_Wtime();
		cout << "\nExecution time of Processor " << rank << " is " << (end - start) * 1000 << endl;
	}

	MPI_Finalize();

	return 0;

}

/*OP

Key to search = 100000
Time for parallel = 2.83999e-07
Element does not present in the list
not found in time 4.07999e-07


*/