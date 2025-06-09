//sum of digits (both recursive and non-recursive approach)
#include <iostream>
using namespace std;

int non_rec(int n)
{
    int sum=0, digit;
    while(n>0)
    {
        digit = n%10;
        sum += digit;
        n/=10;
    }
    return sum;
}

int rec(int n)
{
    if(n<10)
        return n;

    return n%10 + rec(n/10);
}

int main()
{
    int n; cin >> n;
    cout << non_rec(n);

    cout << rec(n);

    return 0;
}