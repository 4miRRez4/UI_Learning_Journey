#include <iostream>
#include <algorithm>
using namespace std;

class makhraj_sefr {};

class Rational{
    public:
    Rational(long long s, long long m);
    Rational(long long s) : Rational(s,1) {};
    Rational(Rational& r) { this->sorat = r.sorat; this->makhraj = r.makhraj;}

    void print();
    void simplify();
    Rational operator*(const Rational q2);

    private:
    long long sorat;
    long long makhraj;
};
Rational::Rational(long long s, long long m)
{
    if(m==0)
        throw makhraj_sefr();
    sorat = s;
    makhraj = m;
}

// string num_to_string(long long a)
// {
//     long long reversed=0;
//     while(a!=0)
//     {
//         reversed*=10;
//         reversed += a%10;
//         a/=10;
//     }
//     string out = "";
//     do
//     {
//         out += reversed%10 + '0';
//         reversed/=10;
//     }while(reversed!=0);
//     return out;
// }

void Rational::print()
{
    if(makhraj == 0)
        cout << "INVALID" << endl;
    else if(makhraj == 1)
        cout << sorat << endl;
    else 
        cout << sorat << " " << makhraj << endl;
}

// long long findGCD(long long a, long long b)
// {
//     if(b == 0) return a;
//     return findGCD(b, a%b);
// }

void Rational::simplify()
{
    long long gcd = __gcd(sorat, makhraj);
    sorat = sorat/gcd;
    makhraj = makhraj/gcd;
    if(makhraj <0)
    {
        sorat *=-1;
        makhraj *=-1;
    }
}

Rational Rational::operator*(const Rational q2)
{
    Rational multiplied(1,1);
    multiplied.makhraj = this->makhraj * q2.makhraj;
    multiplied.sorat = this->sorat * q2.sorat;
    multiplied.simplify();
    return multiplied;
}

int main() {
    long long numOfOperations; cin >> numOfOperations;

    for(long long c=0; c<numOfOperations; c++)
    {
        long long s1,s2,m1,m2; cin >> s1 >> m1 >> s2 >> m2;
        try{
            Rational a(s1, m1);
            Rational b(s2, m2);
            Rational answer = a*b;
            answer.print();
        }catch(makhraj_sefr exc)
        {
            cout << "INVALID" << endl;
        }
    }
    return 0;
}