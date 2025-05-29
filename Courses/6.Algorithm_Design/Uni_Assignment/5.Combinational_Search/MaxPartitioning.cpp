#include <iostream>
using namespace std;

int max_parts = 0;

void BT(int lvl, int h, int v, int n){
    if(lvl == n){
        max_parts = max(max_parts, (h+1)*(v+1));
        return;
    }

    // This road be horizontal
    BT(lvl + 1, h + 1, v, n);

    // This road be vertical
    BT(lvl + 1, h, v + 1, n);
}

int main(){
    int n; cin >> n;

    BT(0, 0, 0, n);
    cout << max_parts << endl;

    return 0; 
}