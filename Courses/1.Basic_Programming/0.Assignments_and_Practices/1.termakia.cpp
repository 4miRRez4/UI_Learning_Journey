#include <iostream>
using namespace std;

int main()
{
    string n; cin >> n;
    if(n.length() == 1)
        if(stoi(n)==1 || stoi(n)==2)
            cout << n;
        else
            cout << n[0]-'0'-1;
    else
    {
        int j=1;
        while(n[n.length()-j]-'0' == 0)
        {
            j++;
        }
        
        for(int i=0; i<n.length()-j; i++)
        {
            cout << n[i];
        }
        if(n.length() != j)
            cout << n[n.length()-j]-'0'-1;
        else if(n[n.length()-j]-'0'-1 != 0)
            cout << n[n.length()-j]-'0'-1;
        for(int i=0; i<j-1;i++)
            cout << 9;
    }
    return 0;

}