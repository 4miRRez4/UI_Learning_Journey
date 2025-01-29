#ifndef RECOMMENDATIONMANAGER_H
#define RECOMMENDATIONMANAGER_H

#pragma once

#include "Graph.h"
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

class RecommendationManager
{
public:
    class WeightsConfig
    {
    public:
        // default weight
        int degreeWeight = 40;
        int workplaceWeight = 35;
        int skillWeight = 25;

        WeightsConfig() = default;
        WeightsConfig(int degreeW, int workplaceW, int skillW)
        {
            if (degreeW + workplaceW + skillW != 100)
            {
                throw std::invalid_argument("Invalid weights: sum of weights must be 100");
            }
            degreeWeight = degreeW;
            workplaceWeight = workplaceW;
            skillWeight = skillW;
        }
    };
    RecommendationManager(Graph &graph);
    vector<string> getRecommandations(string &userId, int numRecommendations = 20);

    void setWeightsConfig(WeightsConfig &weights);
    void resetWeightsConfig();
private:
    static const int MAX_DEGREE_SCORE = 5;
    static const int WORKPLACE_MATCH_SCORE = 10;
    static const int SKILL_MATCH_SCORE = 5;
    Graph &graph;
    WeightsConfig customWeights;
    int calculateDegreeOfConnection(string &user1, string &user2);
    int calculateWorkplaceSimilarity(User &user1, User &user2);
    int calculateSkillSimilarity(User &user1, User &user2);
    vector<string> bfsShortestPath(string &start, string &target);
    double normalizeScore(int score, int maxScore);
};

#endif