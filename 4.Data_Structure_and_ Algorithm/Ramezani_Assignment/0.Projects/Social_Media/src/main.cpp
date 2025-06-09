#include "../include/dataBase.h"
#include "../include/Interface.h"
#include "../include/JSONReader.h"
#include <iostream>
#include <vector>
using namespace std;

void createUsersTable(Database* db) {
    cout << "Creating table users..." << endl;
    string tableName = "users";

    vector<Table::Column> columns = {
        //id as primary key.
        {"name", Table::DataType::STRING, Table::IndexType::NON_UNIQUE},
        {"dateOfBirth", Table::DataType::DATE, Table::IndexType::NON_UNIQUE},
        {"universityLocation", Table::DataType::STRING, Table::IndexType::NON_UNIQUE},
        {"field", Table::DataType::STRING, Table::IndexType::NON_UNIQUE},
        {"workplace", Table::DataType::STRING, Table::IndexType::NON_UNIQUE},
        {"specialties", Table::DataType::STRING, Table::IndexType::NON_UNIQUE},  //comma-separated string
        {"connectionIds", Table::DataType::STRING, Table::IndexType::NON_UNIQUE}  //comma-separated string
    };

    db->createTable(tableName, columns, 3);
    cout << "Table users created successfully." << endl;
}

string join(const vector<string>& vec, const string& delimiter) {
    string result="";
    for (int i=0; i<vec.size(); i++) {
        result += vec[i];
        if (i < vec.size() - 1) 
            result += delimiter;
    }
    return result;
}

void insertUsersToTable(Database* db, const vector<User>& users) {
    Table* usersTable = db->getTable("users");
    if (!usersTable) {
        cout << "Table " << usersTable->name << " does not exist." << endl;
        return;
    }
    int maxId = -1;
    for (const auto& user : users) {
        int userId = stoi(user.getId());
        maxId = (maxId > userId) ? maxId : userId;

        vector<Value> values = {
            user.getName(),
            user.getDateOfBirth(),
            user.getUniversityLocation(),
            user.getField(),
            user.getWorkplace(),
            join(user.getSpecialties(), ", "),   
            join(user.getConnections(), ", ")
        };

        usersTable->addRecord(values, userId);
    }

    usersTable->setNextRecordId(maxId + 1);

    cout << users.size() << " users added successfully." << endl;
}




int main() {
    Graph graph;
    
    string jsonFilePath = "./data/users.json";
    JSONReader JReader(jsonFilePath);
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

    createUsersTable(db);
    insertUsersToTable(db, users);

    Interface interface(graph, recManager, db, jsonFilePath);
    interface.waitForEnter();
    interface.start();

    return 0;
}
