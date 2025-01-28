
int RecommendationManager::calculateDegreeOfConnection(string &user1, string &user2)
{
    vector<string> path = bfsShortestPath(user1, user2);
    if (path.empty())
        return 0;
    int degree = path.size() - 1;
    return max(0, MAX_DEGREE_SCORE - degree); // امتیاز بیشتر برای درجه ارتباط کمتر
}
