#ifndef INTERFACE_H
#define INTERFACE_H

#include "graph.h"
#include "JSONReader.h"
#include "RecommendationManager.h"
#include "CommunicationQuality.h"
#include <iostream>
#include <string>
#include <unordered_map>

class Interface
{
public:
    Interface(Graph &g, RecommendationManager &rM)
        : graph(g), recManager(rM), currentUser("") {}

private:
    Graph &graph;
    RecommendationManager &recManager;
    string currentUser;

    void clearScreen();
    void showLoginMenu();
    void handleLogin();
};

#endif