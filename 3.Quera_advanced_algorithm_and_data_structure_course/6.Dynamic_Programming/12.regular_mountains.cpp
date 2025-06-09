#include <iostream>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7, MAXN = 300 + 10;
int h[MAXN], sorted_h[MAXN], dp[MAXN][MAXN][MAXN];

int main(){
    int n; cin >> n;
    for(int i=0; i<n; i++)
        cin >> h[i];

    //Compress
    for(int i=0; i<n; i++){
        sorted_h[i] = h[i];
    }
    sort(sorted_h, sorted_h + n);
    int uniqueCnt = unique(sorted_h, sorted_h + n) - sorted_h;
    for(int i=0; i<n; i++)
        h[i] = lower_bound(sorted_h, sorted_h + uniqueCnt, h[i]) - sorted_h;

    //base cases
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            dp[i][i][j] = 1;
            dp[i][i+1][j] = (j > h[i]) ? 1 : 2;
        }

    //dp arr
    for(int k=n-1; k>=0; k--){
        for(int l=n-1; l>=0; l--){
            for(int r=l+2; r<=n; r++){
                dp[l][r][k] = dp[l][r-1][k] + dp[l+1][r][k] - dp[l+1][r-1][k];
                if(h[l] == h[r-1] && h[l] >= k)
                    dp[l][r][k] += dp[l+1][r-1][h[l]];
            }
        }
    }

    cout << dp[0][n][0] - 1 << endl;

    return 0;
}