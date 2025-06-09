#include <iostream>
using namespace std;

int main(){
    int n; cin >> n;
    long long nums[n]={};
    for(int i=0; i<n; i++)
        cin >> nums[i];

    for(int i=1; i<n; i++){
        long long tmp = nums[i];
        int j = i-1;
        while(nums[j] > tmp & j>=0){
            nums[j+1] = nums[j];
            j--;
        }
        nums[j+1] = tmp;
    }

    for(int i=0; i<n; i++)
        cout << nums[i] << " ";
    return 0;
}