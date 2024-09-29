#ifndef CUSTOMERCLASS_H
#define CUSTOMERCLASS_H

#include <QString>

class customerClass
{
public:
    customerClass(QString, QString);
    void set_name(QString);
    QString get_name() const;
    void set_pass(QString);
    QString get_pass() const;

private:
    QString name;
    QString pass;
};

#endif // CUSTOMERCLASS_H
