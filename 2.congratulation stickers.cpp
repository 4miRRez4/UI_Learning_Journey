#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    char scores[n];
    

    for ( int i = 0; i<n; i++)
    {
        cin >> scores[i];
        int num = scores[i] -48;

        if((num <= 3))
        {
            for (int j = 0; j < num; j++)
            {
                cout << "*";
            }
            cout << endl;
        }else
        {
            cout << "*" << endl;
        }
    }



}