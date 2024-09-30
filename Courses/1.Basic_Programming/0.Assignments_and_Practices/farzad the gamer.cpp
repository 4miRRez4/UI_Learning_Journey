#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int a[n][n];
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cin >> a[i][j];
        }
    }

    int det;
    int operation = n;
    switch(operation)
    {
        case 1:
            det = n;
            break;
        case 2:
            det = (a[0][0] * a[1][1]) -
            (a[0][1] * a[1][0]);
            break;
        case 3:
            det = (a[0][0]*((a[1][1]*a[2][2])-(a[1][2]*a[2][1])))-(a[0][1]*((a[1][0]*a[2][2])-(a[1][2]*a[2][0])))+(a[0][2]*((a[1][0]*a[2][1])-(a[2][0]*a[1][1])));
            break;

    }

    if(det%2 == 0)
    {
        cout << "Farzad";
    }else
    {
        cout << "Danial";
    }
}