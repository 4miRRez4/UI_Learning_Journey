#ifndef SETOPERATIONS_H
#define SETOPERATIONS_H

#include <set>
#include <string>
using namespace std;

namespace setOperations {
    template <typename T>
    set<T> unionSets(const set<T>& set1, const set<T>& set2);

    template <typename T>
    set<T> intersectionSets(const set<T>& set1, const set<T>& set2);

    template <typename T>
    set<T> differenceSets(const set<T>& set1, const set<T>& set2);
}

#include "../src/setOperations.tpp"

#endif 