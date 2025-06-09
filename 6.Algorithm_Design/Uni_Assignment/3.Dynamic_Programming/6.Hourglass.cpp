#include <iostream>
#include <vector>
using namespace std;

int main(){
    int t; cin >> t;

    while(t--){
        int n, M, T; cin >> n >> M >> T;

        vector<bool> can_flip(T+1, false);
        for(int i=0; i<n; i++){
            int flip_time; cin >> flip_time;
            can_flip[flip_time] = true;
        }

        // Can we reach T with starting point i and j sand on top?
        vector<vector<bool>> dp(T+1, vector<bool> (M+1,false));

        for(int j=0; j<=M; j++)
            dp[T][j] = true;

        for(int i=T-1; i>=0; i--)
            for(int j=0; j<=M; j++){
                if(!can_flip[i]){
                    if(j == 0)
                        dp[i][j] = false;
                    else
                        dp[i][j] = dp[i+1][j-1];
                }
                else{
                    if((j-1 >=0 && dp[i+1][j-1]) || (M-j-1 >=0 && dp[i+1][M-j-1]))
                        dp[i][j] = true;
                    else
                        dp[i][j] = false;
                }
            }
        
        if(dp[0][M])
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }


    return 0;
}


