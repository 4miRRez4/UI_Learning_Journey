#include <iostream>
using namespace std;

const int MOD = 1e9 + 7;
int const MAX_SIZE = 2001;
int dp[MAX_SIZE][MAX_SIZE];

int main(){
    /*
    D(i,j): combination of j thing from i thing
    Base: D(i<j) = 0, D(j=0) = 1, D(i=j) = 1
    recursive relation: D(i, j)= D(i-1, j-1) + D(i-1, j). pick or don't pick.
    Bottom up filling.
    */
    
    for(int i=0; i<MAX_SIZE; i++){
        dp[i][0] = 1;
        dp[i][i] = 1;
    }


    for(int i=2; i<MAX_SIZE; i++){
        for(int j = 1; j<i; j++){
            dp[i][j] = (dp[i-1][j-1] + dp[i-1][j]) % MOD;
        }
    }

    int q; cin >> q;
    while(q--){
        int n, r; cin >> n >> r;
        if(r > n)
            cout << 0 << endl;
        else
            cout << dp[n][r] << endl;
    }

    return 0;
}