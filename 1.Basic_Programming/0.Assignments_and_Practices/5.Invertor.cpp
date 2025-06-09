#include <iostream>

using namespace std;

int main()
{
    int num;
    cin >> num;

    int tmp = num;
    int inverted = 0;
    while (tmp > 0)
    {
        int digit = tmp%10;
        inverted = (inverted*10) + digit;
        tmp = (tmp-digit)/10;
    }

    if (num == inverted)
    {
        cout << "Yes";
    }else
    {
        cout << "No";
    }
}

