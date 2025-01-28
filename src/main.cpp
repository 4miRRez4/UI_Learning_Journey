#include "../include/dataBase.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    Database* db = new Database();

    // Define columns for the Users table
    vector<Table::Column> userColumns;
    Table::Column id("id", Table::DataType::INT, Table::IndexType::PRIMARY);
    Table::Column name("name", Table::DataType::STRING, Table::IndexType::UNIQUE);
    Table::Column dob("dateOfBirth", Table::DataType::DATE, Table::IndexType::NON_UNIQUE);
    
    userColumns.push_back(id);
    userColumns.push_back(name);
    userColumns.push_back(dob);

    // Create a Users table
    db->createTable("Users", userColumns, 2);

    // Get the Users table
    Table* usersTable = db->getTable("Users");
    if (usersTable) {
        // Add records
        usersTable->addRecord(1, {"1", "behdad Levine", "1374/8/10"});
        usersTable->addRecord(2, {"2", "aryan Li", "1370/10/17"});

        // Print all records
        cout << "Records in Users table:" << endl;
        usersTable->printAll();

        // Search for a record
        cout << "\nSearching for record with ID 1:" << endl;
        vector<string> record = usersTable->searchRecord(1);
        for (const auto& field : record) {
            cout << field << " ";
        }
        cout << endl;

        // Update a record
        cout << "\nUpdating record with ID 1:" << endl;
        usersTable->updateRecord(1, {"1", "behdad Levine", "1374/8/10", "XY", "CC", "Microsoft"});
        usersTable->printAll();

        // Remove a record
        cout << "\nRemoving record with ID 2:" << endl;
        usersTable->removeRecord(2);
        usersTable->printAll();
    } else {
        cout << "Failed to retrieve Users table." << endl;
    }

    // Remove the Users table
    db->removeTable("Users");
    return 0;
}
