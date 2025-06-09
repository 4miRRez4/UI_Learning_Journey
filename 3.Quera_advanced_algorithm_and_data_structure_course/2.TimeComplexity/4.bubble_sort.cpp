#include <iostream>
using namespace std;

int main() {
    int n; cin >> n;
    long long nums[n] = {};
    for(int i=0; i<n; i++)
        cin >> nums[i];
        
    for(int i=0; i<n; i++){
	   bool no_swap = true;
        for(int j=0; j<n-i; j++){
            if(nums[j] > nums[j+1]){
                long long tmp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = tmp;
		   no_swap = false;
            }
        }
	   if(no_swap)
	   	break;
    }
    
    for(int i=0; i<n; i++)
        cout << nums[i] << " ";
    return 0;
}






