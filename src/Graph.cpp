#include "../include/Graph.h"
int Graph::numVertices()
{
    return users.size();
}

vector<string> Graph::vertices()
{
    vector<string> vList;
    for (auto &id : users)
    {
        vList.push_back(id.first);
    }
    return vList;
}

int Graph::numEdges()
{
    int count = 0;
    for (auto &edge : adjacencyList)
    {
        count += edge.second.size();
    }
    return count / 2;
}

vector<pair<string, string>> Graph::edges()
{
    vector<pair<string, string>> eList;
    for (auto &edge : adjacencyList)
    {
        string u = edge.first;
        for (auto &v : edge.second)
        {
            if (u < v)
            {
                eList.push_back({u, v});
            }
        }
    }
    return eList;
}
pair<string, string> Graph::getEdge(string u, string v)
{
    if (adjacencyList.find(u) != adjacencyList.end())
    {
        for (string &neighbor : adjacencyList.at(u))
        {
            if (neighbor == v)
            {
                return {u, v};
            }
        }
    }
    return {"", ""};
}

pair<string, string> Graph::endVertices(pair<string, string> edge)
{
    return edge;
}
string Graph::opposite(string v, pair<string, string> edge)
{
    if (edge.first == v)
    {
        return edge.second;
    }
    else if (edge.second == v)
    {
        return edge.first;
    }
    return "";
}

int Graph::outDegree(string v)
{
    if (adjacencyList.find(v) != adjacencyList.end())
    {
        return adjacencyList.at(v).size();
    }
    return 0;
}
int Graph::inDegree(string v)
{
    int count = 0;
    for (auto &it : adjacencyList)
    {
        for (auto &neighbor : it.second)
        {
            if (neighbor == v)
            {
                count++;
                break;
            }
        }
    }
    return count;
}
vector<string> Graph::outgoingEdges(string v)
{
    return adjacencyList[v];
}
vector<string> Graph::incomingEdges(string v)
{
    vector<string> eList;
    for (auto &it : adjacencyList)
    {
        for (auto &neighbor : it.second)
        {
            if (neighbor == v)
            {
                eList.push_back(it.first);
                break;
            }
        }
    }
    return eList;
}
void Graph::insertVertex(User &user)
{
    string id = user.getId();
    if (users.find(id) == users.end())
    {
        users[id] = user;
        adjacencyList[id] = vector<string>();
    }
}
void Graph::insertEdge(string v, string u)
{
    if (users.find(v) != users.end() && users.find(u) != users.end())
    {
        adjacencyList[v].push_back(u);
        adjacencyList[u].push_back(v);

        users[v].addConnection(u);
        users[u].addConnection(v);
    }
}
void Graph::removeVertex(string &v)
{
    if (users.find(v) != users.end())
    {
        users.erase(v);
        adjacencyList.erase(v);
        for (auto &pair : adjacencyList)
        {
            auto &neighbors = pair.second;
            neighbors.erase(remove(neighbors.begin(), neighbors.end(), v), neighbors.end());
        }
    }
}

void Graph::removeEdge(string v, string u)
{
    if (users.find(v) != users.end() && users.find(u) != users.end())
    {
        adjacencyList[v].erase(remove(adjacencyList[v].begin(), adjacencyList[v].end(), u), adjacencyList[v].end());
        adjacencyList[u].erase(remove(adjacencyList[u].begin(), adjacencyList[u].end(), v), adjacencyList[u].end());

        users[v].removeConnection(u);
        users[u].removeConnection(v);
    }
}

User Graph::getUser(string id)
{
    if (users.find(id) != users.end())
    {
        return users.at(id);
    }
    throw std::runtime_error("User not found");
}

void Graph::viewAllUsers()
{
    cout << "List of users..." << endl;
    for (auto &pair : users)
    {
        cout << "ID : " << pair.second.getId() << ", Name :" << pair.second.getName() << endl;
    }
}

void Graph::viewUserDetails(string id)
{
    if (users.find(id) != users.end())
    {
        const User &user = users.at(id);

        std::cout << "User Details:\n";
        std::cout << "ID: " << user.getId() << "\n";
        std::cout << "Name: " << user.getName() << "\n";
        std::cout << "Date of Birth: " << user.getDateOfBirth() << "\n";
        std::cout << "University Location: " << user.getUniversityLocation() << "\n";
        std::cout << "Field: " << user.getField() << "\n";
        std::cout << "Workplace: " << user.getWorkplace() << "\n";
        std::cout << "Specialties: ";
        for (const std::string &specialty : user.getSpecialties())
        {
            std::cout << specialty << ", ";
        }
        std::cout << "\nConnections: ";
        for (const std::string &connectionId : user.getConnections())
        {
            std::cout << connectionId << ", ";
        }
        std::cout << "\n";
    }
    else
    {
        std::cerr << "Error: User with ID " << id << " not found.\n";
    }
}
vector<string> Graph::getKeyUsers(int n, const string &metric)
{ // Get top N key users based on a centrality metric;
    vector<pair<string, double>> centralityScores;
    for (auto &it : users)
    {
        string userId = it.first;
        double score = 0.0;
        if (metric == "degree")
        {
            score = degreeCentrality(userId);
        }
        else if (metric == "page rank")
        {
            unordered_map<string, double> pageRankScores = PageRankCentrality();
            score = pageRankScores[userId];
        }

        centralityScores.push_back({userId, score});
    }

    sort(centralityScores.begin(), centralityScores.end(), [](pair<string, double> &a, pair<string, double> &b)
         { return a.second > b.second; });

    vector<string> keyUsers;
    for (int i = 0; i < min(n, (int)centralityScores.size()); i++)
    {
        keyUsers.push_back(centralityScores[i].first);
    }
    return keyUsers;
}

int Graph::degreeCentrality(string userId)
{
    if (adjacencyList.find(userId) != adjacencyList.end())
    {
        return adjacencyList.at(userId).size();
    }
    return 0;
}

unordered_map<string, double> Graph::PageRankCentrality(double dampingFactor, int maxIterations, double tolerance)
{
    const size_t numUsers = users.size();
    vector<string> userIds(numUsers);
    unordered_map<string, int> userToIndex;

    // Create mappings between user IDs and indices
    int idx = 0;
    for (const auto &user : users)
    {
        userIds[idx] = user.first;
        userToIndex[user.first] = idx++;
    }

    // Initialize score vectors
    vector<double> currentScores(numUsers, 1.0 / numUsers);
    vector<double> newScores(numUsers);

    // Pre-calculate outgoing edges count
    vector<int> outDegrees(numUsers, 0);
    for (int i = 0; i < numUsers; i++)
    {
        outDegrees[i] = adjacencyList[userIds[i]].size();
    }

    // PageRank iteration
    for (int iter = 0; iter < maxIterations; iter++)
    {
        fill(newScores.begin(), newScores.end(), (1.0 - dampingFactor) / numUsers);

        // Calculate dangling node contribution once per iteration
        double danglingSum = 0.0;
        for (int i = 0; i < numUsers; i++)
        {
            if (outDegrees[i] == 0)
            {
                danglingSum += currentScores[i];
            }
        }
        double danglingContribution = dampingFactor * danglingSum / numUsers;

        // Add dangling contribution to all nodes
        for (int i = 0; i < numUsers; i++)
        {
            newScores[i] += danglingContribution;
        }

// Calculate new scores
#pragma omp parallel for schedule(dynamic, 50)
        for (int i = 0; i < numUsers; i++)
        {
            const string &userId = userIds[i];
            for (const string &inNeighbor : adjacencyList[userId])
            {
                int inIdx = userToIndex[inNeighbor];
                if (outDegrees[inIdx] > 0)
                {
                    newScores[i] += dampingFactor * currentScores[inIdx] / outDegrees[inIdx];
                }
            }
        }

        // Check convergence
        double diff = 0.0;
        for (int i = 0; i < numUsers; i++)
        {
            diff += abs(newScores[i] - currentScores[i]);
        }

        if (diff < tolerance)
        {
            break;
        }

        currentScores.swap(newScores);
    }

    // Convert back to unordered_map with user IDs
    unordered_map<string, double> result;
    for (int i = 0; i < numUsers; i++)
    {
        result[userIds[i]] = currentScores[i];
    }

    return result;
}
void Graph::saveToJSON(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    nlohmann::ordered_json jsonData; // استفاده از ordered_json برای حفظ ترتیب
    file >> jsonData;
    file.close();

    // تبدیل JSON به map برای دسترسی سریع بر اساس ID
    unordered_map<string, nlohmann::ordered_json> userMap;
    for (const auto &userData : jsonData)
    {
        string id = userData["id"];
        userMap[id] = userData;
    }

    // به‌روزرسانی اطلاعات و کانکشن‌های کاربران
    for (const auto &pair : users)
    {
        const User &user = pair.second;
        string userId = user.getId();

        if (userMap.find(userId) != userMap.end())
        {
            userMap[userId]["connectionId"] = user.getConnections();
        }
        else
        {
            nlohmann::ordered_json newUser;
            newUser["id"] = user.getId();
            newUser["name"] = user.getName();
            newUser["dateOfBirth"] = user.getDateOfBirth();
            newUser["universityLocation"] = user.getUniversityLocation();
            newUser["field"] = user.getField();
            newUser["workplace"] = user.getWorkplace();
            newUser["specialties"] = user.getSpecialties();
            newUser["connectionId"] = user.getConnections();
            userMap[userId] = newUser;
        }
    }

    // ساخت یک آرایه مرتب برای حفظ ترتیب اولیه کاربران
    nlohmann::ordered_json updatedJsonData = nlohmann::ordered_json::array();
    for (const auto &userData : jsonData)
    {
        string id = userData["id"];
        if (userMap.find(id) != userMap.end())
        {
            updatedJsonData.push_back(userMap[id]);
        }
    }

    // اضافه کردن کاربران جدید (اگر باشند)
    for (const auto &pair : userMap)
    {
        if (find_if(jsonData.begin(), jsonData.end(), [&](const nlohmann::ordered_json &u)
                    { return u["id"] == pair.first; }) == jsonData.end())
        {
            updatedJsonData.push_back(pair.second);
        }
    }

    // ذخیره تغییرات در فایل
    ofstream outFile(filename);
    if (!outFile.is_open())
    {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }
    outFile << updatedJsonData.dump(4); // فرمت مرتب و خوانا
    outFile.close();
}