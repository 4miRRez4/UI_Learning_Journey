#ifndef INTERFACE_H
#define INTERFACE_H

#include "graph.h"
#include "JSONReader.h"
#include "RecommendationManager.h"
#include "CommunicationQuality.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>

class Interface
{
public:
    Interface(Graph &g, RecommendationManager &rM, const string &jsonFilePath)
        : graph(g), recManager(rM), currentUser(""), jsonFilePath(jsonFilePath) {}

    void start()
    {
        while (true)
        {
            if (currentUser.empty())
            {
                showLoginMenu();
            }
            else
            {
                showMainMenu();
            }
        }
    }

private:
    Graph &graph;
    RecommendationManager &recManager;
    string currentUser;
    string jsonFilePath;

    void clearScreen();
    void waitForEnter();
    void showLoginMenu();
    void handleLogin();
    void handleRegistration();
    void showMainMenu();
    void handleViewUserDetails();
    void handleViewRecommendations(string &userId);
    void handleViewRecommendationsForOther();
    void handleConnect();
    void handleRemoveConnection();
    void handleViewKeyUsers();
    void handleCommunicationQuality();
    void saveGraphToJSON()
    {
        graph.saveToJSON(jsonFilePath);
        // cout << "Graph saved to " << jsonFilePath << endl; // برای اطمینان از ذخیره
    }
};

#endif