#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1e4 + 100;
int arr[MAXN], dp[MAXN], par[MAXN];

int main(){
    int n; cin >> n;
    for(int i=0; i<n; i++) 
        cin >> arr[i];

    int max_idx = 0;
    for(int i=0; i<n; i++){
        dp[i] = 1;
        par[i] = i;
        for(int j=0; j<i; j++){
            if(arr[i] > arr[j] && dp[i] < dp[j]+1){
                dp[i] = dp[j] + 1;
                par[i] = j;
            }
        }

        if(dp[i] > dp[max_idx])
            max_idx = i;
    }

    cout << dp[max_idx] << endl;

    string ans = "";
    while(max_idx != par[max_idx]){
        ans += to_string(arr[max_idx]) + " ";
        max_idx = par[max_idx];
    }
    ans += to_string(arr[max_idx]);

    reverse(ans.begin(), ans.end());
    cout << ans;

    return 0;
}