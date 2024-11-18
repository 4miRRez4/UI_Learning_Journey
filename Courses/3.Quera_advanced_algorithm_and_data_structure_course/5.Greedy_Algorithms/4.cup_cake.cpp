#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int n, k; cin >> n >> k;
    int nums[n];
    for(int i=0; i<n; i++)
        cin >> nums[i];

    if(k == 1)
        cout << *max_element(nums, nums+n) << endl;
    else if(k == 2)
        cout << max(nums[0], nums[n-1]) << endl;
    else if(k >= 3)
        cout << *min_element(nums, nums+n) << endl;

    return 0;
}