#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

int main() {
    int n,k; cin >> n >> k;
    
    pair<int, int> fruits[n];
    for(int i=0; i<n; i++){
        cin >> fruits[i].second >> fruits[i].first;
    }
    
    sort(fruits, fruits+n);
    
    long long energy = k;
    for(int i=0; i<n; i++){
        if(fruits[i].first <= energy && fruits[i].second > fruits[i].first)
            energy += fruits[i].second - fruits[i].first;
    }
    
    cout << energy << endl;
    return 0;
}