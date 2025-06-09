#ifndef AGGREGATION_METHODS_H
#define AGGREGATION_METHODS_H

#include <string>
#include <vector>
#include <variant>
#include <limits>

using namespace std;

using Value = variant<int, double, string, Date>;

namespace Aggregation {

inline string sum(const vector<Value>& values) {
    double sum = 0;
    for (const auto& val : values) {
        if (holds_alternative<int>(val)) {
            sum += get<int>(val);
        } else if (holds_alternative<double>(val)) {
            sum += get<double>(val);
        } else{
            cout << "Invalid dataType for aggregation function, sum." << endl;
        }
    }
    return to_string(sum);
}

inline string average(const vector<Value>& values) {
    double sum = 0;
    int n = 0;
    for (const auto& val : values) {
        if (holds_alternative<int>(val)) {
            sum += get<int>(val);
            n++;
        } else if (holds_alternative<double>(val)) {
            sum += get<double>(val);
            n++;
        } else{
            cout << "Invalid data type for aggregation function, average." << endl;
        }
    }

    if (n == 0) return "0";
    return to_string(sum / n);
}

inline string min(const vector<Value>& values) {
    if (values.empty()) 
        return "empty values in aggregation function, min.";

    Value minVal = values[0];

    for (const auto& val : values) {
        if (holds_alternative<int>(val) && holds_alternative<int>(minVal)) {
            if (get<int>(val) < get<int>(minVal)) 
                minVal = val;
        } 
        else if (holds_alternative<double>(val) && holds_alternative<double>(minVal)) {
            if (get<double>(val) < get<double>(minVal)) 
                minVal = val;
        } 
        else if (holds_alternative<string>(val) && holds_alternative<string>(minVal)) {
            if (get<string>(val) < get<string>(minVal)) 
                minVal = val;
        } 
        else if (holds_alternative<Date>(val) && holds_alternative<Date>(minVal)) {
            if (get<Date>(val) < get<Date>(minVal)) 
                minVal = val;
        }
        else{
            cout << "Invalid data type for aggregation function, min." << endl;
        }
    }

    if (holds_alternative<int>(minVal)) 
        return to_string(get<int>(minVal));
    if (holds_alternative<double>(minVal)) 
        return to_string(get<double>(minVal));
    if (holds_alternative<Date>(minVal))
        return get<Date>(minVal).toString(); 
    return get<string>(minVal);
}

inline string max(const vector<Value>& values) {
    if (values.empty()) 
        return "empty values in aggregation function, max.";

    Value maxVal = values[0];

    for (const auto& val : values) {
        if (holds_alternative<int>(val) && holds_alternative<int>(maxVal)) {
            if (get<int>(val) > get<int>(maxVal)) 
                maxVal = val;
        }
        else if (holds_alternative<double>(val) && holds_alternative<double>(maxVal)) {
            if (get<double>(val) > get<double>(maxVal)) 
                maxVal = val;
        } 
        else if (holds_alternative<string>(val) && holds_alternative<string>(maxVal)) {
            if (get<string>(val) > get<string>(maxVal)) 
                maxVal = val;
        }
        else if (holds_alternative<Date>(val) && holds_alternative<Date>(maxVal)) {
            if (get<Date>(val) < get<Date>(maxVal)) 
                maxVal = val;
        }
        else{
            cout << "Invalid data type for aggregation function, max." << endl;
        }
    }

    if (holds_alternative<int>(maxVal)) 
        return to_string(get<int>(maxVal));
    if (holds_alternative<double>(maxVal)) 
        return to_string(get<double>(maxVal));
    if (holds_alternative<Date>(maxVal))
        return get<Date>(maxVal).toString(); 
    return get<string>(maxVal);
}

}

#endif
