#include <iostream>
#include <algorithm>
using namespace std;

int upperBound_nonRec(const long long arr[], int n, long long x){
    int ub_ind = n;

    int left = 0;
    int right = n-1;

    while(left <= right){
        int mid = (right+left)/2;

        if(arr[mid] > x){
            ub_ind = mid;
            right = mid-1;
        }else{
            left = mid+1;
        }
    }

    return ub_ind;
}

int firstLess_nonRec(long long arr[], int n, long long x){
    int lb_ind = n;
    
    int left = 0;
    int right = n-1;
    while(left <= right){
        int mid = (right+mid)/2;

        if(arr[mid] < x){
            lb_ind = mid;
            left = mid+1;
        }else{
            right = mid-1;
        }
    }

    return lb_ind;
}

int main(){
    int t; cin >> t;
    while(t--){
        int n; long long k; 
        cin >> n >> k;

        int arr[n];
        for(int i=0; i<n; i++)
            cin >> arr[i];

        long long prefix_sum[n+1];
        prefix_sum[0] = 0;
        for(int i=0; i<n; i++)
            prefix_sum[i+1] = arr[i] + prefix_sum[i];

        sort(prefix_sum, prefix_sum + n + 1);

        int count = 0;
        // |ps[i] - ps[j]| > k
        for(int j=1; j<n+1; j++){
            // ps[i] > k + ps[j]
            int i1 = upperBound_nonRec(prefix_sum, n+1, k+prefix_sum[j]);
            // ps[i] < ps[j] - k
            int i2 = firstLess_nonRec(prefix_sum, n+1, prefix_sum[j]-k);

            int i = min(i1, i2);
            if(i<=n){
                count += (n-i);
            }
        }
        cout << count << endl;
    }


    return 0;
}