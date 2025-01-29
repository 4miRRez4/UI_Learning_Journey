double CommunicationQuality::calculateSameConnections(string &userId1, string &userId2)
{
    vector<string> connections1 = graph.outgoingEdges(userId1);
    vector<string> connections2 = graph.outgoingEdges(userId2);

    int common = 0;
    for (string &c : connections1)
    {
        if (find(connections2.begin(), connections2.end(), c) != connections2.end())
            common++;
    }
    int maxPossible = min(connections1.size(), connections2.size());
    return maxPossible > 0 ? static_cast<double>(common) / maxPossible : 0.0;
}
double CommunicationQuality::calculateSameSpeciality(User &user1, User &user2)
{
    vector<string> speciality1 = user1.getSpecialties();
    vector<string> speciality2 = user2.getSpecialties();

    int common = 0;
    for (string &s : speciality1)
    {
        if (find(speciality2.begin(), speciality2.end(), s) != speciality2.end())
            common++;
    }
    int maxPossible = min(speciality1.size(), speciality2.size());
    return maxPossible > 0 ? static_cast<double>(common) / maxPossible : 0.0;
}

double CommunicationQuality::calculateSameWorkplace(User &user1, User &user2)
{
    double score = 0.0;

    if (user1.getWorkplace() == user2.getWorkplace())
    {
        score += 0.6;
    }
    if (user1.getField() == user2.getField())
    {
        score += 0.4;
    }
    return score;
}
