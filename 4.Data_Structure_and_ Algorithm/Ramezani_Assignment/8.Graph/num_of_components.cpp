#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void dfs(int node, vector<int>* adj_list, bool* visited){
    stack<int> to_visit;
    to_visit.push(node);
    
    while(!to_visit.empty()){
        int curr_node = to_visit.top();
        to_visit.pop();

        visited[curr_node] = true;

        for(int neighbor : adj_list[curr_node]){
            if(!visited[neighbor])
                to_visit.push(neighbor);
        }
    }
}

int num_of_path_needed(vector<int>* adj_list, int n){
    int needed_path = -1;

    bool visited[n] = {};
    for(int i=0; i<n; i++){
        if(!visited[i]){
            needed_path++;
            dfs(i, adj_list, visited);
        } 
    }

    return needed_path;
}

int main(){
    int n; cin >> n;

    pair<int, int> island_loc[n];
    vector<int> adj_list[n];

    for(int i=0; i<n; i++)
    {
        int x, y; cin >> x >> y;
        island_loc[i] = make_pair(x, y);
        for(int j=0; j<i; j++){
            if(x == island_loc[j].first || y == island_loc[j].second){
                adj_list[i].push_back(j);
                adj_list[j].push_back(i);
            }
        }
    }


    cout << num_of_path_needed(adj_list, n) << endl;


    return 0;
}