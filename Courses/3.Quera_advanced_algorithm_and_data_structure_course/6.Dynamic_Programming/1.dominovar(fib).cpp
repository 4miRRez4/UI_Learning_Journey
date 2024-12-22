#include <iostream>
using namespace std;

long long dp[10000]={};

int main() {
    long long mod = 1e9 + 7;
    dp[0] = 1; dp[1] = 2;
    for(int i=2; i<10000; i++)
        dp[i] = (dp[i-1] + dp[i-2]) % mod;
        
    int n; cin >> n;
    cout << dp[n-1] << endl;
    return 0;
}