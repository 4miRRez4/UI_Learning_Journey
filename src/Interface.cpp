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
        // clearScreen();
        cout << "=== Database Management Menu ===\n";
        cout << "1. Create Table\n";
        cout << "2. Insert Record\n";
        cout << "3. Update Record\n";
        cout << "4. Delete Record\n";
        cout << "5. Search Record\n";
        cout << "6. Print All Records\n";
        cout << "7. Create Index\n";
        cout << "8. Perform Aggregation\n";
        cout << "9. Return to Main Menu\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;
        cin.ignore();
        // clearScreen();

        if (choice == 9)
            break;

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
            searchRecord();
            break;
        case 6:
            printAllRecords();
            break;
        case 7:
            createIndex();
            break;
        case 8:
            performAggregation();
            break;
        default:
            cout << "Invalid option!\n";
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
        else
        {
            cout << "Invalid column data type. Skipping column..." << endl;
            continue;
        }

        Table::IndexType it;
        if (indexType == "primary")
            it = Table::IndexType::PRIMARY;
        else if (indexType == "unique")
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
    cout << "Table '" << tableName << "' created successfully.\n";
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

    vector<string> values;
    cout << "We assume that first column is primary." << endl;
    for (const auto &col : table->getColumns())
    {
        string value;
        cout << "Enter value for " << col.name << ": ";
        cin >> value;
        values.push_back(value);
    }

    int id = stoi(values[0]);
    table->addRecord(id, values);
    cout << "Record inserted successfully." << endl;
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

    vector<string> values;
    for (const auto &col : table->getColumns())
    {
        string value;
        cout << "Enter new value for " << col.name << ": ";
        cin >> value;
        values.push_back(value);
    }

    table->updateRecord(id, values);
    cout << "Record updated successfully." << endl;
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
    cout << "Record deleted successfully." << endl;
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
    cout << "Aggregation function (sum/avg/min/max): ";
    cin >> aggType;

    function<string(const vector<string> &)> func;
    if (aggType == "sum")
        func = Aggregation::sum;
    else if (aggType == "avg")
        func = Aggregation::average;
    else if (aggType == "min")
        func = Aggregation::min;
    else if (aggType == "max")
        func = Aggregation::max;
    else
    {
        cout << "Invalid aggregation function." << endl;
        return;
    }

    vector<string> result = table->aggregate(columnName, func);
    cout << "Aggregation result: " << result[0] << endl;
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

    cout << "Enter index type (0: PRIMARY, 1: UNIQUE, 2: NON_UNIQUE): ";
    cin >> indexType;

    if (indexType < 0 || indexType > 2)
    {
        cout << "Invalid index type." << endl;
        return;
    }

    table->createIndex(colName, static_cast<Table::IndexType>(indexType), 3);
    cout << "Index created successfully." << endl;
}

void Interface::searchRecord()
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

    vector<string> record = table->searchRecord(id);
    if (!record.empty())
    {
        cout << "Record found: ";
        for (const auto &value : record)
            cout << value << " ";
        cout << endl;
    }
    else
    {
        cout << "Record not found." << endl;
    }
}
