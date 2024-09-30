#include <iostream>
using namespace std;

int main()
{
    int angosht, dast, a, b; cin >> angosht >> dast >> a >> b;
    if(a+b != 0)
        cout << (((a+b)%(angosht*dast) == 0) ? angosht*dast:(a+b)%(angosht*dast));
    else
        cout << 0;
    return 0;
}