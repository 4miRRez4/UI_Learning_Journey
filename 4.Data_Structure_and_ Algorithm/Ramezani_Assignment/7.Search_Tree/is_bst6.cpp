#include <iostream>
#include <sstream>
#include <vector>
#include <climits>
using namespace std;

bool is_bst(const vector<long long>& preOrder, int& ind, long long minVal, long long maxVal) {
    if (ind >= preOrder.size()) 
        return true;

    long long V = preOrder[ind];

    if (V <= minVal || V >= maxVal)
        return false;

    ind++;

    return is_bst(preOrder, ind, minVal, V) && 
           is_bst(preOrder, ind, V, maxVal);
}

int main(){
    string inputLine;
    getline(cin, inputLine);

    vector<long long> preOrder;
    stringstream ss(inputLine);
    int num;
    while(ss >> num)
        preOrder.push_back(num);

    int ind =0;
    if(is_bst(preOrder, ind, LONG_LONG_MIN, LONG_LONG_MAX))
        cout << "The tree is a BST." << endl;
    else
        cout << "The tree is not a BST!" << endl;

}