/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *header;
    QPushButton *custButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(500, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("background-image: url(:/images/BG.png);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        header = new QLabel(centralWidget);
        header->setObjectName(QString::fromUtf8("header"));
        header->setGeometry(QRect(200, 50, 111, 41));
        header->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 75 24pt \"Ubuntu Mono\";\n"
""));
        custButton = new QPushButton(centralWidget);
        custButton->setObjectName(QString::fromUtf8("custButton"));
        custButton->setGeometry(QRect(130, 440, 261, 41));
        custButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 75 16pt \"Ubuntu Mono\";"));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        header->setText(QCoreApplication::translate("MainWindow", "WELCOME", nullptr));
        custButton->setText(QCoreApplication::translate("MainWindow", "Enter as a customer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
