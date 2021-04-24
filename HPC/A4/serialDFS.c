#include<stdio.h>
#include<stdlib.h>
#include<time.h>


void printInorder(int* arr,int start,int end)
{
	if(start > end) 
    return; 
  
  // print left subtree 
  printInorder(arr, start*2 + 1, end); 
  
  // print root 
  printf("%d\t", arr[start]); 
  
  // print right subtree 
  printInorder(arr, start*2 + 2, end); 
}


int main(int argc, char const *argv[])
{
	int N = 1024;
	int arr[N];
	int tree[N];
	int i;
	int turns = 1;

	int children =4;

	int store[children][N];
	
	clock_t  cpu_start = clock();
	for(;turns<=children;turns++)
	{
	int offset = (turns-1)*N;
	
	buildTree(arr,0,N,tree,0,offset,N);
	
	printInorder(tree,0,N-1);
	
	}
	clock_t cpu_finish = clock();
	

	
	printf("\ntime elapsed in traversing is = %d millisecinds\n",(cpu_finish - cpu_start) );

	return 0;
}



void buildTree(int* arr,int start,int end,int* tree,int k,int offset,int N)
{
	
	if(start<=end && k<=N-1){
	
	int mid = (end+start+1)/2;
	//printf(" k = %d and element = %d\n",k,arr[mid] );
	tree[k] = mid+offset;
	


	buildTree(arr,start,mid-1,tree, k*2+1,offset,N);
	buildTree(arr,mid+1,end,tree,k*2+2,offset,N);
}





	

}
