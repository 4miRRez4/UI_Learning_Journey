#include <iostream>
using namespace std;

int main()
{
    int lines;
    cin >> lines;

    //1.2d array method:

    int A[lines][lines];
    //iterating on each line;
    for(int line = 1; line<=lines; line++)
    {
        //iterating on each element in that line;
        for(int i = 0; i<line; i++)
        {
            if(i==0 || i==line-1)
            {
                A[line][i] = 1;
                cout << A[line][i] << " ";
            }else
            {
                A[line][i] = A[line-1][i-1] + A[line-1][i];
                cout << A[line][i] << " ";
            }
        }
        cout << endl;
    }




    //2.mathmatic method:

    // for(int line = 1; line <= lines; line++)
    // {
 
    //     int val = 1;
    //     for(int i = 1; i <= line; i++)
    //     {
    //         cout<<val<<" ";
             
    //         val = val * (line - i)/i;
    //     }
    //     cout<<endl;
    // }

}