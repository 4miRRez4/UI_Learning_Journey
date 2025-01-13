#include <iostream>
#include <sstream>
#include <vector>
#include <climits>
using namespace std;

bool is_bst(const vector<int>& preOrder) {
    int min = INT_MIN;
    vector<int> stack;

    for (int value : preOrder) {
        if (value < min)
            return false;

        while (!stack.empty() && value > stack.back()) {
            min = stack.back();
            stack.pop_back();
        }

        stack.push_back(value);
    }
    return true;
}

int main(){
    string inputLine;
    getline(cin, inputLine);

    vector<int> preOrder;
    stringstream ss(inputLine);
    int num;
    while(ss >> num)
        preOrder.push_back(num);

    if(is_bst(preOrder))
        cout << "The tree is a BST." << endl;
    else
        cout << "The tree is not a BST!" << endl;

}