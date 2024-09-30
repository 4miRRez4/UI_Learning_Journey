#include <iostream>
using namespace std;

int main()
{
    int n; cin >> n;
    for (int i=0; i<n; i++)
    {
        int t; cin >> t;
        if(t%3 == 0)
        {
            cout << "Second" << endl;
        }else
            cout << "First" << endl;
    }


    return 0;
}