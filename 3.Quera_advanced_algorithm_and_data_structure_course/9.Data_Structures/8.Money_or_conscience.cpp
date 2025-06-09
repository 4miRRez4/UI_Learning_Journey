#include <iostream>
#include <set>
using namespace std;

int main(){
    int q, k, w, done=0; cin >> q;

    multiset<int> dead_lines;
    for(int day=1; day<=q; day++){
        cin >> k;
        for(int j=0; j<k; j++){
            cin >> w;
            dead_lines.insert(w + day -1);
        }
        
        while(!dead_lines.empty() && *dead_lines.begin() < day)
            dead_lines.erase(dead_lines.begin());
            
        if(!dead_lines.empty()){
            done++;
            dead_lines.erase(dead_lines.begin());
        }
    }

    cout << done << endl;

    return 0;
}