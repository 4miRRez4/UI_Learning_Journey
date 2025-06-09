#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, c; cin >> n;
    long long r; cin >> r;
    
    vector<int> prices(n,0);
    for(int i=0; i<n; i++){
        cin >> prices[i]; 
    }

    sort(prices.begin(), prices.end());

    int buy_cnt=0;
    for(int i=0; i<n ;i++){
        if(r >= prices[i]){
            r -= prices[i];
            buy_cnt++;
        }
    }
    
    cout << buy_cnt;
    return 0;
}