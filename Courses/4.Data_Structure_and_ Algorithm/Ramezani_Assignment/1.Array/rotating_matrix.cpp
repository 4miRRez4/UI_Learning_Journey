//rotating elemnts of given n*n matrix by 90 degree clockwise and inplace
#include <iostream>
using namespace std;


int main(){
    int n; cin >> n;
    int matrix[n][n];
    for(int r=0; r<n; r++)
        for(int c=0; c<n; c++)
            cin >> matrix[r][c];

    //rotating by 90 degree clockwise=> transpose + reverse: [i][j] = [j][n-i-1]
    //transpose: [i][j] => [j][i]
    for(int r=0; r<n; r++)
        for(int c=r; c<n; c++){
            int tmp = matrix[r][c];
            matrix[r][c] = matrix[c][r];
            matrix[c][r] = tmp;
        }

    //reverse: [i][j] = [i][n-j-1]
    for(int r=0; r<n; r++)
        for(int c=0; c< n/2; c++){
            int tmp = matrix[r][c];
            matrix[r][c] = matrix[r][n-c-1];
            matrix[r][n-c-1] = tmp;
        }
 
    for(int r=0; r<n; r++){
        for(int c=0; c<n; c++)
            cout << matrix[r][c] << " ";
        cout << endl;
    }


    return 0;
}
