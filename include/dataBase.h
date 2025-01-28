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
    ~Database() = default;

    void createTable(string tableName, int degree);
    void removeTable(string tableName);
    Table* getTable(string tableName);
};

#endif
