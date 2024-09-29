#include "customerclass.h"

customerClass::customerClass(QString n, QString p)
{
    this->name = n;
    this->pass = p;
}
QString customerClass::get_name() const { return this->name;}
void customerClass::set_name(QString n) { this->name = n;}
QString customerClass::get_pass() const{ return this->pass;}
void customerClass::set_pass(QString p) { this->pass = p;}

