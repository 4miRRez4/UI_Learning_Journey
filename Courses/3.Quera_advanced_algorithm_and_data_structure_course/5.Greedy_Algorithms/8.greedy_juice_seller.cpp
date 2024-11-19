#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

typedef long double ld;

int main(){
    int n; ld capacity; cin >> n >> capacity;

    pair<ld, ld> juices[n]; //h_i, v_i
    for(int i=0; i<n; i++)
        cin >> juices[i].first >> juices[i].second;

    auto compFunc = [] (pair<ld, ld> a, pair<ld, ld> b) { return a.first/a.second > b.first/b.second;};
    sort(juices, juices+n, compFunc);

    
    ld max_happiness = 0;
    for(int i=0; i<n; i++){
        if(capacity >= juices[i].second){
            max_happiness += juices[i].first;
            capacity -= juices[i].second;
        }
        else{
            ld proportion = capacity/juices[i].second;
            max_happiness += juices[i].first * proportion;
            capacity = 0;
            break;
        }   
    }

    cout << setprecision(4) << fixed << max_happiness << endl;
    return 0;
}