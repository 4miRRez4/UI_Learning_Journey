#ifndef COMMUNICATIONQUALITY_H
#define COMMUNICATIONQUALITY_H

#pragma once
#include "graph.h"
#include <unordered_map>
class CommunicationQuality
{
public:
    CommunicationQuality(Graph &g) : graph(g) {}
    double assessQuality(string &userId1, string &userId2);
private:
    Graph &graph;

    // scoring weights
    const double SAME_CONNECTIONS = 0.4;
    const double SAME_SPECIALITY = 0.3;
    const double SAME_WORKPLACE = 0.3;

    double calculateSameConnections(string &userId1, string &userId2);
    double calculateSameSpeciality(User &user1, User &user2);
    double calculateSameWorkplace(User &user1, User &user2);
};

#endif