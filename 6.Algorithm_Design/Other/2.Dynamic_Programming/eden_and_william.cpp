#include <iostream>
using namespace std;

const int MAXN = 2000;
long long court[MAXN][MAXN], dp_eden_to_common[MAXN][MAXN], dp_eden_to_target[MAXN][MAXN], dp_will_to_common[MAXN][MAXN], dp_will_to_target[MAXN][MAXN];

int main(){
    int n, m; cin >> n >> m;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> court[i][j];

    //initialize 4 dp arrays
    //max coin from (0,0) with moves right and down.
    dp_eden_to_common[0][0] = court[0][0];
    for(int i=1; i<n; i++)
        dp_eden_to_common[i][0] = dp_eden_to_common[i-1][0] + court[i][0];
    for(int j=1; j<m; j++)
        dp_eden_to_common[0][j] = dp_eden_to_common[0][j-1] + court[0][j];

    for(int i=1; i<n; i++)
        for(int j=1; j<m; j++)
            dp_eden_to_common[i][j] = max(dp_eden_to_common[i-1][j], dp_eden_to_common[i][j-1]) + court[i][j];
    
    //max coin from (n-1, 0) with moves right and up.
    dp_will_to_common[n-1][0] = court[n-1][0];
    for(int i=n-2; i>=0; i--)
        dp_will_to_common[i][0] = dp_will_to_common[i+1][0] + court[i][0];
    for(int j=1; j<m; j++)
        dp_will_to_common[n-1][j] = dp_will_to_common[n-1][j-1] + court[n-1][j];

    for(int i=n-2; i>=0; i--)
        for(int j=1; j<m; j++)
            dp_will_to_common[i][j] = max(dp_will_to_common[i+1][j], dp_will_to_common[i][j-1]) + court[i][j];

    //max coin to (n-1, m-1) with moves right and down.(calculate it backward)
    dp_eden_to_target[n-1][m-1] = court[n-1][m-1];
    for(int i=n-2; i>=0; i--)
        dp_eden_to_target[i][m-1] = dp_eden_to_common[i+1][m-1] + court[i][m-1];
    for(int j=m-2; j>=0; j--)
        dp_eden_to_target[n-1][j] = dp_eden_to_target[n-1][j-1] + court[n-1][j];

    for(int i=n-2; i>=0; i--)
        for(int j=m-2; j>=0; j--)
            dp_eden_to_target[i][j] = max(dp_eden_to_target[i][j+1], dp_eden_to_target[i+1][j]) + court[i][j];
    
    //max coin to (0, m-1) with moves right and up.(calculate it backward)
    dp_will_to_target[0][m-1] = court[0][m-1];
    for(int i=1; i<n; i++)
        dp_will_to_target[i][m-1] = dp_will_to_target[i-1][m-1] + court[i][m-1];
    for(int j=m-2; j>=0; j--)
        dp_will_to_target[0][j] = dp_will_to_target[0][j+1] + court[0][j];
    
    for(int i=1; i<n; i++)
        for(int j=n-2; j>=0; j--)
            dp_will_to_target[i][j] = max(dp_will_to_target[i][j+1], dp_will_to_target[i-1][j]) + court[i][j];

    //max coin with specific rules
    long long max_coin = 0;
    for(int i=1; i<n-1; i++)
        for(int j=1; j<m-1; j++){
            max_coin = max(max_coin, dp_eden_to_common[i-1][j] + dp_eden_to_target[i+1][j]
                                    + dp_will_to_common[i][j-1] + dp_will_to_target[i][j+1] + court[i][j]);
            
            max_coin = max(max_coin, dp_eden_to_common[i][j-1] + dp_eden_to_target[i][j+1] 
                                    + dp_will_to_common[i+1][j] + dp_will_to_target[i-1][j] + court[i][j]);
        }

    cout << max_coin << endl;

   return 0;
}