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
pair<string, string> Graph::getEdge(string u, string v)
{
    if (adjacencyList.find(u) != adjacencyList.end())
    {
        for (string &neighbor : adjacencyList.at(u))
        {
            if (neighbor == v)
            {
                return {u, v};
            }
        }
    }
    return {"", ""};
}

pair<string, string> Graph::endVertices(pair<string, string> edge)
{
    return edge;
}
string Graph::opposite(string v, pair<string, string> edge)
{
    if (edge.first == v)
    {
        return edge.second;
    }
    else if (edge.second == v)
    {
        return edge.first;
    }
    return "";
}

int Graph::outDegree(string v)
{
    if (adjacencyList.find(v) != adjacencyList.end())
    {
        return adjacencyList.at(v).size();
    }
    return 0;
}
int Graph::inDegree(string v)
{
    int count = 0;
    for (auto &it : adjacencyList)
    {
        for (auto &neighbor : it.second)
        {
            if (neighbor == v)
            {
                count++;
                break;
            }
        }
    }
    return count;
}
vector<pair<string, string>> Graph::outgoingEdges(string v)
{
    vector<pair<string, string>> eList;
    if (adjacencyList.find(v) != adjacencyList.end())
    {
        for (auto &it : adjacencyList.at(v))
        {
            eList.push_back({v, it});
        }
    }
    return eList;
}
vector<pair<string, string>> Graph::incomingEdges(string v)
{
    vector<pair<string, string>> eList;
    for (auto &it : adjacencyList)
    {
        for (auto &neighbor : it.second)
        {
            if (neighbor == v)
            {
                eList.push_back({it.first, v});
                break;
            }
        }
    }
    return eList;
}
