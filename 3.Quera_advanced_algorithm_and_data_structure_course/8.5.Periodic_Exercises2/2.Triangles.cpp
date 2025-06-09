#include <iostream>
#include <vector>
using namespace std;


int main(){
    int t; cin >> t;

    while(t--){
        int n; cin >> n;
        vector<vector<int>> dp_triangle(n, vector<int> (n, 0));

        for(int i=0; i<n; i++){
            for(int j=0; j<=i; j++){
                cin >> dp_triangle[i][j];
            }
        }

        for(int i=n-2; i>=0; i--){
            for(int j=0; j<=i; j++){
                dp_triangle[i][j] = max(dp_triangle[i+1][j], dp_triangle[i+1][j+1]) + dp_triangle[i][j];
            }
        }

        cout << dp_triangle[0][0] << endl;
    }

    return 0;
}