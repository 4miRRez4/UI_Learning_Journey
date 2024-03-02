//we have n nuts and 2 players. in each round a player picks 1,2 or 3 nuts. winner is who picks last nuts.
#include <iostream>
using namespace std;


int main()
{
    int n;
    while(cin >> n)
    {
        if(n%4 == 0)
            cout << -1 << endl;
        else
            cout << 1 << endl;
    }
    return 0;
}