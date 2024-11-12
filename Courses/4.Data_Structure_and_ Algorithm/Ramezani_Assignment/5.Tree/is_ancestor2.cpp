#include <iostream>
#include <vector>
using namespace std;

const int MAX_SIZE = 20000;
vector<int> children[MAX_SIZE];
int first_visit[MAX_SIZE], second_visit[MAX_SIZE];
int timer;

void dfs(int node){
    first_visit[node] = timer;
    timer++;
    for(int child : children[node])
        dfs(child);
    second_visit[node] = timer;
}

bool is_ancestor(int a, int b){
    return first_visit[a] <= first_visit[b] && second_visit[a] >= second_visit[b];
}
int main(){
    int n, m; cin >> n >> m;
    for(int i=0; i<m; i++){
        int a, b; cin >> a >> b;
        children[a].push_back(b);
    }

    dfs(0);

    int p1, p2; cin >> p1 >> p2;
    if(is_ancestor(p1, p2))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;


    return 0;
}