#include <iostream>
using namespace std;

void shift(int nums[], int index, int length)
{
	for(int k = index; k<(length-1); k++)
	{
		nums[k] = nums[k+1];
	}
}

int main()
{
	int l;
	cin >> l;

	int imposter_i;
	cin >> imposter_i;

	//making the array;
	int nums[l];
	for(int i=0; i<l; i++)
	{
		cin >> nums[i];
	}

	//deleting the imposter value;
	int imposter = nums[imposter_i];
	for(int j=0; j<l; j++)
	{
		if(nums[j] == imposter)
		{
			shift(nums, j, l);
			j--;
			l--;
		}
	}

	for(int z = 0; z<l; z++)
	{
		cout << nums[z] << " ";
	}



}
