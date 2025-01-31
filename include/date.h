#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class Date {
private:
    int year, month, day;

public:
    Date();
    Date(int y, int m, int d);

    static Date fromString(const string dateStr);
    string toString() const;

    bool operator<(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator>=(const Date& other) const;
    bool operator==(const Date& other) const;
};

#endif
