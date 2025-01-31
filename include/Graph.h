#ifndef GRAPH_H
#define GRAPH_H

#pragma once
#include "User.h"
#include "JSONReader.h"
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <limits>
#include <cmath>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <omp.h>

using namespace std;
class Graph
{
public:
    int numVertices();
    vector<string> vertices();

    int numEdges();

    vector<pair<string, string>> edges();
    pair<string, string> getEdge(string u, string v);
    pair<string, string> endVertices(pair<string, string> edge);
    string opposite(string v, pair<string, string> edge);
    int outDegree(string v);
    int inDegree(string v);
    vector<string> outgoingEdges(string v);
    vector<string> incomingEdges(string v);
    void insertVertex(User &user);
    void insertEdge(string v, string u);
    void removeVertex(string &v);
    void removeEdge(string v, string u);

    User getUser(string id);

    void viewAllUsers();
    void viewUserDetails(string id);

    Graph() = default;
    ~Graph() = default;

    vector<string> getKeyUsers(int n, const string &metric = "degree");
    int degreeCentrality(string userId);
    unordered_map<string, double> PageRankCentrality(double dampingFactor = 0.85, int maxIterations = 100, double tolerance = 1e-6);
    void saveToJSON(const string &filename);

private:
    unordered_map<string, User> users;                   // نگهداری اطلاعات کاربران
    unordered_map<string, vector<string>> adjacencyList; // نگهداری همسایگان
};

#endif