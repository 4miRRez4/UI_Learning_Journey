#include "productclass.h"

productClass::productClass(QString n, double p)
{
    this->name = n;
    this->Price = p;
}

void productClass::set_name(QString n) { this->name = n;};
QString productClass::get_name() { return this->name;};
void productClass::set_price(double p) { this->Price = p;};
double productClass::get_price() { return this->Price;};

