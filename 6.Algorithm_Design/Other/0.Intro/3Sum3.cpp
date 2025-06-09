#include <iostream>
#include <climits>
using namespace std;

int main(){
    int n; cin >> n;
    int arr[n];
    for(int i=0; i<n; i++)
        cin >> arr[i];
        
    for(int a=0; a<n-1; a++){
        int b = a+1;
        int c = n-1;
        
        while(b < c){
            int sum = arr[a] + arr[b] + arr[c];
            if(sum == 0){
                cout << "YES" << endl;
                return 0;
            }
            else if(sum < 0){
                b++;
            }
            else{
                c--;
            }
        }
    }
    cout << "NO" << endl;
    return 0;
}