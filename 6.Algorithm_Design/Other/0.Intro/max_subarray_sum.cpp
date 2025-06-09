#include <iostream>
#include <climits>
using namespace std;

int main(){
    int n; cin >> n;
    int arr[n];
    for(int i=0; i<n; i++)
        cin >> arr[i];
    int max_sum = INT_MIN;


    //O(n^3)
    for(int i=0; i<n; i++){
        for(int j=i; j<n; j++){
            int sum = 0;
            for(int k=i; k<j+1; k++)
                sum += arr[k];
            
            if(sum > max_sum)
                max_sum = sum;
        }
    }
    cout << max_sum << endl;


    //O(n^2)
    max_sum = INT_MIN;
    for(int i=0; i<n; i++){
        int sum =0;
        for(int j=i; j<n; j++){
            sum += arr[j];

            if(sum > max_sum)
                max_sum = sum;
        }
    }
    cout << max_sum << endl;

    //O(n)
    max_sum = INT_MIN;
    int curr_sub = 0;
    for(int i=0; i<n; i++){
        if(curr_sub + arr[i] > arr[i]){
            curr_sub += arr[i];
        }else{
            curr_sub = arr[i];
        }

        if(curr_sub > max_sum)
            max_sum = curr_sub;
    }
    cout << max_sum << endl;

    return 0;
}