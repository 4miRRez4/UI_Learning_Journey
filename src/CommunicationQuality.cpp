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
