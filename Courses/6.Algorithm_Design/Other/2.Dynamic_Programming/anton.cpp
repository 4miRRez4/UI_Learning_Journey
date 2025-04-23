#include <iostream>
#include <climits>
#include <cstring>
using namespace std;

const int MAX_SIZE = 50 + 10;
const int MAX_K = 1e4 + 100; 
int n;
int a[MAX_SIZE], b[MAX_SIZE], c[MAX_SIZE], v[MAX_SIZE];

int dp[2*MAX_K];
int min_01_knapsack(int k){
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    for(int i=0; i<n; i++){
        for(int j=k; j>=0; j--){
            int jm = max(0, j-v[i]);
            if(dp[jm] != -1 && (dp[j] == -1 || dp[jm] + c[i] <= dp[j]))
                dp[j] = dp[jm] + c[i];
        }
    }

    return dp[k];
}

int main(){
    int k; cin >> n >> k;

    for(int i=0; i<n; i++)
        cin >> a[i];

    for(int i=0; i<n; i++)
        cin >> b[i];

    for(int i=0; i<n; i++)
        cin >> c[i];
    
    for(int i=0; i<n; i++)
        v[i] = max(0, a[i]-1);
    int ans = -1;
    int tmp = min_01_knapsack(k);
    if(ans == -1 || (ans >= tmp && tmp != -1))
        ans = tmp;

    for(int i=0; i<n; i++)
        v[i] = max(0, b[i]-1);
    tmp = min_01_knapsack(k);
    if(ans == -1 || (ans >= tmp && tmp != -1))
        ans = tmp;

    for(int i=0; i<n; i++)
        v[i] = max(0, a[i] + b[i]);
    tmp = min_01_knapsack(2*k -1);
    if(ans == -1 || (ans >= tmp && tmp != -1))
        ans = tmp;
    
    cout << ans << endl;
    return 0;
}