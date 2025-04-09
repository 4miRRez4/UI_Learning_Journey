#include <iostream>
#include <climits>
using namespace std;

int max_crossing_sum(int* arr, int l, int mid, int r){
    int left_sum = INT_MIN;
    int curr_sum = 0;
    for(int i=mid; i >= l; i--){
        curr_sum += arr[i];
        left_sum = max(left_sum, curr_sum);
    }

    int right_sum = INT_MIN;
    curr_sum=0;
    for(int i=mid+1; i <= r; i++){
        curr_sum += arr[i];
        right_sum = max(right_sum, curr_sum);
    }

    return left_sum + right_sum;
}

int max_subarray_sum(int* arr, int l, int r){
    if(l == r)
        return arr[l];
    
    int mid_ind = l + (r-l)/2;
    int left_max = max_subarray_sum(arr, l, mid_ind);
    int right_max = max_subarray_sum(arr, mid_ind+1, r);

    int crossing_max = max_crossing_sum(arr, l, mid_ind, r);

    return max(max(left_max, right_max), crossing_max);
}

int main(){
    int n; cin >> n;
    int arr[n];
    for(int i=0; i<n; i++)
        cin >> arr[i];

    cout << max_subarray_sum(arr, 0, n-1) << endl;


    return 0;
}