#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	
	//getting numbers from input;
	int a[n];	
	int num;
	for(int i=0; i<n; i++)
	{
		cin >> num;
		a[i] = num;
	}

	//printing numbers backward;
	for(int j = (n-1); j>=0; j--)
	{
		cout << a[j] << " ";
	}


}
