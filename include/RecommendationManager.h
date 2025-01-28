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
    RecommendationManager(Graph &graph);
private:
    static const int DEGREE_WEIGHT = 40;
    static const int WORKPLACE_WEIGHT = 35;
    static const int SKILL_WEIGHT = 25;
    static const int MAX_DEGREE_SCORE = 5;
    static const int WORKPLACE_MATCH_SCORE = 10;
    static const int SKILL_MATCH_SCORE = 5;
    Graph &graph;
    int calculateDegreeOfConnection(string &user1, string &user2);
