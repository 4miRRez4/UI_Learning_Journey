#include "../include/Graph.h"
#include "Graph.h"
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
    unordered_map<string, double> pageRank;
    vector<string> allUsers = vertices();
    size_t numUsers = allUsers.size();

    // Initialize PageRank scores
    double initialScore = 1.0 / numUsers;
    for (const string &user : allUsers)
    {
        pageRank[user] = initialScore;
    }

    // Iterate until convergence
    for (int iter = 0; iter < maxIterations; ++iter)
    {
        unordered_map<string, double> newPageRank;
        double danglingMass = 0.0;

        // Calculate new PageRank scores
        for (const string &user : allUsers)
        {
            if (adjacencyList[user].empty())
            {
                danglingMass += pageRank[user];
            }
            double sum = 0.0;
            for (const string &incomingUser : incomingEdges(user))
            {
                sum += pageRank[incomingUser] / adjacencyList[incomingUser].size();
            }
            newPageRank[user] = (1.0 - dampingFactor) / numUsers + dampingFactor * sum;
        }

        // Distribute dangling mass
        double danglingContribution = dampingFactor * danglingMass / numUsers;
        for (const string &user : allUsers)
        {
            newPageRank[user] += danglingContribution;
        }

        // Check for convergence
        double diff = 0.0;
        for (const string &user : allUsers)
        {
            diff += abs(newPageRank[user] - pageRank[user]);
        }
        if (diff < tolerance)
        {
            break;
        }

        pageRank = newPageRank;
    }

    return pageRank;
}
