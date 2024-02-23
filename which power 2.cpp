#include <iostream>
using namespace std;


int main()
{
    double n; cin >> n;

    int i=0;
    while(n>2)
    {
        i++;
        n/=2;
    }
    i++;

    long long out =1;
    for(int j=0; j<i; j++)
    {
        out *= 2;
    }
    cout << out;


    return 0;
}