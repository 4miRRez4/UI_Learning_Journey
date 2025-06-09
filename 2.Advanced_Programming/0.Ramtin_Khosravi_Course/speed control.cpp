#include <iostream>
#include <vector>
using namespace std;

int main()
{
    long long int n, v; cin >> n >> v;
    vector<long long int> distances (n+1);
    distances[0] = 0;
    for(int i=1; i<n+1; i++)
    {
        cin >> distances[i];
    }
    vector<long long int> times(n);
    times[0] = 0;
    for(int i=1; i<n+1; i++)
    {
        cin >> times[i];
    }
    
    int passed = 0;
    for(int l=1; l<=n; l++)
        for(int s=0; s<n-l; s++)
        {
            long double vv =(distances[s]-distances[s+l]) /(times[s]-times[s+l]);
            if(vv > v)
                passed++;
        }
    
    cout << passed;

    return 0;
}