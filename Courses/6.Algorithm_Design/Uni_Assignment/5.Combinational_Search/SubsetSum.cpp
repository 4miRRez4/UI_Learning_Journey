#include <iostream>
#include <vector>  
#include <sstream>
using namespace std;

bool BT(int lvl, int state_sum, vector<int>& arr, int target){
    if(lvl == arr.size()){
        return target == state_sum;
    }

    bool ans = false;

    // Exclude arr[lvl]
    ans = BT(lvl + 1, state_sum, arr, target);
    // Include arr[lvl]
    ans |= BT(lvl + 1, state_sum + arr[lvl], arr, target);

    return ans;
}

int main(){
    vector<int> arr;

    string input, token;
    getline(cin, input);
    stringstream ss(input);
    while(getline(ss, token, ','))
        arr.push_back(stoi(token));
    
    int target; cin >> target;

    if(BT(0, 0, arr, target)){
        cout << "True" << endl;
    }
    else{
        cout << "False" << endl;
    }
    
    return 0;
}