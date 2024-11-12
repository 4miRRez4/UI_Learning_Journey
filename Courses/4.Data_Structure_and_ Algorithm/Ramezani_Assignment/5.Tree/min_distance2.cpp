#include <iostream>
#include <vector>
using namespace std;

const int MAX_SIZE = 101;
vector<int> children[MAX_SIZE];
int parent[MAX_SIZE];
int depth[MAX_SIZE];

void dfs(int node, int d=0){
    depth[node] = d;
    d++;
    for(int i=0; i<children[node].size(); i++){
        dfs(children[node][i], d);
    }
}

int min_distance(int a, int b){
    int d=0;
    d+= abs(depth[a]-depth[b]);
    while(depth[a] > depth[b])
        a = parent[a];
    while(depth[b] > depth[a])
        b = parent[b];

    while(a != b){
        a = parent[a];
        b = parent[b];
        d+=2;
    }

    return d;
}

int main(){
    int n, q, a, b; cin >> n >> q;
    for(int i=0; i<n-1; i++){
        cin >> a >> b;
        children[a].push_back(b);
        parent[b] = a;
    }
    dfs(1);
    for(int i=0; i<q; i++){
        cin >> a >> b;
        cout << min_distance(a, b) << endl;
    }


    return 0;
}