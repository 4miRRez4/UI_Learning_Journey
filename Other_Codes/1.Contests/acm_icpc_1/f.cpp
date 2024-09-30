#include <iostream>
using namespace std;

int main()
{
    int cm, gm, cb, gb, rate;cin >> cm >> gm >> cb >> gb >> rate;
    if(cm >= cb)
    {
        cm -= cb;
        gm += cm/rate;
        if(gm >= gb)
        {
            cout << "Yes";
            return 0;
        }
    }
    else if(gm >= gb)
    {
        gm -= gb;
        cm += gm*rate;
        if(cm >= cb)
        {
            cout << "Yes";
            return 0;
        }

    }
    cout << "No";
    return 0;
}