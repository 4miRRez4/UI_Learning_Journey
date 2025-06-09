#include <iostream>
using namespace std;


//برنامه‌ای بنويسيد كه یک عدد صحيح را که تعداد ارقامش مشخص نيست از کاربر گرفته و هر رقم را به تعداد آن رقم چاپ کند
int main()
{
    long long n; cin >> n;

    int digit;//calculating reverse of given number
    long long reversed=0, p=1;
    while(n>0)
    {
        digit = n%10;
        reversed = reversed*10 + digit;
        n /= 10;
    }

    while(reversed>0)//iterating on reversed number;
    {
        digit = reversed%10;

        //printing condition for specific digit
        cout << digit << ": ";
        for(int i=0; i<digit; i++)
            cout << digit;
        cout << endl;

        //updating
        reversed /= 10;
    }


    return 0;
}