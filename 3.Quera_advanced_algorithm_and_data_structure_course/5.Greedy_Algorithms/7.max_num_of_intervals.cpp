#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

int main(){
    int n; cin >> n;
    pair<int, int> intervals[n];
    for(int i=0; i<n; i++){
        cin >> intervals[i].first >> intervals[i].second;
    }


    auto compFunc = [] (pair<int, int> a, pair<int, int> b) {return a.second < b.second; };
    sort(intervals, intervals+n, compFunc);

    int cnt=0, last_r = -1;
    for(int i=0; i<n; i++){
        if(last_r <= intervals[i].first){
            cnt++;
            last_r = intervals[i].second;
        }
    }

    cout << cnt << endl;
    return 0;
}