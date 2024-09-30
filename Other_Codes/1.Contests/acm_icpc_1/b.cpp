#include <iostream>
using namespace std;

int main()
{
    long start; cin >> start;
    cout << start;
    while(start != 1)
    {
        if(start %2 == 0)
            start/=2;
        else 
        {            
            start*=3;
            start++;
        }
        cout << " " << start;
    }


    return 0;
}