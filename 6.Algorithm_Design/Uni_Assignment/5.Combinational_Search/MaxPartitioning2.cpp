#include <iostream>
using namespace std;

int max_parts = 0;

void BT(int lvl, int h, int v, int n){
    if(lvl == n){
        max_parts = max(max_parts, (h+1)*(v+1));
        return;
    }

    int rem_roads = n - lvl;
    int opt1 = (h + 1 + rem_roads) * (v + 1); // All horizontal
    int opt2 = (h + 1) * (v + 1 + rem_roads); // All vertical
    int opt3 = (h + 1 + rem_roads/2) * (v + 1 + (rem_roads - rem_roads/2)); // Half-Half

    int bound = max(opt1, max(opt2, opt3));
    if(bound <= max_parts)
        return;

    // Horizontal
    BT(lvl + 1, h + 1, v, n);

    // Vertical
    BT(lvl + 1, h, v + 1, n);
}

int main(){
    int n; cin >> n;

    BT(0, 0, 0, n);
    cout << max_parts << endl;

    return 0; 
}