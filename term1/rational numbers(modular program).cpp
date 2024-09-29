/*
 در این سوال قصد داریم مکانیزم تعریف اعداد گویا را با کمک structure ها انجام دهیم .
می دانید که هر عدد گویا از یک صورت و یک مخرج تشکیل شده است. پس استراکتی تعریف کنید که دو فیلد صحیح صورت و مخرج داشته باشد به عنوان مثال:
struct Rational {
int a;
int b;
};
Plain text
سپس توابع زیر را بر اساس این ساختار پیاده سازی نمایید:
void get(Rational *i);
Plain text
این تابع صورت و مخرج عددی را دریافت کرده و آن را در آرگومان ورودی ذخیره می کند.
void print(Rational o);
Plain text
این تابع یک عدد گویا را به عنوان آرگومان دریافت کرده و به شکل صورت تقسیم بر مخرج چاپ می کند.
void simplify(Rational *q);
Plain text
این تابع یک عدد گویا را دریافت کرده و آن را ساده می کند.
Rational add(Rational q1, Rational q2);
Plain text
این تابع دو عدد گویا را دریافت کرده و حاصل جمع آنها را به ساده ترین شکل ممکن برمی گرداند.
Rational subtract(Rational q1, Rational q2);
Plain text
این تابع دو عدد گویا را دریافت کرده و حاصل تفریق آنها را به ساده ترین شکل ممکن برمی گرداند.
Rational multiply(Rational q1, Rational q2);
Plain text
این تابع دو عدد گویا را دریافت کرده و حاصل ضرب آنها را به ساده ترین شکل ممکن برمی گرداند.
Rational division(Rational q1, Rational q2);
Plain text
این تابع دو عدد گویا را دریافت کرده و حاصل تقسیم آنها را به ساده ترین شکل ممکن برمی گرداند.
سپس تابع main را به گونه ای بنویسید که ورودی و خروجی آن بدین شکل باشد: ورودی و خروجی ورودی برنامه شما تعدادی دستور است که با دستور end پایان می پذیرد. اولین دستور بدین شکل است:
new <lowercase letter>
Plain text
با این دستور برنامه یک عدد گویا را دریافت می کند و آن را به یک حرف کوچک انگلیسی که در دستور وارد شده است منتسب می کند.
سایر دستورات بدین فرم می باشند:
a+b
a-b
a*b
a/b
a
Plain text
دستور اول حاصل جمع، دستور دوم حاصل تفریق، دستور سوم حاصل ضرب، دستور چهارم حاصل تقسیم دو عدد گویای a و b و دستور آخر خود عدد a را نمایش می دهد.
 */

#include <iostream>
#include <cstring>
using namespace std;

struct Rational{
    int sorat;
    int makhraj;
};

void get(Rational *i)
{
    cin >> i->sorat;
    cin >> i->makhraj;
}

void print(Rational o)
{
    if(o.makhraj < 0)
        cout << -o.sorat << '/' << -o.makhraj << endl;
    else cout << o.sorat << '/' << o.makhraj << endl;
}

int findGCD(int a, int b)
{
    if(b == 0) return a;
    return findGCD(b, a%b);
}

void simplify(Rational *q)
{
    int gcd = findGCD(q->sorat, q->makhraj);
    q->sorat = (q->sorat)/gcd;
    q->makhraj = (q->makhraj)/gcd;
}

Rational add(Rational q1, Rational q2)
{
    Rational sum;
    sum.makhraj = q1.makhraj * q2.makhraj;
    sum.sorat = q2.makhraj*q1.sorat + q1.makhraj*q2.sorat;
    simplify(&sum);
    return sum;
}

Rational subtract(Rational q1, Rational q2)
{
    Rational minus;
    minus.makhraj = q1.makhraj * q2.makhraj;
    minus.sorat = q2.makhraj*q1.sorat - q1.makhraj*q2.sorat;
    simplify(&minus);
    return minus;
}

Rational multiply(Rational q1, Rational q2)
{
    Rational multiplied;
    multiplied.makhraj = q1.makhraj * q2.makhraj;
    multiplied.sorat = q1.sorat * q2.sorat;
    simplify(&multiplied);
    return multiplied;
}

Rational division(Rational q1, Rational q2)
{
    Rational divisioned;
    Rational tmp;
    tmp.makhraj = q2.sorat;
    tmp.sorat = q2.makhraj;
    divisioned = multiply(q1,tmp);
    return  divisioned;
}

int main() {

    Rational chars[26] ={};
    while (true)
    {
        char input[10];
        cin >> input;

        if(strcmp(input, "end") == 0) break;

        else if(strcmp(input, "new") == 0)
        {
            char variableName;
            cin >> variableName;

            get(&chars[variableName-97]);
        }
        else if(strlen(input) == 1) print(chars[input[0]-97]);
        else
        {
            Rational operand1 = chars[input[0]-97];
            Rational operand2 = chars[input[2]-97];
            char operation = input[1];
            switch (operation)
            {
                case '+':
                {
                    print(add(operand1, operand2));
                    break;
                }
                case '-':
                {
                    print(subtract(operand1, operand2));
                    break;
                }
                case '*':
                {
                    print(multiply(operand1, operand2));
                    break;
                }
                case '/':
                {
                    print(division(operand1, operand2));
                    break;
                }
            }

        }

    }

    return 0;
}
