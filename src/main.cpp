#include "../include/dataBase.h"
#include "../include/cli.h"
#include "../include/Interface.h"
#include "../include/JSONReader.h"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    Database *db = new Database();
    handleUserInput(db);

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
    Interface interface(graph, recManager);
    interface.start();
    return 0;
}
