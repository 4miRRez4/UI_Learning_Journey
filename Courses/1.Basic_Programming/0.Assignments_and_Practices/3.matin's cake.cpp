#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


int main()
{
    int n; cin >> n;
    vector<float> degrees;
    float x;
    for(int i=0; i<n; i++)
    {
        cin >> x;
        degrees.push_back(x);
    }
    sort(degrees.begin(),degrees.end());

    float maxDis = 0;
    for(int i=0; i<n-1;i++)
        if(degrees[i+1]-degrees[i] > maxDis)
            maxDis = degrees[i+1]-degrees[i];

    if(360-degrees[n-1] + degrees[0] > maxDis)
        maxDis = 360-degrees[n-1] + degrees[0];

    float percentage = (maxDis*100) /360;
    cout << percentage;
    return 0;
}