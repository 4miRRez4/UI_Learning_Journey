#include <iostream>
#include <set>
using namespace std;


int main(){
    int q, k, x; cin >> k >> q;

    set<int> landings;
    for(int i=0; i<q; i++){
        cin >> x;
        set<int>::iterator it = landings.lower_bound(x);

        bool can=true;
        if((it != landings.end() && *it - k < x) || (it != landings.begin() && *(--it) + k > x))
            can = false;

        if(can){
            cout << "Permission Granted!" << endl;
            landings.insert(x);
        }else
            cout << "Permission Denied!" << endl;
    }



    return 0;
}