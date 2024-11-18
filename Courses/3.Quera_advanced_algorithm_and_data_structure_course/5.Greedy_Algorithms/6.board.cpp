#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, c; cin >> n >> c;
    int nums[n];
    for(int i=0; i<n; i++)
        cin >> nums[i];
    
    auto comp = [c](int a, int b) { return a-c > b-c;};

    sort(nums, nums+n, comp);

    int d;
    for(int i=0; i<n; i++){
        d = min(c, max(0, nums[i]-c));
        c -= d;
    }
    cout << c << endl;
    return 0;
}