#ifndef GRAPH_H
#define GRAPH_H

#pragma once
#include "User.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

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
    vector<pair<string, string>> outgoingEdges(string v);
    vector<pair<string, string>> incomingEdges(string v);
    void insertVertex(User &user);
    void insertEdge(string v, string u);
    void removeVertex(string &v);
    void removeEdge(string v, string u);

    User getUser(string id);
    void displpyUser() const;
    Graph();
    ~Graph();

private:
    unordered_map<string, User> users;                   // نگهداری اطلاعات کاربران
    unordered_map<string, vector<string>> adjacencyList; // نگهداری همسایگان
};

#endif