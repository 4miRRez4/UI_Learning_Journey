//comparing recursive and linear approach
#include <iostream>
#include <ctime>
using namespace std;

long recFib(long n)
{
    if(n <= 2)
        return 1;
    return recFib(n-1) + recFib(n-2);
}

long nonRecFib(long n)
{
    if(n <= 2)
        return 1;

    long a=1, b=1, c;
    for(int i=0; i<n-2; i++)
    {
        c = a+b;
        a =b;
        b =c;
    }
    return c;
}

int main()
{
    clock_t t;
    for (int n = 1; n < 42; n++) {
        cout << "n=" << n << '\t';
        
        t = clock();
        long f = nonRecFib(n);
        t = clock() - t;
        cout << "Non-Rec: " << 1000*t/CLOCKS_PER_SEC << "(ms)\t";

        t = clock();
        f = recFib(n);
        t = clock() - t;
        cout << "Rec: " << 1000*t/CLOCKS_PER_SEC << "(ms)\n";
    }
    return 0;
}