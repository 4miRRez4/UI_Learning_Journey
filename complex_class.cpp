#include <iostream>
using namespace std;

class Complex
{
    public:
    //constructors
    Complex(double r, double i) : real(r), img(i) {} //{ real = r; img = i;}
    Complex(double r) : real(r), img(0) {}
    void print() const;
    Complex operator+(const Complex& c) const;
    Complex operator+(double r) const;
    Complex& operator+=(const Complex& c);

    double re() const { return real; }
    double im() const { return img; }

    friend ostream& operator<<(ostream& out, const Complex& c);
    private:
    double real;
    double img;

};
void Complex::print() const
{
    cout << real;
    if(img > 0)
        cout << '+' << img << 'i';
    else if(img < 0)
        cout << img << 'i';
}

Complex operator+(const double r, const Complex& c)
{
    return Complex(c.re() + r, c.im());
}

Complex Complex::operator+(double r) const
{
    return Complex(real + r, img);
}

Complex Complex::operator+(const Complex& c) const
{
    return Complex(real + c.real, img + c.img);
}

Complex& Complex::operator+=(const Complex& c)
{
    real += c.real;
    img += c.img;
    return *this;
}

ostream& operator<<(ostream& out, const Complex& c)
{
    out << c.real;
    if (c.img > 0)
        out << '+' << c.img << 'i';
    else if (c.img < 0)
        out << c.img << 'i';

    return out;
}

int main()
{
    Complex a(1, 2);
    Complex b(4, -2);

    cout << a << b << endl;
    cout << a << b;
    return 0;
}