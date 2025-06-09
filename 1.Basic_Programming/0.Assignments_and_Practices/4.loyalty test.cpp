#include <iostream>

using namespace std;

int main()
{
    long num;
    cin >> num;

    if ((num%7 == 0) || (num%4 == 0))
    {
        cout << "Loyalty";
        exit(0);
    }

    while (num > 0)
    {
        int digit = num%10;
        if ((digit != 7) && (digit != 4))
        {
            cout << "Disloyalty";
            exit(0);
        }
        num = (num - digit) /10;

    }
    cout << "Loyalty";
    


}