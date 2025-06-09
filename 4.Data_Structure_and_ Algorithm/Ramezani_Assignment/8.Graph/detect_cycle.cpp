#include <iostream>
#include <vector>
using namespace std;

bool check_dfs(int node, int parent, vector<int>* adj_list, bool* visited){
    visited[node] = true;

    for(int neighbor : adj_list[node]){
        if(!visited[neighbor]){
            if(check_dfs(neighbor, node, adj_list, visited)){
                return true;
            }
        }
        else if(neighbor != parent){
            return true;
        }
    }

    return false;
}

bool has_cycle(vector<int>* adj_list, int n){
    //maybe graph is disconnected so we have to check all components.
    bool visited[n] = {};
    for(int i=0; i<n; i++){
        if(!visited[i]){
            if(check_dfs(i, -1, adj_list, visited)){
                return true;
            }
        }
    }
    return false;;
}

int main(){
    int n; cin >> n;

    vector<int> adj_list[n]; //index represents the node
    int a, b;
    while(cin >> a >> b){
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    if(has_cycle(adj_list, n)){
        cout << "YES" << endl;
    }else{
        cout << "NO" << endl;
    }


    return 0;
}