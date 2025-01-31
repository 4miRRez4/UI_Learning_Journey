#include <iostream>
#include "../include/cli.h"
#include "../include/aggregation_methods.h"

using namespace std;

void displayMenu() {
    cout << "========== Social Media Menu ==========" << endl;
    cout << "1. Create Table" << endl;
    cout << "2. Insert Record" << endl;
    cout << "3. Update Record" << endl;
    cout << "4. Delete Record" << endl;
    cout << "5. Search Record" << endl;
    cout << "6. Print All Records" << endl;
    cout << "7. Create Index" << endl;
    cout << "8. Aggregation" << endl;
    cout << "10. Range Query" << endl;
    cout << "11. Exit" << endl;
    cout << "========================================" << endl;
    cout << "Enter your choice: ";
}

void createTable(Database* db) {
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
        cout << "Data type (int/string/date/double): ";
        cin >> colType;
        cout << "Index type(unique/non-unique): ";
        cin >> indexType;

        Table::DataType dataType;
        if (colType == "int") 
            dataType = Table::DataType::INT;
        else if (colType == "string") 
            dataType = Table::DataType::STRING;
        else if (colType == "date")
            dataType = Table::DataType::DATE;
        else if (colType == "double") 
            dataType = Table::DataType::DOUBLE;
        else {
            cout << "Invalid column data type. Skipping column..." << endl;
            continue;
        }

        Table::IndexType it;
        if(indexType == "unique")
            it = Table::IndexType::UNIQUE;
        else if(indexType == "non-unique")
            it = Table::IndexType::NON_UNIQUE;
        else{
            cout << "Invalid index type. Skipping column..." << endl;
            continue;
        }

        Table::Column newCol(colName, dataType, it);
        columns.push_back(newCol);
    }

    db->createTable(tableName, columns, 3);
}
vector<Value> getColumnsValues(const vector<Table::Column>& cols){
    vector<Value> values;
    for(int i=0; i<cols.size(); i++) {
        const auto& col = cols[i];
        string value;
        cout << "Enter value for " << col.name << ": ";
        cin >> value;

        if (col.type == Table::DataType::INT) {
            size_t pos;
            int intValue = stoi(value, &pos);
                
            if (pos != value.length()) {
                throw invalid_argument("Invalid integer.");
            }
            
            values.push_back(intValue);
        }  
        else if (col.type == Table::DataType::DOUBLE) {
            size_t pos;
            int doubleValue = stod(value, &pos);
                
            if (pos != value.length()) {
                throw invalid_argument("Invalid double.");
            }
            
            values.push_back(doubleValue);
        }
        else if(col.type == Table::DataType::DATE){
            Date date = Date::fromString(value);   
            values.push_back(date);  
        }
        else {
            values.push_back(value); //store as string
        } 
    }
    return values;
}

void insertRecord(Database* db) {
    string tableName;
    cout << "Enter table name: ";
    cin >> tableName;

    Table* table = db->getTable(tableName);
    if (!table) {
        cout << "No table named: " << tableName << endl;
        return;
    }

    const vector<Table::Column>& cols = table->getColumns();
    vector<Value> values;
    try{
        values = getColumnsValues(cols);
    }catch (const invalid_argument& e) {
        cout << "Invalid input." << endl;
        return ;
    }
    
    table->addRecord(values);
}

void updateRecord(Database* db) {
    string tableName;
    cout << "Enter table name: ";
    cin >> tableName;

    Table* table = db->getTable(tableName);
    if (!table) {
        cout << "No table named: " << tableName << endl;
        return;
    }

    int id;
    cout << "Enter ID of record to update: ";
    cin >> id;

    const auto& cols = table->getColumns();
    vector<Value> values = getColumnsValues(cols);

    table->updateRecord(id, values);
}

void deleteRecord(Database* db) {
    string tableName;
    cout << "Enter table name: ";
    cin >> tableName;

    Table* table = db->getTable(tableName);
    if (!table) {
        cout << "No table named: " << tableName << endl;
        return;
    }

    int id;
    cout << "Enter ID of record to delete: ";
    cin >> id;

    table->removeRecord(id);
}

void searchRecord(Database* db) { 
    string tableName;
    cout << "Enter table name: ";
    cin >> tableName;

    Table* table = db->getTable(tableName);
    if (!table) {
        cout << "No table named: " << tableName << endl;
        return;
    }

    int id;
    cout << "Enter ID to search: ";
    cin >> id;

    Table::Record record = table->searchRecord(id);
    for (const auto& value : record.rowData){
        string stred_val;
        if (holds_alternative<string>(value)) {
            stred_val = get<string>(value);
        } else if (holds_alternative<int>(value)) {
            stred_val = to_string(get<int>(value));
        } else if (holds_alternative<double>(value)) {
            stred_val = to_string(get<double>(value));
        } else if (holds_alternative<Date>(value)){
            stred_val = get<Date>(value).toString();
        }
        cout << stred_val << " ";
    }
    cout << endl;
}

void createIndex(Database* db) {
    string tableName, colName;
    int indexType;

    cout << "Enter table name: ";
    cin >> tableName;

    Table* table = db->getTable(tableName);
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

bool validateColumn(Database* db, string columnName, Table*& table) {
    vector<Table::Column> tableCols = table->getColumns();
    auto col_it = find_if(tableCols.begin(), tableCols.end(), [&](const Table::Column& col) {
        return col.name == columnName;
    });

    if (col_it == tableCols.end()) {
        cout << "No column named " << columnName << " in the table " << table->name << endl;
        return false;
    }

    return true;
}

function<string(const vector<Value>&)> getAggregationFunc() {
    string aggFunc;
    cout << "Aggregation function (sum/avg/min/max): ";
    cin >> aggFunc;

    if (aggFunc == "sum") 
        return Aggregation::sum;
    else if (aggFunc == "avg") 
        return Aggregation::average;
    else if (aggFunc == "min") 
        return Aggregation::min;
    else if (aggFunc == "max") 
        return Aggregation::max;
    
    cout << "Invalid aggregation function." << endl;
    return nullptr;
}


void performAggregation(Database* db) {
    string tableName, columnName, aggType;
    cout << "Enter table name: ";
    cin >> tableName;

    Table* table = db->getTable(tableName);
    if (!table) {
        cout << "No table named: " << tableName << endl;
        return;
    }

    cout << "Enter column name: ";
    cin >> columnName;

    if (!validateColumn(db, columnName, table)) {
        return;
    }

    function<string(const vector<Value>&)> func = getAggregationFunc();

    vector<string> result = table->aggregate(columnName, func);
    cout << "Aggregation result: " << result[0] << endl;
}


void printAllRecords(Database* db) {
    string tableName;
    cout << "Enter table name: ";
    cin >> tableName;

    Table* table = db->getTable(tableName);
    if (!table) {
        cout << "No table named: " << tableName << endl;
        return;
    }

    table->printAll();
}

// void rangeQuery(Database* db) {
//     string tableName, columnName;
//     cout << "Enter table name: ";
//     cin >> tableName;

//     Table* table = db->getTable(tableName);
//     if (!table) {
//         cout << "No table named: " << tableName << endl;
//         return;
//     }

//     cout << "Enter column name for range query: ";
//     cin >> columnName;

//     vector<Table::Column> tableCols = table->getColumns();
//     auto col_it = find_if(tableCols.begin(), tableCols.end(), [&](const Table::Column& col) {
//         return col.name == columnName;
//     });

//     if (col_it == tableCols.end()) {
//         cout << "No column named " << columnName << " in the table " << tableName << endl;
//         return;
//     }

//     if (col_it->indexType != Table::PRIMARY && !table->hasIndex(columnName)) {
//         cout << "Column is not indexed. Range queries require an index.\n";
//         return;
//     }

//     cout << "Enter lower bound: ";
//     string lowerStr;
//     cin >> lowerStr;
//     cout << "Enter upper bound: ";
//     string upperStr;
//     cin >> upperStr;

//     vector<string> result;
//     if (col_it->type == Table::DataType::INT) {
//         int lower = stoi(lowerStr);
//         int upper = stoi(upperStr);
//         result = table->rangeQuery<int>(columnName, lower, upper);
//     } else if (col_it->type == Table::DataType::STRING) {
//         result = table->rangeQuery<string>(columnName, lowerStr, upperStr);
//     } else {
//         cout << "Unsupported data type for range query.\n";
//         return;
//     }

//     cout << "Range Query Results:\n";
//     for (const auto& entry : result) {
//         cout << entry << endl;
//     }
// }


void handleUserInput(Database* db) {
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
            // case 9: rangeQuery(db); break;
            case 10: return;
            default: cout << "Invalid choice. Try again." << endl;
        }
    }
}