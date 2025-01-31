#include "../include/Interface.h"
void Interface::clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Interface::waitForEnter()
{
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    clearScreen();
}

void Interface::showLoginMenu()
{
    clearScreen();
    cout << "=== Social Network Login ===\n";
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. Exit\n";
    cout << "Choose an option: ";

    int choice;
    cin >> choice;
    cin.ignore();

    switch (choice)
    {
    case 1:
        handleLogin();
        break;
    case 2:
        handleRegistration();
        break;
    case 3:
        cout << "Goodbye!\n";
        exit(0);
    default:
        cout << "Invalid option!\n";
        waitForEnter();
    }
}

void Interface::handleLogin()
{
    clearScreen();
    cout << "=== Login ===\n";
    cout << "Enter username (your full name): ";
    string username;
    getline(cin, username);

    vector<string> allUser = graph.vertices();
    for (string &userId : allUser)
    {
        User user = graph.getUser(userId);
        if (user.getName() == username)
        {
            currentUser = userId;
            cout << "Login successful!\n";
            waitForEnter();
            return;
        }
    }
    cout << "User not found!\n";
    waitForEnter();
}

void Interface::handleRegistration()
{
    clearScreen();
    cout << "=== New User Registration ===\n";

    // Generate new ID
    string id = to_string(graph.numVertices() + 1);
    cout << "Enter your name: ";
    string name;
    getline(cin, name);

    cout << "Enter date of birth (YYYY-MM-DD): ";
    string dob;
    getline(cin, dob);

    cout << "Enter university location: ";
    string university;
    getline(cin, university);

    cout << "Enter field of study: ";
    string field;
    getline(cin, field);

    cout << "Enter workplace: ";
    string workplace;
    getline(cin, workplace);

    vector<string> specialties;
    cout << "Enter specialties (enter 'done' when finished):\n";
    while (true)
    {
        string specialty;
        getline(cin, specialty);
        if (specialty == "done")
            break;
        specialties.push_back(specialty);
    }

    // New user starts with no connections
    vector<string> connections;

    User newUser(id, name, dob, university, field, workplace, specialties, connections);
    graph.insertVertex(newUser);

    saveGraphToJSON();
    cout << "Registration successful! Your ID is: " << id << "\n";
    waitForEnter();
}

void Interface::showMainMenu()
{
    while (true)
    {
        clearScreen();
        cout << "=== Main Menu === (Logged in as: " << graph.getUser(currentUser).getName() << ")\n";
        cout << "1. Social Network Menu\n";
        cout << "2. Database Management Menu\n";
        cout << "3. Logout\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            showSocialNetworkMenu();
            break;
        case 2:
            showDatabaseMenu();
            break;
        case 3:
            currentUser = "";
            cout << "Logged out successfully!\n";
            waitForEnter();
            return;
        default:
            cout << "Invalid option!\n";
            waitForEnter();
        }
    }
}

void Interface::showSocialNetworkMenu()
{
    while (true)
    {
        cout << "=== Main Menu === (Logged in as: " << graph.getUser(currentUser).getName() << ")\n";
        cout << "1. View Profile\n";
        cout << "2. View All Users\n";
        cout << "3. View User Details\n";
        cout << "4. View Recommendations\n";
        cout << "5. View Recommendations for Another User\n";
        cout << "6. Connect with User\n";
        cout << "7. Remove Connection\n";
        cout << "8. view key users\n";
        cout << "9. View Communication Quality\n";
        cout << "10. Return to Main Menu\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;
        cin.ignore();
        clearScreen();
        if (choice == 10)
        {
            break;
        }
        switch (choice)
        {
        case 1:
            graph.viewUserDetails(currentUser);
            break;
        case 2:
            graph.viewAllUsers();
            break;
        case 3:
            handleViewUserDetails();
            break;
        case 4:
            handleViewRecommendations(currentUser);
            break;
        case 5:
            handleViewRecommendationsForOther();
            break;
        case 6:
            handleConnect();
            break;
        case 7:
            handleRemoveConnection();
            break;
        case 8:
            handleViewKeyUsers();
            break;
        case 9:
            handleCommunicationQuality();
            break;
        default:
            cerr << "Invalid option\n";
        }
        waitForEnter();
    }
}
void Interface::handleViewUserDetails()
{
    cout << "Enter you ID: ";
    string userId;
    getline(cin, userId);

    try
    {
        graph.viewUserDetails(userId);
    }
    catch (const std::runtime_error &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

void Interface::handleViewRecommendations(string &userId)
{
    while (true)
    {
        // clearScreen();
        cout << "\n=== Recommendations for " << graph.getUser(userId).getName() << " ===\n";

        // Show current weights
        cout << "\nCurrent Weights Configuration:\n";
        cout << "1. Degree of Connection: " << recManager.getCurrentWeights().degreeWeight << "%\n";
        cout << "2. Workplace Match: " << recManager.getCurrentWeights().workplaceWeight << "%\n";
        cout << "3. Skill Match: " << recManager.getCurrentWeights().skillWeight << "%\n";

        // Show recommendations
        vector<string> recommendations = recManager.getRecommandations(const_cast<string &>(userId));
        cout << "\nTop 20 Recommendations:\n";
        int count = 0;
        for (const string &recId : recommendations)
        {
            if (count >= 20)
                break;
            User recUser = graph.getUser(recId);
            cout << count + 1 << ". " << recUser.getName() << " (ID: " << recId << ")\n";
            count++;
        }

        // Options menu
        cout << "\nOptions:\n";
        cout << "1. Customize weights\n";
        cout << "2. Reset weights to default\n";
        cout << "3. Return to main menu\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            cout << "\nEnter new weights (must sum to 100):\n";
            int degreeWeight, workplaceWeight, skillWeight;

            while (true)
            {
                cout << "Degree of Connection weight (0-100): ";
                cin >> degreeWeight;

                cout << "Workplace Match weight (0-100): ";
                cin >> workplaceWeight;

                cout << "Skill Match weight (0-100): ";
                cin >> skillWeight;

                if (degreeWeight + workplaceWeight + skillWeight != 100)
                {
                    cout << "Error: Weights must sum to 100. Please try again.\n";
                    continue;
                }

                try
                {
                    RecommendationManager::WeightsConfig newWeights(degreeWeight, workplaceWeight, skillWeight);
                    recManager.setWeightsConfig(newWeights);
                    cout << "Weights updated successfully!\n";
                    break;
                }
                catch (const invalid_argument &e)
                {
                    cout << "Error: " << e.what() << "\nPlease try again.\n";
                }
            }
            cin.ignore();
        }
        else if (choice == 2)
        {
            recManager.resetWeightsConfig();
            cout << "Weights reset to default values.\n";
            waitForEnter();
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            cout << "Invalid option!\n";
            waitForEnter();
        }
    }
}

void Interface::handleViewRecommendationsForOther()
{
    cout << "Enter user ID: ";
    string userId;
    getline(cin, userId);

    try
    {
        handleViewRecommendations(userId);
    }
    catch (const std::runtime_error &e)
    {
        cerr << "Error: " << e.what() << '\n';
    }
}

void Interface::handleConnect()
{
    cout << "Enter user ID to connect with: ";
    string userId;
    getline(cin, userId);

    try
    {
        graph.insertEdge(currentUser, userId);
        saveGraphToJSON();
        cout << "Connected successfully with " << graph.getUser(userId).getName() << endl;
    }
    catch (const std::runtime_error &e)
    {
        cout << "Error: " << e.what() << endl;
    }
}

void Interface::handleRemoveConnection()
{
    cout << "Enter user ID to remove connection: ";
    string userId;
    getline(cin, userId);

    try
    {
        graph.removeEdge(currentUser, userId);
        saveGraphToJSON();
        cout << "Connection removed successfully with " << graph.getUser(userId).getName() << endl;
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Interface::handleViewKeyUsers()
{
    cout << "=== View Key Users ===\n";
    cout << "Select metric:\n";
    cout << "1. Degree Centrality\n";
    cout << "2. Page Rank\n";
    cout << "Enter choice (1-2): ";

    int choice;
    cin >> choice;
    cin.ignore();

    string metric = (choice == 1) ? "degree" : "page rank";

    cout << "Enter number of key users to view: ";
    int n;
    cin >> n;
    cin.ignore();

    vector<string> keyUsers = graph.getKeyUsers(n, metric);

    cout << "\nTop " << n << " Key Users (by " << metric << "):\n";
    for (int i = 0; i < keyUsers.size(); i++)
    {
        User user = graph.getUser(keyUsers[i]);
        cout << i + 1 << ". " << user.getName() << " (ID: " << user.getId() << ")\n";

        if (metric == "degree")
        {
            cout << "   Degree Centrality: " << graph.degreeCentrality(user.getId()) << "\n";
        }
        else
        {
            // For PageRank, you might want to store the scores when calculating them
            // and display them here
            auto scores = graph.PageRankCentrality();
            cout << "   PageRank Score: " << scores[user.getId()] << "\n";
        }
    }
}

void Interface::handleCommunicationQuality()
{
    cout << "=== Communication Quality Analysis ===\n";
    cout << "Choose an option:\n";
    cout << "1. View quality with specific user\n";
    cout << "2. View top quality connections\n";
    cout << "Enter choice (1-2): ";

    int choice;
    cin >> choice;
    cin.ignore();

    CommunicationQuality commQuality(graph);

    if (choice == 1)
    {
        cout << "Enter user ID to analyze communication quality: ";
        string targetId;
        getline(cin, targetId);

        try
        {
            double quality = commQuality.assessQuality(currentUser, targetId);
            cout << "\nCommunication Quality Analysis with " << graph.getUser(targetId).getName() << ":\n";
            cout << "Quality Score: " << quality * 100 << "%\n";
        }
        catch (const runtime_error &e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }
    else if (choice == 2)
    {
        cout << "Enter number of top connections to view: ";
        int limit;
        cin >> limit;
        cin.ignore();

        vector<pair<string, double>> topConnections = commQuality.getTopConnections(currentUser, limit);

        cout << "\nTop " << limit << " Quality Connections:\n";
        for (int i = 0; i < topConnections.size(); i++)
        {
            User user = graph.getUser(topConnections[i].first);
            cout << i + 1 << ". " << user.getName()
                 << " (ID: " << user.getId() << ")"
                 << " - Quality Score: "
                 << topConnections[i].second * 100 << "%\n";
        }
    }
}

void Interface::showDatabaseMenu()
{
    while (true)
    {

        clearScreen();
        cout << "========== DataBase Menu ==========" << endl;
        cout << "1. Create Table" << endl;
        cout << "2. Insert Record" << endl;
        cout << "3. Update Record" << endl;
        cout << "4. Delete Record" << endl;
        cout << "5. Search By Id" << endl;
        cout << "6. Search By Column" << endl;
        cout << "7. Print All Records" << endl;
        cout << "8. Create Index" << endl;
        cout << "9. Aggregation" << endl;
        cout << "10. Range Query" << endl;
        cout << "11. Exit" << endl;
        cout << "====================================" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();
        // clearScreen();

        switch (choice)
        {
        case 1:
            createTable();
            break;
        case 2:
            insertRecord();
            break;
        case 3:
            updateRecord();
            break;
        case 4:
            deleteRecord();
            break;
        case 5:
            searchById();
            break;
        case 6:
            searchByColumn();
            break;
        case 7:
            printAllRecords();
            break;
        case 8:
            createIndex();
            break;
        case 9:
            performAggregation();
            break;
        case 10: 
            performRangeQuery(); break;
        case 11:
            return;
        default:
            cout << "Invalid choice. Try again." << endl;
        }

        waitForEnter();
    }
}

void Interface::createTable()
{
    string tableName;
    cout << "Enter table name: ";
    cin >> tableName;

    int numOfCol;
    cout << "Enter number of columns: ";
    cin >> numOfCol;

    vector<Table::Column> columns;
    for (int i = 0; i < numOfCol; i++)
    {
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
        else
        {
            cout << "Invalid column data type. Skipping column..." << endl;
            continue;
        }

        Table::IndexType it;
        if (indexType == "unique")
            it = Table::IndexType::UNIQUE;
        else if (indexType == "non-unique")
            it = Table::IndexType::NON_UNIQUE;
        else
        {
            cout << "Invalid index type. Skipping column..." << endl;
            continue;
        }

        Table::Column newCol(colName, dataType, it);
        columns.push_back(newCol);
    }

    db->createTable(tableName, columns, 3);
}

vector<Value> getColumnsValues(const vector<Table::Column> &cols)
{
    vector<Value> values;
    for (int i = 0; i < cols.size(); i++)
    {
        const auto &col = cols[i];
        string value;
        cout << "Enter value for " << col.name << ": ";
        cin >> value;

        if (col.type == Table::DataType::INT)
        {
            size_t pos;
            int intValue = stoi(value, &pos);

            if (pos != value.length())
            {
                throw invalid_argument("Invalid integer.");
            }

            values.push_back(intValue);
        }
        else if (col.type == Table::DataType::DOUBLE)
        {
            size_t pos;
            int doubleValue = stod(value, &pos);

            if (pos != value.length())
            {
                throw invalid_argument("Invalid double.");
            }

            values.push_back(doubleValue);
        }
        else if (col.type == Table::DataType::DATE)
        {
            Date date = Date::fromString(value);
            values.push_back(date);
        }
        else
        {
            values.push_back(value); // store as string
        }
    }
    return values;
}

void Interface::insertRecord()
{
    string tableName;
    cout << "Enter table name: ";
    cin >> tableName;

    Table *table = db->getTable(tableName);
    if (!table)
    {
        cout << "No table named: " << tableName << endl;
        return;
    }

    const vector<Table::Column> &cols = table->getColumns();
    vector<Value> values;
    try
    {
        values = getColumnsValues(cols);
    }
    catch (const invalid_argument &e)
    {
        cout << "Invalid input." << endl;
        return;
    }

    table->addRecord(values);
}

void Interface::updateRecord()
{
    string tableName;
    cout << "Enter table name: ";
    cin >> tableName;

    Table *table = db->getTable(tableName);
    if (!table)
    {
        cout << "No table named: " << tableName << endl;
        return;
    }

    int id;
    cout << "Enter ID of record to update: ";
    cin >> id;

    const auto &cols = table->getColumns();
    vector<Value> values = getColumnsValues(cols);

    table->updateRecord(id, values);
}

void Interface::deleteRecord()
{
    string tableName;
    cout << "Enter table name: ";
    cin >> tableName;

    Table *table = db->getTable(tableName);
    if (!table)
    {
        cout << "No table named: " << tableName << endl;
        return;
    }

    int id;
    cout << "Enter ID of record to delete: ";
    cin >> id;

    table->removeRecord(id);
}

void Interface::searchById()
{
    string tableName;
    cout << "Enter table name: ";
    cin >> tableName;

    Table *table = db->getTable(tableName);
    if (!table)
    {
        cout << "No table named: " << tableName << endl;
        return;
    }

    int id;
    cout << "Enter ID to search: ";
    cin >> id;

    Table::Record record = table->searchRecordById(id);
    vector<Table::Column> cols = table->getColumns();
    for (int i=0; i<cols.size(); i++)
    {
        cout << cols[i].name << ": ";
        string stred_val = table->ValueToStr(record.rowData[i]);
        cout << stred_val << " | ";
    }
    cout << endl;
}

void Interface::searchByColumn()
{
    string tableName;
    cout << "Enter table name: ";
    cin >> tableName;

    Table *table = db->getTable(tableName);
    if (!table)
    {
        cout << "No table named: " << tableName << endl;
        return;
    }

    cout << "Columns: ";
    for (auto col : table->getColumns())
    {
        cout << col.name << " ";
    }
    cout << endl;

    string colName;
    cout << "Enter column name to search: ";
    cin >> colName;

    Table::DataType colType;
    for (auto col : table->getColumns())
    {
        if (col.name == colName)
        {
            colType = col.type;
            break;
        }
    }

    string inVal;
    cout << "Enter column value to search: ";
    cin >> inVal;

    Value val = table->strToValue(inVal, colType);

    vector<Value> results = table->searchByColumn(colName, val);
    if(results.empty())
        return;
        
    vector<Table::Column> cols = table->getColumns();
    for (int i=0; i<cols.size(); i++)
    {
        cout << cols[i].name << ": ";
        string stred_val = table->ValueToStr(results[i]);
        cout << stred_val << " | ";
    }
    cout << endl;
}

void Interface::createIndex()
{
    string tableName, colName;
    int indexType;

    cout << "Enter table name: ";
    cin >> tableName;

    Table *table = db->getTable(tableName);
    if (!table)
    {
        cout << "No table named: " << tableName << endl;
        return;
    }

    cout << "Enter column name to index: ";
    cin >> colName;

    for (auto col : table->getColumns())
    {
        if (colName == col.name)
            indexType = col.indexType;
    }

    table->createIndex(colName, static_cast<Table::IndexType>(indexType), 3);
    cout << "Index created successfully." << endl;
}

bool validateColumn(string columnName, Table *&table)
{
    vector<Table::Column> tableCols = table->getColumns();
    auto col_it = find_if(tableCols.begin(), tableCols.end(), [&](const Table::Column &col)
                          { return col.name == columnName; });

    if (col_it == tableCols.end())
    {
        cout << "No column named " << columnName << " in the table " << table->name << endl;
        return false;
    }

    return true;
}

function<string(const vector<Value> &)> getAggregationFunc()
{
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

void Interface::performAggregation()
{
    string tableName, columnName, aggType;
    cout << "Enter table name: ";
    cin >> tableName;

    Table *table = db->getTable(tableName);
    if (!table)
    {
        cout << "No table named: " << tableName << endl;
        return;
    }

    cout << "Enter column name: ";
    cin >> columnName;

    if (!validateColumn(columnName, table))
    {
        return;
    }

    function<string(const vector<Value> &)> func = getAggregationFunc();

    vector<string> result = table->aggregate(columnName, func);
    cout << "Aggregation result: " << result[0] << endl;
}

void Interface::performRangeQuery() {
    string tableName, colName, lowerStr, upperStr;
    
    cout << "Enter table name: ";
    cin >> tableName;

    Table* table = db->getTable(tableName);
    if (!table) {
        cout << "No table named: " << tableName << endl;
        return;
    }

    cout << "Enter column name: ";
    cin >> colName;

    cout << "Enter lower bound: ";
    cin >> lowerStr;

    cout << "Enter upper bound: ";
    cin >> upperStr;

    auto columns = table->getColumns();
    auto it = find_if(columns.begin(), columns.end(), [&](const Table::Column& col) { return col.name == colName; });

    if (it == columns.end()) {
        cout << "Column not found." << endl;
        return;
    }

    Value lower, upper;

    if (it->type == Table::DataType::INT) {
        lower = stoi(lowerStr);
        upper = stoi(upperStr);
    } 
    else if (it->type == Table::DataType::DOUBLE) {
        lower = stod(lowerStr);
        upper = stod(upperStr);
    } 
    else if (it->type == Table::DataType::DATE) {
        lower = Date::fromString(lowerStr);
        upper = Date::fromString(upperStr);
    } 
    else {
        lower = lowerStr;
        upper = upperStr;
    }

    vector<Value> results = table->rangeQuery(colName, lower, upper);

    cout << "Range query results: " << endl;
    for (const auto& value : results) {
        cout << table->ValueToStr(value) << " ";
    }
    cout << endl;
}


void Interface::printAllRecords()
{
    string tableName;
    cout << "Enter table name: ";
    cin >> tableName;

    Table *table = db->getTable(tableName);
    if (!table)
    {
        cout << "No table named: " << tableName << endl;
        return;
    }

    table->printAll();
}
