#ifndef INTERFACE_H
#define INTERFACE_H

#include "Graph.h"
#include "JSONReader.h"
#include "RecommendationManager.h"
#include "CommunicationQuality.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>
#include "dataBase.h"
#include "aggregation_methods.h"

class Interface
{
public:
    Interface(Graph &g, RecommendationManager &rM, Database *db)
        : graph(g), recManager(rM), db(db), currentUser("") {}

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
    Database *db;

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
    void showSocialNetworkMenu();
    void showDatabaseMenu();
    void createTable();
    void insertRecord();
    void updateRecord();
    void deleteRecord();
    void searchRecord();
    void printAllRecords();
    void performAggregation();
    void createIndex();
};

#endif