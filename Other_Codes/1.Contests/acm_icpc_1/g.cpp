#include <iostream>
#include <vector>
using namespace std;


int main()
{
    int n, tmp, operations=0; cin >> n;
    vector<int> a;
    for(int i=0; i<n; i++)
    {
        cin >> tmp;
        a.push_back(tmp);
    }
    for(int i=1; i<n; i++)
    {
        if(a[i] <= a[i-1])
        {
            operations += (a[i-1] +1)-a[i];
            a[i] = a[i-1]+1;
        }
    }
    cout << operations;
    return 0;
}