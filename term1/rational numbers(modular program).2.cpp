//upgrading the program after learning class ,operator overloading and clean code
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
#include <vector>
using namespace std;

class Rational{
    public:
    Rational(int s, int m);
    Rational(int s) : Rational(s,1) {};

    string print();
    void simplify();
    Rational operator+(const Rational q2);
    Rational operator-(const Rational q2);
    Rational operator*(const Rational q2);
    Rational operator/(const Rational q2);
    private:
    int sorat;
    int makhraj;
};
Rational::Rational(int s, int m)
{
    if(m<0)
    {
        cout << "INVALID";
        return;
    }
    sorat = s;
    makhraj = m;
}

string Rational::print()
{
    string out = "";
    if(makhraj < 0)
        out += -sorat + '/' + -makhraj + '\n';
    else 
        out += sorat + '/' + makhraj + '\n';
    return out;
}

int findGCD(int a, int b)
{
    if(b == 0) return a;
    return findGCD(b, a%b);
}

void Rational::simplify()
{
    int gcd = findGCD(sorat, makhraj);
    sorat = sorat/gcd;
    makhraj = makhraj/gcd;
}

Rational Rational::operator+(const Rational q2)
{
    Rational sum(1,1);
    sum.makhraj = this->makhraj * q2.makhraj;
    sum.sorat = q2.makhraj*this->sorat + this->makhraj*q2.sorat;
    sum.simplify();
    return sum;
}

Rational Rational::operator-(const Rational q2)
{
    Rational minus(1,1);
    minus.makhraj = this->makhraj * q2.makhraj;
    minus.sorat = q2.makhraj*this->sorat - this->makhraj*q2.sorat;
    minus.simplify();

    return minus;
}

Rational Rational::operator*(const Rational q2)
{
    Rational multiplied(1,1);
    multiplied.makhraj = this->makhraj * q2.makhraj;
    multiplied.sorat = this->sorat * q2.sorat;
    multiplied.simplify();
    return multiplied;
}

Rational Rational::operator/(const Rational q2)
{
    Rational divisioned(1,1);
    Rational tmp(1,1);
    tmp.makhraj = q2.sorat;
    tmp.sorat = q2.makhraj;
    divisioned = this->operator*(tmp);
    return divisioned;
}

int main() {
    vector<Rational> rationals(26);
    while (true)
    {
        cout << "ENTER YOUR COMMAND SIR: ";
        char input[10];
        cin >> input;

        if(strcmp(input, "end") == 0) break;

        else if(strcmp(input, "new") == 0)
        {
            cout << "ENTER NAME OF NEW VARIABLE:(lower case character) ";
            char name; cin >> name;
            cout << "ENTER MAKHRAJ AND SORAT: ";
            int m, s; cin >> s >> m;  
            Rational n(s, m);
            rationals[name-97] = n;
        }
        else if(strlen(input) == 1) 
        {
            cout << rationals[input[0]-97].print() << endl;
        }
        else
        {
            Rational operand1 = rationals[input[0]-97];
            Rational operand2 = rationals[input[2]-97];
            char operation = input[1];
            switch (operation)
            {
                case '+':
                {
                    cout << (operand1+operand2).print() << endl;
                    break;
                }
                case '-':
                {
                    cout << (operand1-operand2).print() << endl;
                    break;
                }
                case '*':
                {
                    cout << (operand1*operand2).print() << endl;
                    break;
                }
                case '/':
                {
                    cout << (operand1*operand2).print() << endl;
                    break;
                }
            }

        }

    }

    return 0;
}
