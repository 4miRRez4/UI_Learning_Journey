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
    Interface(Graph &g, RecommendationManager &rM, Database *db, const string &jsonFilePath)
        : graph(g), recManager(rM), db(db), currentUser(""), jsonFilePath(jsonFilePath) {}


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
    void waitForEnter();

private:
    Graph &graph;
    RecommendationManager &recManager;
    string currentUser;
    string jsonFilePath;
    Database *db;

    void clearScreen();
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
    void showSocialNetworkMenu();
    void showDatabaseMenu();
    void createTable();
    void insertRecord();
    void updateRecord();
    void deleteRecord();
    void searchById();
    void searchByColumn();
    void printAllRecords();
    void performAggregation();
    void createIndex();
};

#endif