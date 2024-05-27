//ramtin khosravi chapter 17 exercise
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Date {
public:
    Date(int d, int m, int y);
    void set_date(int d, int m, int y);
    void print_date();
    void inc_one_day();
    bool equals(Date d);

    int get_day() { return day; }
    int get_month() { return month; }
    int get_year() { return year; }
private:
    int day;
    int month;
    int year;
};
                                                                                
Date::Date(int d, int m, int y)
{
    set_date(d, m, y);
}
                                                                                
bool is_leap_year(int year)
{
    int r = year % 33;
    return r==1 || r==5 || r==9 || r==13 || r==17 || r==22 || r==26 || r==30;
}

int days_of_month(int m, int y)
{
    if (m < 7)
        return 31;
    else if (m < 12)
        return 30;
    else if (m == 12)
        return is_leap_year(y) ? 30 : 29;
    else
        abort();
}

void Date::set_date(int d, int m, int y)
{
    if (y < 0 || m < 1 || m > 12 || d < 1 || d > days_of_month(m, y))
        abort();

    day = d;
    month = m;
    year = y;
}

void Date::inc_one_day()
{
    day++;
    if (day > days_of_month(month, year)) {
        day = 1;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
}

void Date::print_date()
{
    cout << day << '/' << month << '/' << year << endl;
}

bool Date::equals(Date d) {
    return day == d.day && month == d.month && year == d.year;
}

bool is_in_season(Date d, int season){
        return d.get_month() > 3*(season-1);
}
class c_is_in_season{
    public:
        c_is_in_season(int season) { s = season; }
        bool operator()(Date d) { return d.get_month() > 3*(s-1);}
    private:
        int s;
};
template<typename In, typename Pred>
In find_iff(In first, In last, Pred p, int season)
{
    while(first!=last && !p(*first)){
        ++first;
    }
    return first;
}

Date first_in_season(vector<Date> v, int season){
    vector<Date>::iterator it = v.begin();
    //printing using iterators
    // while(it!=v.end())
    // {
    //     it->print_date();
    //     ++it;
    // }
    // for (vector<Date>::iterator it2 = v.begin(); it2 != v.end(); ++it2)
    //     it2->print_date();

    //1: using iterators
    // for(vector<Date>::iterator it=v.begin(); it!=v.end(); it++)
    //     if(it->get_month() > 3*(season-1))
    //         return *it;
    // return Date(1,1,1);

    //2: using find_if and function pointer
    //using find_if in <algorithm> and function ptr
    // return *find_if(v.begin(), v.end(), is_in_season);

    //using find_if in <algorithm> and lambda expression for predicate
    // return *find_if(v.begin(), v.end(), [=](Date d) { return d.get_month() > 3*(season-1);});

    //using custom find_if and function ptr
    // return *find_iff(v.begin(), v.end(), is_in_season);

    //using find_if and class and overloading operator () (fuctors)
    return *find_if(v.begin(), v.end(), c_is_in_season(season));
}

template<class T, class Pred>
int count(T first, T last, Pred p){
    int c=0;
    while(first != last){
        if(p(*first))
            c++;
        first++;
    }
    return c;
}

int main(){
    Date bd(30, 12, 1387);

    vector<Date> dates;
    dates.push_back(bd);
    dates.push_back(Date(1, 1, 1));
    first_in_season(dates, 2).print_date();

    cout << count_if(dates.begin(), dates.end(), [](Date d){ return d.get_month() > 6;});
    return 0;
}