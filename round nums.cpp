//rounding given number amount(until power of p)
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int amount, p, rounded;
    while(cin >> amount >> p)
    { 
        int precision = pow(10, p);
        if(precision == 1)
        {
            rounded = amount;
        }
        else if(amount%precision < precision/2)
        {
            rounded = (amount/=precision)*precision;
        }else //round up
        {
            rounded = ((amount/=precision)+1)*precision;
        }

        cout << rounded << endl;
    }
    return 0;
}