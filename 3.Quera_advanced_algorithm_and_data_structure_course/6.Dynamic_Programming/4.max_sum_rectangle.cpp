#include <iostream>
using namespace std;

typedef long long ll;

const int MAX_SIZE = 500 + 10;
const ll INF = 1e18;
ll dp[MAX_SIZE];

int main(){
    int rows, cols; cin >> rows >> cols;
    
    int nums[MAX_SIZE][MAX_SIZE];
    for(int r=0; r<rows; r++)
        for(int c=0; c<cols; c++)
            cin >> nums[r][c];

    ll max_rec_sum = -INF;
    for(int left_c=0; left_c<cols; left_c++){
        ll row_sum[rows] = {};
        for(int right_c=left_c; right_c<cols; right_c++){

            for(int row=0; row<rows; row++)
                row_sum[row] += nums[row][right_c];
            
            dp[0] = 0;
            for(int i=0; i<rows; i++){
                dp[i+1] = max(row_sum[i], row_sum[i] + dp[i]);
                max_rec_sum = max(max_rec_sum, dp[i+1]);
            }
        }
    }

    cout << max_rec_sum << endl;
    return 0;
}