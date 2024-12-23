#include <iostream>
using namespace std;

typedef long long ll;

int main(){
    int rows, cols; cin >> rows >> cols;
    
    int nums[rows][cols];
    for(int r=0; r<rows; r++)
        for(int c=0; c<cols; c++)
            cin >> nums[r][c];

    ll max_rec_sum = -1e18;
    for(int left_c=0; left_c<cols; left_c++){
        ll row_sum[rows] = {};
        for(int right_c=left_c; right_c<cols; right_c++){

            for(int row=0; row<rows; row++)
                row_sum[row] += nums[row][right_c];
            
            ll curr_subset_sum=-1e18;
            ll max_row_sum=-1e18;
            for(int i=0; i<rows; i++){
                curr_subset_sum = max(row_sum[i], row_sum[i] + curr_subset_sum);
                max_row_sum = max(max_row_sum, curr_subset_sum);
            }
            
            max_rec_sum = max(max_rec_sum, max_row_sum);
        }
    }

    cout << max_rec_sum << endl;
    return 0;
}