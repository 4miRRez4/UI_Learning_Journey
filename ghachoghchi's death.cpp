//finding month and day of ghachoghchi murder with given day of year(365)
#include <iostream>
using namespace std;

int main()
{
    int day; cin >> day;

    int month, date, dayOfWeek;
    dayOfWeek = (day%7 == 0) ? 7 : day%7;

    if(day <= 186) //first six month of year(31 day)
    {
        month = day / 31;
        date = (day%31 == 0) ? 31:day%31;
    }else if(day <= 336) //5 month of second half of the year(30 day)
    {
        month = 6;
        month += ((day-186)/30 == 0) ? (day-186)/30: (day-186)/30 +1;
        date = ((day-186)/30 == 0) ? 30: (day-186)%30;
    }else //esfand(29 day)
    {
        month = 12;
        date = (day-336);
    }
    //can be outputed by switch case(i'm lazy to do so!)
    cout << dayOfWeek << endl << date << endl << month << endl;
    return 0;
}