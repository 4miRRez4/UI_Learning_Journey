#include "Graph.h"

int Graph::numVertices()
{
    return users.size();
    ;
}

vector<string> Graph::vertices()
{
    vector<string> vList;
    for (auto &id : users)
    {
        vList.push_back(id.first);
    }
    return vList;
}

int Graph::numEdges()
{
    int count = 0;
    for (auto &edge : adjacencyList)
    {
        count += edge.second.size();
    }
    return count / 2;
}

vector<pair<string, string>> Graph::edges()
{
    vector<pair<string, string>> eList;
    for (auto &edge : adjacencyList)
    {
        string u = edge.first;
        for (auto &v : edge.second)
        {
            if (u < v)
            {
                eList.push_back({u, v});
            }
        }
    }
    return eList;
}
