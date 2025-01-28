#include "../include/dataBase.h"
#include <iostream>
using namespace std;

void Database::createTable(string tableName, int degree) {
    if (tables.contains(tableName)) {
        cerr << tableName << " already exists." << endl;
        return;
    }

    Table* newTable = new Table(degree);
    tables.insert(tableName, newTable);

    cout << "Table " << tableName << " created successfully." << endl;
}

void Database::removeTable(string tableName) {
    if (!tables.contains(tableName)) {
        cerr << tableName << " does not exist." << endl;
        return;
    }

    delete tables.search(tableName);
    tables.remove(tableName);

    cout << "Table " << tableName << " removed succesfuly." << std::endl;
}

Table* Database::getTable(string tableName) {
    if (!tables.contains(tableName)) {
        cerr << tableName << " does not exist." << endl;
        return nullptr;
    }

    return tables.search(tableName);
}