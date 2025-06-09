/********************************************************************************
** Form generated from reading UI file 'customersignup.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMERSIGNUP_H
#define UI_CUSTOMERSIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_customerSignUp
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *passWord;
    QLineEdit *passIn;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout;
    QLabel *userName;
    QLineEdit *nameIn;
    QPushButton *signUpButt;

    void setupUi(QDialog *customerSignUp)
    {
        if (customerSignUp->objectName().isEmpty())
            customerSignUp->setObjectName(QString::fromUtf8("customerSignUp"));
        customerSignUp->resize(500, 600);
        customerSignUp->setStyleSheet(QString::fromUtf8("background-image: url(:/images/BG.png);"));
        label = new QLabel(customerSignUp);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 60, 431, 31));
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 75 20pt \"Ubuntu Mono\";"));
        layoutWidget = new QWidget(customerSignUp);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(90, 270, 311, 61));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        passWord = new QLabel(layoutWidget);
        passWord->setObjectName(QString::fromUtf8("passWord"));
        passWord->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 75 16pt \"Ubuntu Mono\";"));

        horizontalLayout_2->addWidget(passWord);

        passIn = new QLineEdit(layoutWidget);
        passIn->setObjectName(QString::fromUtf8("passIn"));
        passIn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        passIn->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(passIn);

        layoutWidget_2 = new QWidget(customerSignUp);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(90, 220, 311, 51));
        horizontalLayout = new QHBoxLayout(layoutWidget_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        userName = new QLabel(layoutWidget_2);
        userName->setObjectName(QString::fromUtf8("userName"));
        userName->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 75 16pt \"Ubuntu Mono\";"));

        horizontalLayout->addWidget(userName);

        nameIn = new QLineEdit(layoutWidget_2);
        nameIn->setObjectName(QString::fromUtf8("nameIn"));
        nameIn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(nameIn);

        signUpButt = new QPushButton(customerSignUp);
        signUpButt->setObjectName(QString::fromUtf8("signUpButt"));
        signUpButt->setGeometry(QRect(190, 350, 121, 41));
        signUpButt->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 75 16pt \"Ubuntu Mono\";"));

        retranslateUi(customerSignUp);

        QMetaObject::connectSlotsByName(customerSignUp);
    } // setupUi

    void retranslateUi(QDialog *customerSignUp)
    {
        customerSignUp->setWindowTitle(QCoreApplication::translate("customerSignUp", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("customerSignUp", "You're Signing up as a customer.", nullptr));
        passWord->setText(QCoreApplication::translate("customerSignUp", "Password:", nullptr));
        passIn->setText(QString());
        userName->setText(QCoreApplication::translate("customerSignUp", "User Name:", nullptr));
        nameIn->setText(QString());
        signUpButt->setText(QCoreApplication::translate("customerSignUp", "SIGN UP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class customerSignUp: public Ui_customerSignUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMERSIGNUP_H
