//https://quera.org/contest/assignments/67462/problems/233370
#include <iostream>

using namespace std;

int main()
{
    long long n, d;
    cin >> n;
    int flag1 = 1, flag2 = 0;
    long long nam1 = 0, nam2 = 0;
    int p = 1;
    while (n > 0)
    {
        d = n % 2;
        n /= 2;
        if (d == 1)
        {
            nam1 += flag1 * p;
            nam2 += flag2 * p;
            flag1 = (flag1 == 1) ? 0 : 1;
            flag2 = (flag2 == 1) ? 0 : 1;
        }
        p *= 2;
    }
    cout << nam1 << " " << nam2 << endl;
    return 0;
}