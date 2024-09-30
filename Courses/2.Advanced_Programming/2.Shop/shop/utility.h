#ifndef UTILITY_H
#define UTILITY_H

#include "customerclass.h"
#include "productclass.h"
#include <QMessageBox>
#include <QWidget>
#include <QFile>
#include <QTextStream>


void emptyInputWarning(QWidget *parent);
void saveToFile(QString fileName, QVector<customerClass> *list);
void loadFromFile(QString fileName, QVector<customerClass> *list);
void loadProductsFromFile(QString fileName, QVector<productClass> *list);

#endif // UTILITY_H
