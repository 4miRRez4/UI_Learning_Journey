//can given array be ascending with only one change
#include <iostream>
using namespace std;

int main(){
    int n; cin >> n;
    long long nums[n];
    for(int i=0; i<n; i++)
        cin >> nums[i];

    // int issues[2] = {};
    // int j=0;
    // for(int i=0; i<n-1; i++){
    //     if(nums[i] > nums[i+1]){
    //         issues[j] = i;
    //         j++;
    //     }
        
    //     if(j > 2){
    //         cout << "NO";
    //         return 0;
    //     }
    // }


    // for(int a=issues[0]; a<= issues[0]+1; a++)
    //     for(int b=issues[1]; b<= issues[1]+1; b++){
    //         bool flag = true;
    //         if(a > 0 && (nums[b] < nums[a-1] || nums[b] > nums[a+1]))
    //             flag = false;
    //         if(b < n-1 && (nums[a] > nums[b+1] || nums[a] < nums[b-1]))
    //             flag = false;
            
    //         if(flag == true){
    //             cout << "YES";
    //             return 0;
    //         }

    //     }

    // cout << "NO";


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