//calculating a[0]*a[1] + a[2]/a[3] + …  recursively
#include <iostream>
#include <vector>
using namespace std;

int pattern(vector<int> a, int p =0, int where=0)
{
    if(where == a.size()-1)
        return a[where];
    else if(where == a.size())
        return 0;
    else
        return (p%2 == 0 ? a[where]*a[where+1] : a[where]/a[where+1]) + pattern(a, p+1, where+2);
}

int main()
{
    int n, tmp; cin>>n;
    vector<int> a;
    for(int i=0; i<n; i++)
    {
        cin >>tmp;
        a.push_back(tmp);
    }

    cout << pattern(a);

    return 0;
}