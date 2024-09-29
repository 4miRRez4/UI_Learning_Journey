#ifndef CUSTOMERSIGNUP_H
#define CUSTOMERSIGNUP_H

#include "customerlogin.h"
#include "custmainpage.h"
#include <iostream>
#include <QMessageBox>

namespace Ui {
class customerSignUp;
}

class customerSignUp : public  QDialog
{
    Q_OBJECT

public:
    explicit customerSignUp(QVector<customerClass> *customer, QWidget *parent = nullptr);
    ~customerSignUp();

private slots:
    void on_signUpButt_clicked();

private:
    Ui::customerSignUp *ui;
    QVector<customerClass> *customers;
};

#endif // CUSTOMERSIGNUP_H
