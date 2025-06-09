#include <iostream>
using namespace std;

int main() {
    int n; cin >> n;
    long long nums[n]={};
    for(int i=0; i<n; i++)
        cin >> nums[i];
        
    for(int i=0; i<n-1; i++){
        int min_ind = i;
        for(int j=i+1; j<n; j++){
            if(nums[j] < nums[min_ind]){
                min_ind = j;
            }
        }
        int tmp = nums[i];
            nums[i] = nums[min_ind];
            nums[min_ind] = tmp;
    }
    
    for(int i=0; i<n; i++)
        cout << nums[i] << " ";
    return 0;
}