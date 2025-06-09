#include<iostream>
#include<vector>
#include<cstdlib>
#include<string>
using namespace std;

class Date{
    public:
        //methods of class.(what functions do objects of this class have in common and we can do it outside of class)
        //constructor:(a special method used to initialize objects)(if we don't do this, it will default with no parameter)
        Date(int d, int m, int y);
        void set_date(int d, int m, int y);
        void print_date();
        void operator++();// void go_on_one_day(); //->operator overloading: giving special meaning to cpp operators.
        bool isEqual(Date d2);
        int compare(Date d2);
        string day_of_week();

        //setters: Setters: These are the methods used in OOPS feature which helps to set the value to private attributes in a class.
        //getters: These are the methods used in Object-Oriented Programming (OOPS) which helps to access the private attributes from a class.
        int get_day() { return day; }
        int get_month() { return month; }
        int get_year() { return year; }

    private:
        //fields of class.(what objects of this class have in common and we don't want to change them outside of class.)
        int day;
        int month;
        int year;
};

Date::Date(int d, int m, int y) // constructor
{
    set_date(d, m, y);
}

bool is_leap_year(int year) // Date helper(its not exclusively member method of date but we can use it in Date members)
{
    int r = year%33;
    return r==1 || r==5 || r==9 || r==13 || r==17 || r==22 || r==26 || r==30;
}

int days_of_month(int month, int year)
{
    if(month < 7)
        return 31;
    if((month > 6) && (month <12))
        return 30;
    if(month == 12)
        return (is_leap_year(year)) ? 30 : 29;
    else
        abort();
}

void Date::set_date(int d, int m, int y)
{
    // if (y < 0 || m < 1 || m > 12 || d < 1 ||
    //     (m<7 && d>31) || (m>6 && m<12 && d>30) ||
    //     (m==12 && is_leap_year(y) && d>30) ||
    //     (m==12 && !is_leap_year(y) && d>29))
    //     abort();

    if(y<0 || m<1 || m>12 || d<1 || d>days_of_month(m, y))
        abort();

    day = d;
    month = m;
    year = y;
}

void Date::print_date()
{
    cout << day << "/" << month << "/" << year << endl;
}

// void Date::go_on_one_day()
void Date::operator++()
{   
    day++;
    if(day>days_of_month(month, year))
    {
        day=1;
        month++;
        
        if(month > 12)
        {
            month = 1;
            year++;
        }
    }
}

bool Date::isEqual(Date d2)
{
    return day==d2.day && month==d2.month && year==d2.year;
}

int days_between(Date d1, Date d2)
{
    int status = d1.compare(d2);
    if(status == 0)
        return 0;
    else if(status == 1)
    {
        Date tmp = d1;
        d1 = d2;
        d2 = tmp;
    }

    int counter=0;
    while(!d1.isEqual(d2))
    {
        ++d1; // d1 has been called here by value, so there is no problem.
        counter++;
    }
    return counter;
}

Date str_to_date(string s)
{
    int slash_pos= s.find('/');
    int d = atoi(s.substr(0, slash_pos).c_str());
    s = s.substr(slash_pos+1);
    slash_pos = s.find('/');
    int m = atoi(s.substr(0, slash_pos).c_str());
    int y = atoi(s.substr(slash_pos+1).c_str());

    return Date(d,m,y);
}

int Date::compare(Date d2)
{
    if(year != d2.year)
        return (year < d2.year) ? -1:1;
    else if(month != d2.month)
        return (month < d2.month) ? -1:1;
    else if(day != d2.day)
        return (day < d2.day) ? -1:1;
    else
        return 0;
}

string Date::day_of_week()
{
    //"1 farvardin" considared as "jome"
    int totalDays = day;
    for(int m=1; m<month; m++)
        totalDays += days_of_month(m, year);
    
    int dayIndex = totalDays%7;
    switch(dayIndex)
    {
        case 1: return "Friday";
        case 2: return "Saturday";
        case 3: return "Sunday";
        case 4: return "Monday";
        case 5: return "Tuesday";
        case 6: return "Wednesday";
        case 7: return "Thursday";
    }
    return "";
}

int main()
{
    //Date bd; //if class had default constructor
    Date bd(15,12,1383);
    Date fd(12,1,1383);
    //  bd.print_date();
    // fd.set_date(28,3,1383);
    // bd.print_date();
    bd.operator++();
    ++bd;
    bd.print_date();
    // cout << bd.get_day() << endl;
    // cout << bd.get_month() << endl;

    // cout << bd.isEqual(fd) << endl;
    // cout << days_between(bd, fd) << endl;

    // str_to_date("12/11/1393").print_date();

    // cout << bd.compare(fd) << endl;
    // cout << fd.day_of_week() << endl;

    return 0;
}