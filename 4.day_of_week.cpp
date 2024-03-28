#include <iostream>
using namespace std;

int month_to_int(string month)
{
    int m;
    switch(month[0])
    {
        case 'F':
            return 1;
        case 'O':
            return 2;
        case 'K':
            return 3;
        case 'T':
            return 4;
        case 'M':
            if(month[1] == 'o')
                return 5;
            else
                return 7;
        case 'S':
            return 6;
        case 'A':
            if(month[1] == 'b')
                return 8;
            else
                return 9;
        case 'D':
            return 10;
        case 'B':
            return 11;
        case 'E':
            return 12;
    }
    return 0;
}

int days_of_month(int month)
{
    if(month < 7)
        return 31;
    if(month == 12)
        return 29;
    if(month > 6)
        return 30;

    return 0;
}

int total_days(int date, string month)
{
    int days=0;
    int m = month_to_int(month);

    for(int i=1; i<m; i++)
        days += days_of_month(i);
    days += date;
    return days;
}

int weekDay_to_int(string weekDay)
{
    switch(weekDay[0])
    {
        case 's':
            return 1;
        case '1':
            return 2;
        case '2':
            return 3;
        case '3':
            return 4;
        case '4':
            return 5;
        case '5':
            return 6;
        case 'j':
            return 7;
    }
    return 0;
}

string int_to_weekDay(int wk)
{
    switch(wk)
    {   
        case 1:
            return "shanbe";
        case 2:
            return "1shanbe";
        case 3:
            return "2shanbe";
        case 4:
            return "3shanbe";
        case 5:
            return "4shanbe";
        case 6:
            return "5shanbe";
        case 7:
            return "jome";
    }
    return 0;
}

int main()
{
    int t; cin >> t;
    while(t--)
    {
        int date; cin >> date;
        string month; cin >> month;
        string weekDay; cin >> weekDay;
        int nDate; cin >> nDate;
        string nMonth; cin >> nMonth;

        int tDays1 = total_days(date, month);
        int tDays2 = total_days(nDate, nMonth);

        if(tDays2 > tDays1)
        {
            int mod = (tDays2 - tDays1)%7;
            int wk = weekDay_to_int(weekDay);
            int newWk = (wk+mod) == 7 ? 7 : (wk+mod)%7;
            cout << int_to_weekDay(newWk) << endl;
        }else
        {
            int mod = (tDays1 - tDays2)%7;
            int wk = weekDay_to_int(weekDay);
            int newWk = (wk-mod) == 7 ? 7 : 7+(wk-mod)%7;
            if(newWk > 7)
                newWk = newWk%7;
            cout << int_to_weekDay(newWk) << endl;
        }
    }


    return 0;
}