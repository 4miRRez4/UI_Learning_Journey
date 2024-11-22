#include <iostream>
#include <algorithm>
using namespace std;


int main(){
    long long n, k;
    cin >> n >> k;

    long long firstSeq[n];
    for(long long i=0; i<n; i++)
        cin >> firstSeq[i];

    long long cost, minCost=10000000;
    for(long long start = firstSeq[0] - (n-1)*k -1; start <= firstSeq[n-1] + 1; start++){
        cost = 0;
        for(long long i=0; i<n ; i++)
            cost += abs(firstSeq[i] - (start + i*k));

        if(cost < minCost)
            minCost = cost;
    }

    cout << minCost << endl;



    return 0;
}
