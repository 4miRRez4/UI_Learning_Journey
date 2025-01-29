#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "map.h"
#include "table.h"
using namespace std;

class Database {
private:
    Map<string, Table*> tables; // table names to table objects

public:
    

    Database() = default;
    ~Database();

    void createTable(string tableName,const vector<Table::Column>& cols, int degree); //table with specific columns and data types
    void removeTable(string tableName);
    Table* getTable(string tableName);
};

#endif
