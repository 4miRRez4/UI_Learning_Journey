#ifndef CUSTMAINPAGE_H
#define CUSTMAINPAGE_H

#include "customerclass.h"
#include "utility.h"
#include "customerclass.h"
#include "productclass.h"
#include <QMainWindow>
#include <QMapIterator>
#include <QSet>
#include "QTreeWidget"
#include "QDebug"
#include "QMessageBox"

namespace Ui {
class custMainPage;
}

class custMainPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit custMainPage(QVector<customerClass>::iterator *currentUsr, QWidget *parent = nullptr);

    ~custMainPage();

private slots:
    void showProducts();

    void on_addButt_clicked();

    void on_buyButt_clicked();


private:
    Ui::custMainPage *ui;
    QVector<customerClass>::iterator *currentUsr;
    QVector<productClass> *allProducts;
    QVector<productClass> *basketProducts;
    double *totalPrice;
    QSet<QString> addedItems;
};

#endif // CUSTMAINPAGE_H
