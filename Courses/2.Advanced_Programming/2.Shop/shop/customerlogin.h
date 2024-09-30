#ifndef CUSTOMERLOGIN_H
#define CUSTOMERLOGIN_H

#include "custmainpage.h"
#include "mainwindow.h"
#include "utility.h"
#include "customerclass.h"
#include <QMapIterator>
#include <QDialog>
#include <customqmessagebox.h>
#include <QMap>
#include <QVector>
#include <algorithm>

namespace Ui {
class customerLogin;
}

class customerLogin : public QDialog
{
    Q_OBJECT

public:
    explicit customerLogin(QWidget *parent = nullptr);

    ~customerLogin();

private slots:
    void on_signUpButt_clicked();

    void on_logInButt_clicked();

private:
    Ui::customerLogin *ui;
    QVector<customerClass> *customers;
};

#endif // CUSTOMERLOGIN_H
