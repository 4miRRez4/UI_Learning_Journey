#include <iostream>
using namespace std;

int MAX_SIZE = 300000;
string find_post_order(int* pre, int* in, int in_left, int in_right, string post=""){
    if(in_left == in_right)
        return to_string(in[in_right]) + " ";
    if(in_left > in_right)
        return "";

    int curr_root = *pre;
    //finding left and right sub-tree of curr_root
    int root_ind = in_left;
    while(in[root_ind] != curr_root)
        root_ind++;
    
    //post order of left sub-tree
    post += find_post_order(pre+1, in, in_left, root_ind-1);
    //post order of right sub-tree
    post += find_post_order(pre+root_ind+1, in, root_ind+1, in_right);

    return post + to_string(curr_root) + " ";
}


int main(){
    int n, tmp; cin >> n;
    int in_order[MAX_SIZE]={};
    for(int i=0; i<n; i++){
        cin >> tmp;
        in_order[i] = tmp;
    }

    int pre_order[MAX_SIZE] = {};
    for(int i=0; i<n; i++){
        cin >> tmp;
        pre_order[i] = tmp;
    }

    cout << find_post_order(pre_order, in_order, 0, n-1) << endl;

    return 0;
}