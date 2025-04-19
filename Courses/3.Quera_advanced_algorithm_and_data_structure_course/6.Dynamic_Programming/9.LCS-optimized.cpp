#include <iostream>
#include <algorithm>
using namespace std;


int main(){
    string a, b; cin >> a >> b;
    int n = a.length();
    int m = b.length();

    int parent[n+1][m+1];

    int dp[2][m+1];
    for(int j=0; j<=m; j++){
        dp[0][j] = 0;
        parent[0][j] = 1;
    }
    
    for(int i=1; i<=n; i++){
        dp[i%2][0] = 0;
        parent[i][0] = 2;

        for(int j=1; j<=m; j++){
            if(a[i-1] == b[j-1]){
                dp[i%2][j] = dp[(i-1)%2][j-1] + 1;
                parent[i][j] = 0;
            }
            else{
                if(dp[i%2][j-1] > dp[(i-1)%2][j]){
                    dp[i%2][j] = dp[i%2][j-1];
                    parent[i][j] = 1;
                }
                else{
                    dp[i%2][j] = dp[(i-1)%2][j];
                    parent[i][j] = 2;
                }
            }
        }
    }

    cout << dp[n%2][m] << endl;

    string common = "";
    int i=n, j=m;
    while(i > 0 && j > 0){
        switch(parent[i][j]){
            case 0:{
                common += a[i-1];
                i = i-1;
                j = j-1;

                break;
            }
            case 1:{
                j = j-1;
                break;
            }
            case 2:{
                i = i-1;
                break;
            }
        }
    }

    reverse(common.begin(), common.end());
    cout << common << endl;

    return 0;
}