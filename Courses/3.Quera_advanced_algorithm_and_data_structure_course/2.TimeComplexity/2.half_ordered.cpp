#include <iostream>
using namespace std;

int main(){
    int n; cin >> n;
    long long nums[n];
    for(int i=0; i<n; i++)
        cin >> nums[i];

    int cnt = 0;
    for(int i=0; i<n; i++){
        if(nums[i] != i+1)
            cnt++;
    }
    if(cnt == 2)
        cout << "YES";
    else
        cout << "NO";
    return 0;
}
