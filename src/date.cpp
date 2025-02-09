#include "../include/date.h"

using namespace std;

Date::Date() : year(0), month(0), day(0) {}

Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}

Date Date::fromString(const string dateStr) {
    //"YYYY/MM/DD" to Date
    int y, m, d;
    char slash1, slash2;
    istringstream ss(dateStr);
    
    if (!(ss >> y >> slash1 >> m >> slash2 >> d) || slash1 != '/' || slash2 != '/') {
        cout << "Invalid date format." << endl;
        return Date();
    }

    if (m < 1 || m > 12 || d < 1 || d > 31) {  
        cout << "Invalid date format." << endl;
        return Date();
    }

    return Date(y, m, d);
}

string Date::toString() const {
    ostringstream ss;
    ss << year << "/" << setw(2) << setfill('0') << month
       << "/" << setw(2) << setfill('0') << day;
    return ss.str();
}

bool Date::operator<(const Date& other) const {
    return tie(year, month, day) < tie(other.year, other.month, other.day);
}

bool Date::operator<=(const Date& other) const {
    return tie(year, month, day) <= tie(other.year, other.month, other.day);
}

bool Date::operator>(const Date& other) const {
    return tie(year, month, day) > tie(other.year, other.month, other.day);
}

bool Date::operator>=(const Date& other) const {
    return tie(year, month, day) >= tie(other.year, other.month, other.day);
}



bool Date::operator==(const Date& other) const {
    return year == other.year && month == other.month && day == other.day;
}
