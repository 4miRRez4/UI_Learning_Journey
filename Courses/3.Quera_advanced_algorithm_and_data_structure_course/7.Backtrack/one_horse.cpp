#include <iostream>
#include <utility>
#include <vector>
using namespace std;

pair<int, int> movements[8] = {{-2, -1}, {-2, 1}, {-1, 2}, {-1, -2}, {1, 2}, {1, -2}, {2, -1}, {2, 1}};

bool canPut(int x, int y, int n){
    return (x>=0 && x<n && y>=0 && y<n);
}

void one_horse_bt(vector<vector<bool>> &table, int i, int j, int k, int n, int &cnt){
    if(k == 0){
        if(!table[i][j]){
            cnt++;
            table[i][j] = true;
        }

        return;
    }

    for(int m=0; m<8; m++){
        pair<int, int> move = movements[m];
        int x = i + move.first;
        int y = j + move.second;
        
        if(canPut(x, y, n)){
            one_horse_bt(table, x, y, k-1, n, cnt);
        }
    } 
}

int count(int n, int k){
    int cnt = 0;
    vector<vector<bool>> table(n, vector<bool> (n, false));

    one_horse_bt(table, 0, 0, k, n, cnt);

    return cnt;
}

int main(){
    int n, k; cin >> n >> k;

    cout << count(n, k) << endl;

    return 0;
}