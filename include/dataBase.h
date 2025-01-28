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

    void createTable(const std::string& tableName, int degree);
    void dropTable(const std::string& tableName);
    Table* getTable(const std::string& tableName);

    void printAll() const;
};

#endif
