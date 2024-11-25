#include <iostream>
using namespace std;

int main(){
    int n, k; cin >> n >> k;
    int sorted_arr[n];
    for(int i=0; i<n; i++)
        cin >> sorted_arr[i];

    int left =0, right =n-1, sum=0;
    while(left < right){
        sum = sorted_arr[left] + sorted_arr[right];
        while(sum > k){
            right--;
            sum = sorted_arr[left] + sorted_arr[right];
        }
        if(sum == k)
            cout << sorted_arr[left] << " " << sorted_arr[right] << endl;

        left++;
    }



    return 0;
}