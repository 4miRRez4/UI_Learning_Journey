#include "../include/RecommendationManager.h"
RecommendationManager::RecommendationManager(Graph &g) : graph(g)
{
}

vector<string> RecommendationManager::getRecommandations(string &aimId, int numRecommendations)
{
    vector<string> recommendations;
    unordered_map<string, double> recommendationScores;
    User currentUser = graph.getUser(aimId);
    vector<string> allUsers = graph.vertices();
    for (string &otherUserId : allUsers)
    {
        if (otherUserId == aimId)
        {
            continue;
        }
        User otherUser = graph.getUser(otherUserId);

        int degreeScore = calculateDegreeOfConnection(aimId, otherUserId);
        int workplaceScore = calculateWorkplaceSimilarity(currentUser, otherUser);
        int skillScore = calculateSkillSimilarity(currentUser, otherUser);

        double normalizedDegreeScore = normalizeScore(degreeScore, MAX_DEGREE_SCORE);
        double normalizedWorkplaceScore = normalizeScore(workplaceScore, WORKPLACE_MATCH_SCORE);
        double normalizedSkillScore = normalizeScore(skillScore, SKILL_MATCH_SCORE * 10); // فرض حداکثر ۱۰ مهارت مشترک

        double totalScore =
            (normalizedDegreeScore * DEGREE_WEIGHT / 100.0) +
            (normalizedWorkplaceScore * WORKPLACE_WEIGHT / 100.0) +
            (normalizedSkillScore * SKILL_WEIGHT / 100.0);

        recommendationScores[otherUserId] = totalScore;
    }

    vector<pair<string, double>> sortedRecommendations(recommendationScores.begin(), recommendationScores.end());
    sort(sortedRecommendations.begin(), sortedRecommendations.end(), [](const pair<string, double> &a, const pair<string, double> &b)
         { return a.second > b.second; });

    for (int i = 0; i < min(numRecommendations, (int)sortedRecommendations.size()); i++)
    {
        recommendations.push_back(sortedRecommendations[i].first);
    }
    return recommendations;
}

void RecommendationManager::setWeightsConfig(WeightsConfig &weights)
{
    customWeights = weights;
}
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

int RecommendationManager::calculateSkillSimilarity(User &user1, User &user2)
{
    vector<string> user1_skill = user1.getSpecialties();
    vector<string> user2_skill = user2.getSpecialties();
    vector<string> common_skils;
    int i = 0, j = 0;
    while (i < user1_skill.size() && j < user2_skill.size())
    {
        if (user1_skill[i] == user2_skill[j])
        {
            common_skils.push_back(user1_skill[i]);
            i++;
            j++;
        }
        else if (user1_skill[i] < user2_skill[j])
        {
            i++;
        }
        else
        {
            j++;
        }
    }
    return common_skils.size() * SKILL_MATCH_SCORE;
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

double RecommendationManager::normalizeScore(int score, int maxScore)
{
    return static_cast<double>(score) / maxScore;
}