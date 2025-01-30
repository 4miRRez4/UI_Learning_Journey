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

    cout << "Registration successful! Your ID is: " << id << "\n";
    waitForEnter();
}

void Interface::showMainMenu()
{
    while (true)
    {
        clearScreen();
        cout << "=== Main Menu === (Logged in as: " << graph.getUser(currentUser).getName() << ")\n";
        cout << "1. View Profile\n";
        cout << "2. View All Users\n";
        cout << "3. View User Details\n";
        cout << "4. View Recommendations\n";
        cout << "5. View Recommendations for Another User\n";
        cout << "6. Connect with User\n";
        cout << "7. Remove Connection\n";
        cout << "8. Logout\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;
        cin.ignore();

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

        default:
            break;
        }
    }
}
