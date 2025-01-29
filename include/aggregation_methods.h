#ifndef AGGREGATION_METHODS_H
#define AGGREGATION_METHODS_H

#include <string>
#include <vector>
using namespace std;

namespace Aggregation {

string sum(const vector<string>& values) {
    int sum = 0;
    for (int i = 0; i < values.size(); ++i) {
        sum += stoi(values[i]);
    }
    return to_string(sum);
}

string average(const vector<string>& values) {
    int sum = 0;
    for (int i = 0; i < values.size(); ++i) {
        sum += stoi(values[i]);
    }
    return to_string(static_cast<double>(sum) / values.size());
}

string min(const vector<string>& values) {
    if (values.empty()) return "empty values in min()."; // Handle empty case

    int minVal = stoi(values[0]);
    for (int i = 1; i < values.size(); ++i) {
        int val =stoi(values[i]);
        if (val < minVal) {
            minVal = val;
        }
    }
    return to_string(minVal);
}

string max(const vector<string>& values) {
    if (values.empty()) return "empty values in max().";

    int maxVal = stoi(values[0]); 
    for (size_t i = 1; i < values.size(); ++i) {
        int val = stoi(values[i]);
        if (val > maxVal) {
            maxVal = val;
        }
    }
    return to_string(maxVal);
}

}

#endif
