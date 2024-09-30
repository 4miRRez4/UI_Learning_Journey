//https://quera.org/course/assignments/65747/problems/223325
//exercising concepts of oop with class car
#include <iostream>
using namespace std;

class Car
{
    public:
    Car(string _color, string _company, int _model);
    Car(string _color, string _company);
    Car(string _color);
    private:
    string color;
    string company;
    int model;

};
Car::Car(string _car, string _company, int _model)
{
    color = _car;
    company = _company;
    model = _model;
}
Car::Car(string _car, string _company)
{
    Car(_car, _company, 0);
}
Car::Car(string _car)
{
    Car(_car,"default",0);
}


int main()
{
    Car myCar("peykan", "iranKhodro", 1382);


    return 0;
}