//rotating elemnts of given n*n matrix by 90 degree clockwise and inplace
#include <iostream>
using namespace std;


int main(){
    int n; cin >> n;
    int matrix[n][n];
    for(int r=0; r<n; r++)
        for(int c=0; c<n; c++)
            cin >> matrix[r][c];

    for(int layer =0; layer < n/2; layer++){
        int first = layer;
        int last = n - 1 - layer;

        for(int i=first; i<last; i++){
            int offset = i - first;

            int first_elem = matrix[first][i];
            matrix[first][i] = matrix[last - offset][first];
            matrix[last - offset][first] = matrix[last][last - offset];
            matrix[last][last - offset] = matrix[i][last];
            matrix[i][last] = first_elem;
        }
    }
 
    for(int r=0; r<n; r++){
        for(int c=0; c<n; c++)
            cout << matrix[r][c] << " ";
        cout << endl;
    }


    return 0;
}
