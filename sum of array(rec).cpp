//calculating a[0] - a[1] + a[2] - … ± a[n-1] recursively
#include <iostream>
#include <vector>
using namespace std;

int pattern_rec(vector<int> a, int where=0)
{
    if(where == a.size())
        return 0;
    return (where%2 == 0 ? a[where] : -a[where]) + pattern_rec(a, ++where); 
}

int main()
{
    vector<int> a;
    int n,tmp; cin >> n;
    for(int i=0;i<n;i++)
    {
        cin >> tmp;
        a.push_back(tmp);
    }

    cout << pattern_rec(a);



    return 0;
}