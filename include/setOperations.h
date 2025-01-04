#ifndef SETOPERATIONS_H
#define SETOPERATIONS_H

#include <set>
#include <string>
using namespace std;

namespace setOperations {
    set<string> unionSets(const set<string>& set1, const set<string>& set2);
    set<string> intersectionSets(const set<string>& set1, const set<string>& set2);
    set<string> differenceSets(const set<string>& set1, const set<string>& set2);
}

#endif 