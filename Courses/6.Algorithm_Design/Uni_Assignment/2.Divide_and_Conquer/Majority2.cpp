#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int find_majority(vector<int>& arr, int l, int r){
    if(l == r)
        return arr[l];

    int mid = l + (r-l)/2;
    int l_maj = find_majority(arr, l, mid);
    int r_maj = find_majority(arr, mid+1, r);

    if(l_maj == r_maj)
        return l_maj;
    else{
        int l_cnt=0, r_cnt=0;
        for(int i=l; i<=r; i++){
            if(arr[i] == l_maj)
                l_cnt++;
            else if(arr[i] == r_maj)
                r_cnt++;
        }

        return (l_cnt > r_cnt) ? l_maj : r_maj;
    }
}

int main(){
    vector<int> arr;
    int n;
    while(cin >> n){
        arr.push_back(n);
    }

    cout << find_majority(arr, 0, arr.size()-1) << endl;

    return 0;
}