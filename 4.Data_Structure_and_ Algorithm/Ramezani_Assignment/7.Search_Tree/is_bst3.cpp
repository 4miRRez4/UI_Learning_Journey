#include <iostream>
#include <vector>
#include <queue>
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

    queue<TreeNode*> queue;
    queue.push(root);

    int i = 1;
    while (!queue.empty() && i < nums.size()) {
        TreeNode* curr = queue.front();
        queue.pop();

        if (i < nums.size()) {
            curr->left = new TreeNode(nums[i]);
            queue.push(curr->left);
            i++;
        }

        if (i < nums.size()) {
            curr->right = new TreeNode(nums[i]);
            queue.push(curr->right);
            i++;
        }
    }

    return root;
}

bool isBstValid(TreeNode* root) {
    stack<TreeNode*> s;
    TreeNode* prev = nullptr;

    while (!s.empty() || root != nullptr) {
        while (root != nullptr) {
            s.push(root);
            root = root->left;
        }

        root = s.top();
        s.pop();

        if (prev != nullptr && root->value <= prev->value) {
            return false;
        }

        prev = root;
        root = root->right;
    }

    return true;
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
    if(isBstValid(root))
        cout << "The tree is a BST." << endl;
    else
        cout << "The tree is not a BST!" << endl;

    return 0;
}
