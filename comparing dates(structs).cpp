/*پس از کشف تکنولوژی سفر در زمان توسط قورباغه‌ها در سیاره‌ی Dumeron L46، مشکلات بسیاری در این سیاره پیش آمده. گروه قور قور تا ابد برای حل مشکل در حال سفر در زمان هستند اما نمی‌توانند به طور دقیق زمان سفر خود را مشخص کنند و نیاز به برنامه‌ای دارند که مشخص کند در زمان درست سفر کرده اند یا خیر. از آنجایی که با دستان قورباغه‌ای تایپ کردن در کامپیوتر کار آسانی نیست، آنها از زمین کمک خواسته اند تا برای حل این مشکل یک برنامه سی پلاس پلاس طراحی کنند. شما باید یک struct با ویژگی‌های ساعت، دقیقه، ثانیه، روز، ماه و سال تعریف کنید. سپس یک تابع بنویسید که در ورودی دو struct دریافت می‌کند و و آن دو را مقایسه می‌کند. در صورت برابر بودن مثلا روز، ماه، سال، ساعت و دقیقه، مقایسه باید بر اساس ثانیه صورت گیرد.

ورودی
در دو خط اول ورودی به ترتیب دو تاریخ به صورت yyyy mm dd hh mm ss وارد می‌شوند.

خروجی
در تنها خط خروجی اگر تاریخ اول بزرگتر بود باید عبارت LATE، اگر تاریخ دوم بزرگتر بود عبارت SOON و اگر کاملا برابر بودند عبارت RIGHT چاپ شود.
*/

#include <iostream>
#include <cstring>
using namespace std;

struct date{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

char* compare(date a, date b)
{
    //comparing years;
    if(a.year > b.year) return "LATE";
    else if(a.year < b.year) return "SOON";
    //comparing months;
    else if(a.month > b.month) return "LATE";
    else if(a.month < b.month) return "SOON";
    //comparing days:
    else if(a.day > b.day) return "LATE";
    else if(a.day < b.day) return "SOON";
    //comparing hours;
    else if(a.hour > b.hour) return "LATE";
    else if(a.hour < b.hour) return "SOON";
    //comparing minuts;
    else if(a.minute > b.minute) return "LATE";
    else if(a.minute < b.minute) return "SOON";
    //comparing seconds;
    else if(a.second > b.second) return "LATE";
    else if(a.second < b.second) return "SOON";
    else return "RIGHT";

}

int main() {
    struct date a;
    cin >> a.year >> a.month >> a.day >> a.hour >> a.minute >> a.second;
    struct date b;
    cin >> b.year >> b.month >> b.day >> b.hour >> b.minute >> b.second;

    cout << compare(a, b);

    return 0;
}
