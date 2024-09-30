/*با توجه به پیشرفت‌های چشم‌گیر چین در حوزه کامپیوتر و نرم افزار، پاندای کنگفو کار به تازگی تصمیم گرفته تا این مهارت را با کمک استاد شیفو یاد بگیرد. او می‌خواهد که تمرین برنامه نویسی یک پیاده سازی کوچک انجام دهد. از آنجایی که او عاشق رشته پلو است، می‌خواهد رشته را در سی پلاس پلاس پیاده سازی کند. برای این کار به پو کمک کنید. برای پیاده سازی این رشته شما باید یک struct تعریف کنید که دو ویژگی آرایه‌ی کاراکتری و طول رشته را داراست. سپس شما باید توابع str_len و str_cpy و str_cmp را برای رشته‌ی خود بازنویسی کنید.
ورودی
در خط اول ورودی رشته‌ی اول و در خط دوم رشته دوم وارد می‌شود.

خروجی
در خط اول خروجی برنامه شما باید ابتدا با استفاده از تابع str_len نوشته شده توسط شما طول دو رشته را چاپ کند. سپس با استفاده از دستور str_cmp اگر دو رشته برابر بودند عبارت SHIFU چاپ شود. اگر نه با استفاده از str_cpy جای دو رشته عوض شود و در دو خط بعدی چاپ شوند.
 */

#include <iostream>
using namespace std;

struct str{
    int l = 0;
    char stri[1000] = {};
};

int str_len(str x)
{
    int len =0;
    char* p = &x.stri[0];
    while(*p != '\0')
    {
        len++;
        p++;
    }
    return len;
}

int str_cmp(str x, str y)
{
    char* px = &x.stri[0];
    char* py = &y.stri[0];
    if(x.l != y.l) return false;
    while(*px != '\0')
    {
        if(*px != *py) return false;
        px++;
        py++;
    }
    return true;
}

void str_cpy(str &x, str &y)
{
    int lengthx = str_len(x);
    int lengthy = str_len(y);
    int l;
    if(lengthx >= lengthy) l=lengthx;
    else l=lengthy;

    for(int i=0; i<l; i++)
    {
        char tmp = x.stri[i];
        x.stri[i] = y.stri[i];
        y.stri[i] = tmp;
    }
}
int main() {
    struct str a;
    cin >> a.stri;
    a.l =  str_len(a);
    struct str b;
    cin >> b.stri;
    b.l = str_len(b);

    cout << str_len(a) << ' ' << str_len(b) << endl;
    if(str_cmp(a, b)) cout << "SHIFU";
    else
    {
        str_cpy(a, b);
        cout << a.stri << endl << b.stri;
    }

    return 0;
}
