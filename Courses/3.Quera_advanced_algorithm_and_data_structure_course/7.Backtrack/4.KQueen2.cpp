#include <iostream>
#include <vector>
#include <utility>
using namespace std;

bool canPlace(vector<bool> &cols, vector<bool> &main_diags, vector<bool> &anti_diags, int i, int j, int n){
    return !(cols[j] || main_diags[i-j+n-1] || anti_diags[i+j]);
}

void kQueen(vector<bool> &cols, vector<bool> &main_diags, vector<bool> &anti_diags, int row, int k, int n, int &validCnt){
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
            if(canPlace(cols, main_diags, anti_diags, row, j, n)){
                // Put queen at (row, j)
                cols[j] = main_diags[row-j+n-1] = anti_diags[row+j] = true;

                kQueen(cols, main_diags, anti_diags, row+1, k-1, n, validCnt);

                cols[j] = main_diags[row-j+n-1] = anti_diags[row+j] = false;
            }
        }
    }

    // Skip this row
    kQueen(cols, main_diags, anti_diags, row+1, k, n, validCnt);
}

int count(int n, int k){
    int validCnt = 0;
    vector<bool> cols(n, 0), main_diags(2*n -1, 0), anti_diags(2*n -1, 0);
    
    kQueen(cols, main_diags, anti_diags, 0, k, n, validCnt);

    return validCnt;
}

int main(){
    int n, k; cin >> n >> k;

    cout << count(n, k) << endl;

    return 0;
}