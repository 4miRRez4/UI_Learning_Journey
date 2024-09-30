#include <iostream>
using namespace std;

int main()
{
    long long int n; cin >> n;
    for(long long int k=1; k<=n; k++)
    {
        long long int total = (((k*k)*(k*k -1)) /2); //all places for first one and all minus one for second one;
        long long int threatned = 2*2*(k-1)*(k-2); //all 2*3 and 3*2 in board<(n-2)(n-1) + (n-1)(n-2)>, that have two threatned placement;
        cout << total - threatned << endl;
    }

    return 0;
}