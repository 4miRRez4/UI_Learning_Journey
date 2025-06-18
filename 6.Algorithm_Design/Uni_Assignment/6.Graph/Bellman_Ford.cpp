#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Edge {
    int u, v, w;

    Edge(int node1, int node2, int weight): u(node1), v(node2), w(weight) {};
};

void printResult(int dest, int time, vector<int>& parent) {
    vector<int> path;
    for (int v = dest; v != -1; v = parent[v])
        path.push_back(v);

    reverse(path.begin(), path.end());

    cout << "Time:" << time << ", Route:[";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i + 1 < path.size()) cout << ", ";
    }
    cout << "]" << endl;
}

void bellman_ford(int n, int m, int src, int dest, vector<Edge>& edges) {
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    dist[src] = 0;

    // Relaxing
    for (int i = 0; i < n - 1; i++) {
        bool updated = false;
        for (Edge& edge : edges) {
            if (dist[edge.u] != INT_MAX && dist[edge.u] + edge.w < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.w;
                parent[edge.v] = edge.u;
                updated = true;
            }
        }
        if(!updated) break;
    }

    bool exist = true;
    for (Edge& edge : edges) {
        if (dist[edge.u] != INT_MAX && dist[edge.u] + edge.w < dist[edge.v]) {
            exist = false; // Negative cycle
            break;
        }
    }

    if (dist[dest] == INT_MAX) {
        exist = false;
    }

    if(!exist){
        cout << "No path exists" << endl;
        return;
    }

    printResult(dest, dist[dest], parent);
}

int main() {
    int t; cin >> t;
    while (t--) {
        int n, m, src, dest; cin >> n >> m >> src >> dest;

        vector<Edge> edges;
        for (int i = 0; i < m; ++i) {
            int u, v, w; cin >> u >> v >> w;
            edges.emplace_back(u, v, w);
        }

        bellman_ford(n, m, src, dest, edges);
    }
    return 0;
}
