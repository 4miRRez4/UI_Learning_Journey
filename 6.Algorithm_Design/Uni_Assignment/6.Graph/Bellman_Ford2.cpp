#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

struct Edge {
    int to, weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

void printPath(int dest, int time, const vector<int>& parent) {
    vector<int> path;
    for (int v = dest; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    cout << "Time:" << time << ", Route:[";
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i + 1 < path.size()) cout << ", ";
    }
    cout << "]\n";
}

void spfa(int n, int src, int dest, vector<vector<Edge>>& graph) {
    vector<int> dist(n, INT_MAX), inQueue(n, false), parent(n, -1);
    queue<int> q;

    dist[src] = 0;
    q.push(src);
    inQueue[src] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        inQueue[u] = false;

        for (const Edge& e : graph[u]) {
            if (dist[u] != INT_MAX && dist[u] + e.weight < dist[e.to]) {
                dist[e.to] = dist[u] + e.weight;
                parent[e.to] = u;
                if (!inQueue[e.to]) {
                    q.push(e.to);
                    inQueue[e.to] = true;
                }
            }
        }
    }

    if (dist[dest] == INT_MAX)
        cout << "No path exists\n";
    else
        printPath(dest, dist[dest], parent);
}

int main() {
    int t; cin >> t;
    while (t--) {
        int n, m, src, dest;
        cin >> n >> m >> src >> dest;
        vector<vector<Edge>> graph(n);

        for (int i = 0; i < m; ++i) {
            int u, v, w; cin >> u >> v >> w;
            graph[u].emplace_back(v, w);
        }

        spfa(n, src, dest, graph);
    }
    return 0;
}
