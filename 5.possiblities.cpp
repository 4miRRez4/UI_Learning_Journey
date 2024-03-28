#include <iostream>
using namespace std;

void pos(string x)
{
    bool isThereQ = false;
    for(int i=0; i<x.length(); i++)
    {
        if(x[i] == '?')
        {
            isThereQ = true;
            x[i] ='1';
            pos(x);
            x[i] = '0';
            pos(x);
            break;
        }
    }
    if(!isThereQ)
        cout << x << endl;
}
int main()
{
    string x; cin >> x;
    pos(x);

    return 0;
}