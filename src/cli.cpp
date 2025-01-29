#include <iostream>
#include "cli.h"
#include "aggregation_methods.h"

using namespace std;

void displayMenu() {
    cout << "========== Social Media Menu ==========" << endl;
    cout << "1. Create Table";
    cout << "2. Insert Record";
    cout << "3. Update Record";
    cout << "4. Delete Record";
    cout << "5. Search Record";
    cout << "6. Print All Records";
    cout << "7. Create Index";
    cout << "8. Perform Aggregation";
    cout << "9. Exit";
    cout << "===========================================\n";
    cout << "Enter number: ";
}

void createTable(Database& db) {
    string tableName;
    cout << "Enter table name: ";
    cin >> tableName;

    int numOfCol;
    cout << "Enter number of columns: ";
    cin >> numOfCol;

    vector<Table::Column> columns;
    for (int i = 0; i < numOfCol; i++) {
        string colName, colType, indexType;
        cout << "Column " << (i + 1) << " name: ";
        cin >> colName;
        cout << "Data type (int/string/date): ";
        cin >> colType;
        cout << "Index type(primary/unique/non-unique): ";
        cin >> indexType;

        Table::DataType dataType;
        if (colType == "int") 
            dataType = Table::DataType::INT;
        else if (colType == "string") 
            dataType = Table::DataType::STRING;
        else if (colType == "date")
            dataType = Table::DataType::DATE;
        else {
            cout << "Invalid column data type. Skipping column..." << endl;
            continue;
        }

        Table::IndexType it;
        if(indexType == "primary")
            it = Table::IndexType::PRIMARY;
        else if(indexType == "unique")
            it = Table::IndexType::UNIQUE;
        else if(indexType == "primary")
            it = Table::IndexType::NON_UNIQUE;
        else{
            cout << "Invalid index type. Skipping column..." << endl;
            continue;
        }

        Table::Column newCol(colName, dataType, it);
        columns.push_back(newCol);
    }

    db.createTable(tableName, columns, 3);
    cout << "Table '" << tableName << "' created successfully.\n";
}

void insertRecord(Database& db) {
    string tableName;
    cout << "Enter table name: ";
    cin >> tableName;

    Table* table = db.getTable(tableName);
    if (!table) {
        cout << "No table named: " << tableName << endl;
        return;
    }

    vector<string> values;
    cout << "We assume that first column is primary." << endl;
    for (const auto& col : table->getColumns()) {
        string value;
        cout << "Enter value for " << col.name << ": ";
        cin >> value;
        values.push_back(value);
    }

    int id = stoi(values[0]);
    table->addRecord(id, values);
    cout << "Record inserted successfully.\n";
}
void updateRecord(Database& db) {
    string tableName;
    cout << "Enter table name: ";
    cin >> tableName;

    Table* table = db.getTable(tableName);
    if (!table) {
        cout << "No table named: " << tableName << endl;
        return;
    }

    int id;
    cout << "Enter ID of record to update: ";
    cin >> id;

    vector<string> values;
    for (const auto& col : table->getColumns()) {
        string value;
        cout << "Enter new value for " << col.name << ": ";
        cin >> value;
        values.push_back(value);
    }

    table->updateRecord(id, values);
    cout << "Record updated successfully.\n";
}

void deleteRecord(Database& db) {
    string tableName;
    cout << "Enter table name: ";
    cin >> tableName;

    Table* table = db.getTable(tableName);
    if (!table) {
        cout << "No table named: " << tableName << endl;
        return;
    }

    int id;
    cout << "Enter ID of record to delete: ";
    cin >> id;

    table->removeRecord(id);
    cout << "Record deleted successfully.\n";
}

void searchRecord(Database& db) {
    string tableName;
    cout << "Enter table name: ";
    cin >> tableName;

    Table* table = db.getTable(tableName);
    if (!table) {
        cout << "No table named: " << tableName << endl;
        return;
    }

    int id;
    cout << "Enter ID to search: ";
    cin >> id;

    vector<string> record = table->searchRecord(id);
    if (!record.empty()) {
        cout << "Record found: ";
        for (const auto& value : record) 
            cout << value << " ";
        cout << endl;
    } else {
        cout << "Record not found.\n";
    }
}

void createIndex(Database& db) {
    string tableName, colName;
    int indexType;

    cout << "Enter table name: ";
    cin >> tableName;

    Table* table = db.getTable(tableName);
    if (!table) {
        cout << "No table named: " << tableName << endl;
        return;
    }

    cout << "Enter column name to index: ";
    cin >> colName;

    cout << "Enter index type (0: PRIMARY, 1: UNIQUE, 2: NON_UNIQUE): ";
    cin >> indexType;

    if (indexType < 0 || indexType > 2) {
        cout << "Invalid index type." << endl;
        return;
    }

    table->createIndex(colName, static_cast<Table::IndexType>(indexType), 3);
    cout << "Index created successfully." << endl;
}


void performAggregation(Database& db) {
    string tableName, columnName, aggType;
    cout << "Enter table name: ";
    cin >> tableName;

    Table* table = db.getTable(tableName);
    if (!table) {
        cout << "No table named: " << tableName << endl;
        return;
    }

    cout << "Enter column name: ";
    cin >> columnName;
    cout << "Aggregation function (sum/avg/min/max): ";
    cin >> aggType;

    function<string(const vector<string>&)> func;
    if (aggType == "sum") 
        func = Aggregation::sum;
    else if (aggType == "avg") 
        func = Aggregation::average;
    else if (aggType == "min") 
        func = Aggregation::min;
    else if (aggType == "max") 
        func = Aggregation::max;
    else {
        cout << "Invalid aggregation function." << endl;
        return;
    }

    vector<string> result = table->aggregate(columnName, func);
    cout << "Aggregation result: " << result[0] << endl;
}

void handleUserInput(Database& db) {
    int choice;
    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: createTable(db); break;
            case 2: insertRecord(db); break;
            case 3: updateRecord(db); break;
            case 4: deleteRecord(db); break;
            case 5: searchRecord(db); break;
            case 6: printAllRecords(db); break;
            case 7: createIndex(db); break;
            case 8: performAggregation(db); break;
            case 0: return;
            default: cout << "Invalid choice. Try again.\n";
        }
    }
}