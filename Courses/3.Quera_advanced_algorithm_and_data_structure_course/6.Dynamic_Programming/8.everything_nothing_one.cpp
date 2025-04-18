#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;


int main(){
    int n, s; cin >> n >> s;

    vector<int> size_of_pack(n, 0);
    vector<int> min_of_pack(n, INT_MAX);
    vector<int> sum_of_pack(n, 0);

    for(int i=0; i<n; i++){
        cin >> size_of_pack[i];
        int p;
        for(int j=0; j<size_of_pack[i]; j++){
            cin >> p;
            min_of_pack[i] = min(min_of_pack[i], p);
            sum_of_pack[i] += p;
        }
    }

    int dp[n+1][s+1];
    for(int i=0; i<=n; i++){
        dp[i][0] = 0;
    }
    for(int j=0; j<=s; j++)
        dp[0][j] = 0;

    for(int i=1; i<=n; i++){
        for(int j=1; j<=s; j++){
            dp[i][j] = dp[i-1][j];

            if(min_of_pack[i-1] <= j)
                dp[i][j] = max(dp[i][j], dp[i-1][j - min_of_pack[i-1]] + 1);
            
            if(sum_of_pack[i-1] <= j)
                dp[i][j] = max(dp[i][j], dp[i-1][j - sum_of_pack[i-1]] + size_of_pack[i-1]);
        }
    }

    cout << dp[n][s] << endl;

    string decisions = "";
    int i=n, j=s;
    while(i > 0){
        if(dp[i][j] == dp[i-1][j]){
            decisions += "0";
            i = i-1;
        }
        else if(dp[i][j] == dp[i-1][j - min_of_pack[i-1]] + 1){
            decisions += "1";
            i = i-1;
            j = j - min_of_pack[i-1];
        }else{
            decisions += "2";
            i = i-1;
            j = j - size_of_pack[i-1];
        }
    }

    reverse(decisions.begin(), decisions.end());
    cout << decisions << endl;
    return 0;
}