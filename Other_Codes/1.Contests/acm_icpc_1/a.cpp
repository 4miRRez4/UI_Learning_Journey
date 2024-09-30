#include <iostream>
using namespace std;

int main()
{
    int n; cin >> n;
    int place=1;
    for(int i=0;i<n;i++)
    {
        int j, k; cin >> j >> k;
        if(place == j)
            place = k;
        else if(place == k)
            place = j;
    }
    cout << place;

    return 0;
}