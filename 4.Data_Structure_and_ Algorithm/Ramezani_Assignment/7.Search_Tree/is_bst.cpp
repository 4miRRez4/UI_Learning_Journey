#include <iostream>
#include <sstream>
#include <vector>
#include <climits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

void connectNode(TreeNode* prevNode, TreeNode* newNode) {

    if (newNode->val < prevNode->val) {
        if (!prevNode->left) {
            prevNode->left = newNode;
        }

    } else if (newNode->val > prevNode->val) {
        if (!prevNode->right) {
            prevNode->right = newNode;
        }
    }
}

bool isInorderValidBst(TreeNode* root, int minVal, int maxVal) {
    if (!root) return true;
    cout << root->val << endl;
    if (root->val <= minVal || root->val >= maxVal) return false;

    return isInorderValidBst(root->left, minVal, root->val) &&
           isInorderValidBst(root->right, root->val, maxVal);
}


void insertInto(vector<int>& nums, int l, int r, TreeNode* parent) {
    if (l > r) 
        return;

    int V = parent->val;

    int sep = l + 1;
    while (sep <= r && nums[sep] < V){
        sep++;
    }
    if(l <= sep-1){
        TreeNode* newNode = new TreeNode(nums[l]);
        connectNode(parent, newNode);
        insertInto(nums, l+1, sep-1, newNode);  
    }
    
    if(sep <= r){
        TreeNode* newNode = new TreeNode(nums[sep]);
        connectNode(parent, newNode);
        insertInto(nums, sep+1, r, newNode);
    }
}


int main(){
    string inputLine;
    getline(cin, inputLine);

    vector<int> nums;
    stringstream ss(inputLine);
    int num;
    while(ss >> num)
        nums.push_back(num);

    TreeNode* root = new TreeNode(nums[0]);
    insertInto(nums, 1, nums.size()-1, root);

    if(isInorderValidBst(root, INT_MIN, INT_MAX))
        cout << "The tree is a BST." << endl;
    else
        cout << "The tree is not a BST!" << endl;

}