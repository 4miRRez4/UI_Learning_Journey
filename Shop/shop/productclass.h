#ifndef PRODUCTCLASS_H
#define PRODUCTCLASS_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QString>

class productClass
{
public:
    productClass(QString, double);
    void loadProductsFromFile(QString fileName);
    void set_name(QString);
    QString get_name();
    void set_price(double);
    double get_price();
private:
    QString name;
    double Price;
};

#endif // PRODUCTCLASS_H
