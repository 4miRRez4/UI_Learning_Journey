#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
#include <string>
using namespace std;

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : value(value), left(nullptr), right(nullptr) {}
};

TreeNode* buildBST(const vector<int>& nums) {
    if (nums.empty()) return nullptr;

    TreeNode* root = new TreeNode(nums[0]);
    vector<TreeNode*> nodes;
    nodes.push_back(root);

    for (int i = 1, parentIndex = 0; i < nums.size(); parentIndex++) {
        if (i < nums.size()) {
            nodes[parentIndex]->left = new TreeNode(nums[i]);
            nodes.push_back(nodes[parentIndex]->left);
            i++;
        }
        if (i < nums.size()) {
            nodes[parentIndex]->right = new TreeNode(nums[i]);
            nodes.push_back(nodes[parentIndex]->right);
            i++;
        }
    }

    return root;
}


bool isBstValid(TreeNode* root, TreeNode*& prev) {
    if (root == nullptr) return true;

    if (!isBstValid(root->left, prev)) {
        return false;
    }

    if (prev != nullptr && root->value <= prev->value) {
        return false;
    }
    prev = root;

    return isBstValid(root->right, prev);
}

int main() {
    string line;
    getline(cin, line);

    istringstream ss(line);
    vector<int> nums;

    int num;
    while (ss >> num) 
        nums.push_back(num);

    TreeNode* root = buildBST(nums);
    TreeNode* prev = nullptr;
    if(isBstValid(root, prev))
        cout << "The tree is a BST." << endl;
    else
        cout << "The tree is not a BST!" << endl;

    return 0;
}
