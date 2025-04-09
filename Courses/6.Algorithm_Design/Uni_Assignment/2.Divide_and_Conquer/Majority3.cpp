#include <iostream>
#include <vector>
using namespace std;

int find_maj(vector<int>& arr){
    int candidate = arr[0];
    int counter = 1;

    for(int i=1; i<arr.size(); i++){
        if(arr[i] == candidate){
            counter +=1;
        }else{
            counter -=1;

            if(counter < 0){
                candidate = arr[i];
                counter = 0;
            }
        }
    }

    return candidate;
}

int main(){
    vector<int> arr;
    int n;
    while(cin >> n){
        arr.push_back(n);
    }

    cout << find_maj(arr) << endl;
    return 0;
}