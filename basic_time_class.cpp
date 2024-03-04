#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
using namespace std;

class Time
{
    public:
        Time(int m, int h);
        Time(int h);
        void change_time(int m, int h);
        int compare(Time t);
        string which_part_of_day();

        int get_min() { return min; }
        int get_hour() { return hour; }
    private:
        int min;
        int hour;
};

Time::Time(int m, int h) : min(m), hour(h) {}

Time::Time(int h) : min(0), hour(h) {}

void Time::change_time(int m, int h)
{
    min = m;
    hour = h;
}

int Time::compare(Time t)
{
    if(hour != t.hour)
        return (hour > t.hour) ? 1:-1;
    else if(min != t.min)
        return (min > t.min) ? 1:-1;
    else
        return 0;
}

Time str_to_time(string t)
{
    int colon_pos = t.find(':');
    int h = atoi(t.substr(0, colon_pos).c_str());
    int m = atoi(t.substr(colon_pos+1).c_str());
    return Time(m, h);
}

string Time::which_part_of_day()
{
    if(compare(str_to_time("12:00")) == -1)
        return "morning";
    if(compare(str_to_time("12:00")) == 0)
        return "noon";
    if(compare(str_to_time("17:00")) == -1)
        return "after noon";
    if(compare(str_to_time("20:00")) == -1)
        return "evening";
    else
        return "night";
        
    return "";
}

int main()
{
    Time now(8, 11);
    Time next(10);

    cout << next.get_hour() << endl;
    next.change_time(30, 22);
    cout << next.get_min() << endl;
    cout << now.compare(next) << endl;
    cout << str_to_time("11:26").get_hour() << endl;
    cout << now.which_part_of_day() << endl;
    cout << next.which_part_of_day() << endl;

    return 0; 
}