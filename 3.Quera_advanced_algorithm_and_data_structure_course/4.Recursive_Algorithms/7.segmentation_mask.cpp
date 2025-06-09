#include <iostream>
using namespace std;

long long check_subsets(long long nums[], int n){
    long long min_differ = 1e19;
    for(int mask=0; mask < (1<<n) /2; mask++){
        long long ones = 0, zeros =0;
        for(int i=n-1; i>=0; i--){
            if(mask & 1<<i){
                ones += nums[i];
            }else{
                zeros += nums[i];
            }
        }

        long long curr_differ = abs(ones - zeros);
        if(curr_differ < min_differ)
            min_differ = curr_differ;
    }
    return min_differ;
}

int main(){
    int n; cin >> n;
    long long nums[n];
    for(int i=0; i<n ;i++)
        cin >> nums[i];

    cout << check_subsets(nums, n) << endl;
    
    return 0;
}