#include "../include/dataBase.h"
#include "../include/Interface.h"
#include "../include/JSONReader.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    Graph graph;
    JSONReader JReader("../data/users.json");
    vector<User> users = JReader.readUsers();
    for (User &user : users)
    {
        graph.insertVertex(user);
        for (const string &connectionId : user.getConnections())
        {
            graph.insertEdge(user.getId(), connectionId);
        }
    }

    RecommendationManager recManager(graph);

    Database* db = new Database();
    //TODO: default table users...

    Interface interface(graph, recManager, db);
    interface.start();

    return 0;
}
