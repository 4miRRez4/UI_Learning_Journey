#include <iostream>
#include <vector>
using namespace std;

const int MAX_SIZE = 11;
vector<long long> neighbors[MAX_SIZE];
bool visited[MAX_SIZE] = {false};
long long max_path=0, min_path=10000000000;

void dfs(long long node, string path=""){
    visited[node] = true;

    char r = node + '0';
    path = r + path;

    bool is_leaf = true;
    for(int i=0; i<neighbors[node].size(); i++){
        long long child = neighbors[node][i];
        if(!visited[child]){
            dfs(child, path);
            is_leaf=false;
        }
    }
    
    if(is_leaf){
        long long inted_path = stoll(path);
        if(inted_path > max_path)
            max_path = inted_path;
        if(inted_path < min_path)
            min_path = inted_path;
    }

}

int main(){
    int n; cin >> n;
    long long a, b;
    for(int i=0; i<n ;i++){
        cin >> a >> b;
        neighbors[a].push_back(b);
        neighbors[b].push_back(a);
    }

    long long root; cin >> root;
    dfs(root);

    cout << max_path-min_path << endl;

    return 0;
}
