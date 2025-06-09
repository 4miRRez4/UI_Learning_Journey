//https://quera.org/problemset/9722
#include <iostream>
#include <cmath>
using namespace std;

bool isPrimitive(int n)
{
    if(n < 2)
        return false;
    else if (n == 2)
        return true;
    else if (n%2 == 0)
        return false;
    
    for(int i=3; i<= sqrt(n); i++)
    {
        if(n%i == 0) return false;
    }

    return true;
}

bool isHard(int n)
{
    while(n>0)
    {
        if(!isPrimitive(n))
            return false;
        n/=10;
    }
    return true;
}

int main()
{
    int numberOfDigits; cin >> numberOfDigits;
    int upperFence = pow(10,numberOfDigits);
    for(int i=pow(10,numberOfDigits-1); i<upperFence; i++)
    {
        if(isHard(i))
        {
            cout << i << endl;
        }
    }

    return 0;
}