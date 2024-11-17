#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, c; cin >> n;
    long long r; cin >> r;
    
    vector<int> prices(n,0);
    for(int i=0; i<n; i++){
        cin >> prices[i];
    }
    
    int buy_cnt=0;
    while(r > 0){
        int min_price = prices[0];
        int min_ind = 0;
        
        for(int i=1; i<n; i++){
            if(prices[i] < min_price){
                min_price = prices[i];
                min_ind = i;
            }
        }

        if(min_price <= r){
            r -= min_price;
            prices.erase(prices.begin() + min_ind);
            buy_cnt++;
        }else
            break;
    }
    
    cout << buy_cnt;
    return 0;
}