#include <iostream>
using namespace std;
const int MAX_SIZE = 100001;
const long long mod = 1000000007;
long long dp[MAX_SIZE]={};

int main(){
    dp[0] = dp[1] = dp[2] = 1;
    dp[3] = 2;
    for(int i=4; i<=MAX_SIZE; i++){
        long long tmp = dp[i-1] + dp[i-2] + dp[i-3] - dp[i-4];
        dp[i] = (tmp + mod) % mod;
    }

    int q,n; cin >> q;
    for(int i=0; i<q; i++){
        cin >> n;
        cout << dp[n] << endl;
    }


    return 0;
}