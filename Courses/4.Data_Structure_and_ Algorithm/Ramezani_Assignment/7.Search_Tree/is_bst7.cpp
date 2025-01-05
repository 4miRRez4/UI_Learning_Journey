#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

bool is_bst(vector<int>& preOrder, int l, int r, int minVal, int maxVal) {
    if (l > r) 
        return true;

    int V = preOrder[l];

    if (V < minVal || V > maxVal)
        return false;

    // first element bigger than V
    int sep = l + 1;
    while (sep <= r && preOrder[sep] < V)
        sep++;

    return is_bst(preOrder, l + 1, sep - 1, minVal, V) && 
           is_bst(preOrder, sep, r, V, maxVal);
}

int main(){
    string inputLine;
    getline(cin, inputLine);

    vector<int> preOrder;
    stringstream ss(inputLine);
    int num;
    while(ss >> num)
        preOrder.push_back(num);

    if(is_bst(preOrder, 0, preOrder.size()-1, INT32_MIN, INT32_MAX))
        cout << "The tree is a BST." << endl;
    else
        cout << "The tree is not a BST!" << endl;

}