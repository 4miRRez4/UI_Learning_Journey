#include <iostream>
using namespace std;

int main(){
    int n, m; cin >> n >> m;

    int arr[n][m];
    for (int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> arr[i][j];

    int* prev_row = new int[m];
    int* curr_row = new int[m];
    char dir[n][m];

    prev_row[0] = arr[n-1][0];
    dir[n-1][0] = 0;
    for(int j=1; j<m; j++){
        prev_row[j] = arr[n-1][j] + prev_row[j-1];
        dir[n-1][j] = 'R';
    }
    
    for(int i=n-2; i>=0; i--){
        curr_row[0] = prev_row[0] + arr[i][0];
        dir[i][0] = 'U';
        for(int j=1; j<m; j++){
            if(prev_row[j] + arr[i][j] > curr_row[j-1] + arr[i][j]){
                curr_row[j] = prev_row[j] + arr[i][j];
                dir[i][j] = 'U';
            }else{
                curr_row[j] = curr_row[j-1] + arr[i][j];
                dir[i][j] = 'R';
            }
        }
        int* tmp = prev_row;
        prev_row = curr_row;
        curr_row = tmp;
    }

    cout << prev_row[m-1] << endl;

    int i = 0, j = m - 1;
    string path = "";
    while (i != n - 1 || j != 0) {
        char move = dir[i][j];
        path += move;
        if (move == 'U') i++;
        else if (move == 'R') j--;
    }

    for (int k = path.size() - 1; k >= 0; k--)
        cout << path[k];
    cout << endl;

    delete[] prev_row;
    delete[] curr_row;

    return 0;
}