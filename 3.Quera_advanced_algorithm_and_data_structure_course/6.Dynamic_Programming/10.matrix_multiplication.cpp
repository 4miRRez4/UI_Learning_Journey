#include <iostream>
#include <climits>
using namespace std;

const int MAXN = 300 + 10;
int a[MAXN], dp[MAXN][MAXN];

int main(){
    int n; cin >> n;
    for(int i=0; i<n+1; i++)
        cin >> a[i];

    for(int i=0; i<n+1; i++){
        dp[i][i] = 0;
    }

    for(int l=2; l<n+1; l++){
        for(int i=0; i<n-l+1; i++){
            int j = i + l;
            dp[i][j] = INT_MAX;

            for(int k=i+1; k<j; k++)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + a[i] * a[k] * a[j]);
        }
    }


    cout << dp[0][n] << endl;
    return 0;
}