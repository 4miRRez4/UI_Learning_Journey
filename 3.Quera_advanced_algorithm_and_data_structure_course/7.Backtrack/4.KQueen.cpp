#include <iostream>
#include <vector>
#include <utility>
using namespace std;

bool canPlace(vector<pair<int, int>> &queensInGrid, int i, int j){
    for(pair<int, int> &q : queensInGrid){
        if(q.first == i || q.second == j || q.first-q.second == i-j || q.first+q.second == i+j)
            return false;
    }
    return true;
}

void kQueen(vector<pair<int, int>> &queensInGrid, int row, int k, int n, int &validCnt){
    if(row == n){
        if(k == 0)
            validCnt += 1;
        return;
    }

    // Early pruning
    if(k > n-row)
        return;

    // Place a queen in this row
    if(k > 0){
        for(int j=0; j<n; j++){
            if(canPlace(queensInGrid, row, j)){
                queensInGrid.push_back({row, j});

                kQueen(queensInGrid, row+1, k-1, n, validCnt);

                queensInGrid.pop_back();
            }
        }
    }

    // Skip this row
    kQueen(queensInGrid, row+1, k, n, validCnt);
}

int main(){
    int n, k; cin >> n >> k;
    
    int validCnt = 0;
    vector<pair<int, int>> queensInGrid;
    
    kQueen(queensInGrid, 0, k, n, validCnt);

    cout << validCnt << endl;

    return 0;
}