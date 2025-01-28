
int RecommendationManager::calculateDegreeOfConnection(string &user1, string &user2)
{
    vector<string> path = bfsShortestPath(user1, user2);
    if (path.empty())
        return 0;
    int degree = path.size() - 1;
    return max(0, MAX_DEGREE_SCORE - degree); // امتیاز بیشتر برای درجه ارتباط کمتر
}

int RecommendationManager::calculateWorkplaceSimilarity(User &user1, User &user2)
{
    if (user1.getWorkplace() == user2.getWorkplace())
    {
        return WORKPLACE_MATCH_SCORE;
    }
    return 0;
}


vector<string> RecommendationManager::bfsShortestPath(string &start, string &target)
{
    unordered_map<string, string> parent;
    queue<string> q;
    q.push(start);
    parent[start] = "";
    while (!q.empty())
    {
        string current = q.front();
        q.pop();
        if (current == target)
        {
            vector<string> path;
            for (string v = current; v != ""; v = parent[v])
            {
                path.push_back(v);
            }
            reverse(path.begin(), path.end());
            return path;
        }
        for (string &neighbor : graph.outgoingEdges(current))
        {
            if (parent.find(neighbor) == parent.end())
            {
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }
    return {};
}
