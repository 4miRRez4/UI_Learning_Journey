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
    enum class DataType { INT, STRING, DATE };

    Database() = default;
    ~Database() = default;

    void createTable(string tableName,const vector<pair<string, Database::DataType>>& columns, int degree); //table with specific columns and data types
    void removeTable(string tableName);
    Table* getTable(string tableName);
};

#endif
