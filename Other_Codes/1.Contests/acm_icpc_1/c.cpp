#include <iostream>
using namespace std;

int main()
{
    int n; cin >> n;
    string str; cin >> str;
    for(int i=0; i<n; i++)
    {
        if(str[i] == 'S' & str[n+i] == 'S')
        {
            cout << "NO";
            return 0;
        }
        if(str[i] == 'F' & str[n+i] == 'F')
        {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
    return 0;
}