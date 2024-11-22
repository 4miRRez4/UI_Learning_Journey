#include <iostream>
using namespace std;

const int MAXN = 1000 * 100 + 5;
const int MAXD = 1000 * 1000 + 5;

int main()//memoization
{
    int n, q, x;
    cin >> n >> q;
    
    int memo[MAXD]={};
    for (int i = 0; i < n; i++){
        cin >> x;
        memo[x-1]++;
    }

    for(int i=1; i<MAXD; i++){
        memo[i] += memo[i-1];
    }
    for (int i = 0; i < q; i++){
        cin >> x;
        cout << memo[x-2] << endl;
    }


        
    return 0;
}