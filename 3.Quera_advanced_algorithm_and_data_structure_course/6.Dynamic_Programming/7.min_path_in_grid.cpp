#include <iostream>
#include <climits>
using namespace std;


int main(){
    int n, m; cin >> n >> m;
    
    int grid[n][m];
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> grid[i][j];
    
    long long d1[n][m];
    long long d2[n][m];

    d1[0][0] = d2[0][0] = grid[0][0];
    for(int j=1; j<m; j++){
        d1[0][j] = d1[0][j-1] + grid[0][j];
        d2[0][j] = INT_MAX;
    }

    for(int i=1; i<n; i++){
        d1[i][0] = min(d1[i-1][0], d2[i-1][0]) + grid[i][0];
        for(int j=1; j<m; j++){
            d1[i][j] = min(min(d1[i-1][j], d2[i-1][j]), d1[i][j-1]) + grid[i][j];
        }

        d2[i][m-1] = min(d1[i-1][m-1], d2[i-1][m-1]) + grid[i][m-1];
        for(int j=m-2; j>=0; j--){
            d2[i][j] = min(min(d1[i-1][j], d2[i-1][j]), d2[i][j+1]) + grid[i][j];
        }
    }
    
    cout << d1[n-1][m-1] << endl;
    
    return 0;
}