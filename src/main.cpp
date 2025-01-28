#include "../include/BPlusTree.h"
#include "../include/Graph.h"
#include "../include/JSONReader.h"
#include <iostream>
using namespace std;

int main()
{
    Graph graph;
    JSONReader reader("../data/users.json");
    vector<User> users = reader.readUsers();
    for (User &user : users)
    {
        graph.insertVertex(user);
        for (const string &connectionId : user.getConnections())
        {
            graph.insertEdge(user.getId(), connectionId);
        }
    }

    cout << "Number of vertices: " << graph.numVertices() << endl;
    cout << "Number of edges: " << graph.numEdges() << endl;
    cout << "Details of 2 id: ";
    graph.viewUserDetails("2");

    return 0;
}