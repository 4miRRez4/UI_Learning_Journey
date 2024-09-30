#include<iostream>
using namespace std;

int main()
{
    int t; cin >> t;
    for(int i=0; i<t; i++)
    {
        int a,b; cin >> a >> b;
        if((a+b) %2 == 0)
        {
            cout << "Matine Tanha" << endl;
        }
        else 
            cout << "Pouyaye Hakim" << endl;
    }
    return 0;
}