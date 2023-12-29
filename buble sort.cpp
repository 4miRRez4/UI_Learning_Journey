#include <iostream>
using namespace std;

int main()
{
	int l;
	cin >> l;

    int A[l];
    for(int i=0; i<l; i++)
    {
        cin >> A[i];
    }

    int c = 0;
    while(c!=(l-1))
    {
        c = 0;
        for(int z =0; z<=(l-2); z++)
        {
            if(A[z] > A[z+1])
            {
                int temp = A[z];
                A[z] = A[z+1];
                A[z+1] = temp;
            }else
            {
                c++;
            }
        }
    }

	for(int j=0; j<l; j++)
	{
		cout << A[j] << " ";
	}

}
