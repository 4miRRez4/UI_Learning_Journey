#include <iostream>
using namespace std;

void swap(int a, int b)
{
	temp = A[a];
	A[a] = A[b];
	A[b] = temp;
}

void quick_sort(int A[])
{
	int pivot = l-1;
	int j = -1;
	for(int i = 0; i<pivot; i++)
	{
		if(A[i] < A[pivot])
		{
			j++;
			swap(i, j);

		}
	}
	j++;
	swap(pivot, j);
	//make it recursive...
}

int main()
{
	int l;
	cin >> l;

	int nums[l];
	for(int i = 0; i<l; i++)
	{
		cin >> nums[i];
	}
}
