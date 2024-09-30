#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	
	//making array of numbers;
	int a[n];
	int num;
	for(int i = 0; i<n; i++)
	{
		cin >> num;
		a[i] = num;
	}

	//deleting element with index k from array;
	int k;
	cin >> k;

	for(int j = k; j<(n-1); j++)
	{
		a[j] = a[j+1];
	}


	//printing shifted array;
	for(int z = 0; z<(n-1); z++)
	{
		cout << a[z] << " ";

	}
}
