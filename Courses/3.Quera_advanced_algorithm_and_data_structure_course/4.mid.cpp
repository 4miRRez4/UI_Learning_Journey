//finding the element of given array that we convert all elements to it with minimum cost
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main(){
    long long n;
    cin >> n;
    vector<long long> nums;
    long long t;
    for(long long i=0; i<n; i++){
        cin >> t;
        nums.push_back(t);
    }
    sort(nums.begin(), nums.end());

    long long mid = nums[(n-1)/2];
    cout << mid << " ";

    long long cost = 0;
    for(long long i=0; i<n; i++)
        cost += abs(mid - nums[i]);
    cout << cost << endl;

    return 0;
}