/********************************************************************************
** Form generated from reading UI file 'customerlogin.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMERLOGIN_H
#define UI_CUSTOMERLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_customerLogin
{
public:
    QLabel *Header;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *userName;
    QLineEdit *nameIn;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *passWord;
    QLineEdit *passIn;
    QPushButton *logInButt;
    QLabel *signUp;
    QPushButton *signUpButt;

    void setupUi(QDialog *customerLogin)
    {
        if (customerLogin->objectName().isEmpty())
            customerLogin->setObjectName(QString::fromUtf8("customerLogin"));
        customerLogin->resize(500, 600);
        customerLogin->setStyleSheet(QString::fromUtf8("background-image: url(:/images/BG.png);"));
        Header = new QLabel(customerLogin);
        Header->setObjectName(QString::fromUtf8("Header"));
        Header->setGeometry(QRect(60, 40, 381, 31));
        Header->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 75 18pt \"Ubuntu Mono\";"));
        layoutWidget = new QWidget(customerLogin);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(90, 220, 311, 51));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        userName = new QLabel(layoutWidget);
        userName->setObjectName(QString::fromUtf8("userName"));
        userName->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 75 16pt \"Ubuntu Mono\";"));

        horizontalLayout->addWidget(userName);

        nameIn = new QLineEdit(layoutWidget);
        nameIn->setObjectName(QString::fromUtf8("nameIn"));
        nameIn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(nameIn);

        layoutWidget1 = new QWidget(customerLogin);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(90, 270, 311, 61));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        passWord = new QLabel(layoutWidget1);
        passWord->setObjectName(QString::fromUtf8("passWord"));
        passWord->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 75 16pt \"Ubuntu Mono\";"));

        horizontalLayout_2->addWidget(passWord);

        passIn = new QLineEdit(layoutWidget1);
        passIn->setObjectName(QString::fromUtf8("passIn"));
        passIn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        passIn->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(passIn);

        logInButt = new QPushButton(customerLogin);
        logInButt->setObjectName(QString::fromUtf8("logInButt"));
        logInButt->setGeometry(QRect(190, 350, 121, 41));
        logInButt->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 75 16pt \"Ubuntu Mono\";"));
        signUp = new QLabel(customerLogin);
        signUp->setObjectName(QString::fromUtf8("signUp"));
        signUp->setGeometry(QRect(60, 530, 241, 21));
        signUp->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 75 16pt \"Ubuntu Mono\";"));
        signUpButt = new QPushButton(customerLogin);
        signUpButt->setObjectName(QString::fromUtf8("signUpButt"));
        signUpButt->setGeometry(QRect(320, 530, 111, 25));
        signUpButt->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 75 16pt \"Ubuntu Mono\";"));

        retranslateUi(customerLogin);

        QMetaObject::connectSlotsByName(customerLogin);
    } // setupUi

    void retranslateUi(QDialog *customerLogin)
    {
        customerLogin->setWindowTitle(QCoreApplication::translate("customerLogin", "Dialog", nullptr));
        Header->setText(QCoreApplication::translate("customerLogin", "You're logging in as a customer.", nullptr));
        userName->setText(QCoreApplication::translate("customerLogin", "User Name:", nullptr));
        nameIn->setText(QString());
        passWord->setText(QCoreApplication::translate("customerLogin", "Password:", nullptr));
        passIn->setText(QString());
        logInButt->setText(QCoreApplication::translate("customerLogin", "LOG IN", nullptr));
        signUp->setText(QCoreApplication::translate("customerLogin", "Don't have an account?", nullptr));
        signUpButt->setText(QCoreApplication::translate("customerLogin", "SIGN UP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class customerLogin: public Ui_customerLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMERLOGIN_H
