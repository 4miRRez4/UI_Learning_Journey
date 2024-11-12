#include <iostream>
#include <vector>
using namespace std;

const int MAX_SIZE = 10;
vector<int> neighbors[MAX_SIZE];
bool visited[MAX_SIZE] = {false};
long long max_path=0, min_path=999999999;

void dfs(int node, string path=""){
    visited[node] = true;

    char r = node + '0';
    path = r + path;

    bool is_leaf = true;
    for(int i=0; i<neighbors[node].size(); i++){
        int child = neighbors[node][i];
        if(!visited[child]){
            dfs(child, path);
            is_leaf=false;
        }
    }
    
    if(is_leaf){
        int inted_path = stoi(path);
        if(inted_path > max_path)
            max_path = inted_path;
        if(inted_path < min_path)
            min_path = inted_path;
    }

}

int main(){
    int n, a, b; cin >> n;
    for(int i=0; i<n ;i++){
        cin >> a >> b;
        neighbors[a].push_back(b);
        neighbors[b].push_back(a);
    }

    int root; cin >> root;
    dfs(root);

    cout << max_path-min_path << endl;

    return 0;
}
