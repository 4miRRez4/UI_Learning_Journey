//reversing an given int (both recursive and non-recursive approach)
#include <iostream>
using namespace std;

int non_rec(int n)
{
    int reversed=0, place =1, digit;
    while(n>0)
    {
        digit = n%10;
        reversed = reversed*10 + digit;
        place *= 10;
        n /= 10;
    }
    return reversed;
}

int rec(int n, int reversed=0)
{
    if(n<10)
        return n + reversed;
    return rec(n/10, (reversed+ n%10) * 10);
}

int main()
{
    int n; cin>>n;
    cout << non_rec(n) << endl;
    cout << rec(n) << endl;
    return 0;
}