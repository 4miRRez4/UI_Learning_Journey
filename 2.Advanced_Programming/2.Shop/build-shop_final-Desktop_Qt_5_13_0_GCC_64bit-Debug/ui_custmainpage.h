/********************************************************************************
** Form generated from reading UI file 'custmainpage.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTMAINPAGE_H
#define UI_CUSTMAINPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_custMainPage
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QTabWidget *tabWidget;
    QWidget *productsTab;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *prodTabLay;
    QTreeWidget *prodTree;
    QPushButton *addButt;
    QWidget *basketTab;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *baskTabLay;
    QTreeWidget *baskTree;
    QLabel *priceLabel;
    QPushButton *buyButt;
    QLabel *welcomeLable;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *custMainPage)
    {
        if (custMainPage->objectName().isEmpty())
            custMainPage->setObjectName(QString::fromUtf8("custMainPage"));
        custMainPage->resize(502, 617);
        custMainPage->setStyleSheet(QString::fromUtf8("background-image: url(:/images/BG.png);"));
        centralwidget = new QWidget(custMainPage);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 30, 461, 541));
        groupBox->setStyleSheet(QString::fromUtf8(""));
        tabWidget = new QTabWidget(groupBox);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 461, 541));
        productsTab = new QWidget();
        productsTab->setObjectName(QString::fromUtf8("productsTab"));
        verticalLayoutWidget_2 = new QWidget(productsTab);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 0, 461, 511));
        prodTabLay = new QVBoxLayout(verticalLayoutWidget_2);
        prodTabLay->setObjectName(QString::fromUtf8("prodTabLay"));
        prodTabLay->setContentsMargins(0, 0, 0, 0);
        prodTree = new QTreeWidget(verticalLayoutWidget_2);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setBackground(0, QColor(255, 255, 255));
        prodTree->setHeaderItem(__qtreewidgetitem);
        prodTree->setObjectName(QString::fromUtf8("prodTree"));
        prodTree->setStyleSheet(QString::fromUtf8("selection-background-color: rgb(84, 83, 83);\n"
"selection-color: rgb(255, 255, 255);"));

        prodTabLay->addWidget(prodTree);

        addButt = new QPushButton(verticalLayoutWidget_2);
        addButt->setObjectName(QString::fromUtf8("addButt"));
        addButt->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 12pt \"Ubuntu\";"));

        prodTabLay->addWidget(addButt);

        tabWidget->addTab(productsTab, QString());
        basketTab = new QWidget();
        basketTab->setObjectName(QString::fromUtf8("basketTab"));
        verticalLayoutWidget = new QWidget(basketTab);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 461, 511));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        baskTabLay = new QVBoxLayout();
        baskTabLay->setObjectName(QString::fromUtf8("baskTabLay"));
        baskTree = new QTreeWidget(verticalLayoutWidget);
        baskTree->setObjectName(QString::fromUtf8("baskTree"));
        baskTree->setStyleSheet(QString::fromUtf8(""));

        baskTabLay->addWidget(baskTree);

        priceLabel = new QLabel(verticalLayoutWidget);
        priceLabel->setObjectName(QString::fromUtf8("priceLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(priceLabel->sizePolicy().hasHeightForWidth());
        priceLabel->setSizePolicy(sizePolicy);
        priceLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 12pt \"Ubuntu\";"));

        baskTabLay->addWidget(priceLabel);

        buyButt = new QPushButton(verticalLayoutWidget);
        buyButt->setObjectName(QString::fromUtf8("buyButt"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(buyButt->sizePolicy().hasHeightForWidth());
        buyButt->setSizePolicy(sizePolicy1);
        buyButt->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 12pt \"Ubuntu\";"));

        baskTabLay->addWidget(buyButt);


        verticalLayout->addLayout(baskTabLay);

        tabWidget->addTab(basketTab, QString());
        welcomeLable = new QLabel(centralwidget);
        welcomeLable->setObjectName(QString::fromUtf8("welcomeLable"));
        welcomeLable->setGeometry(QRect(180, 10, 151, 20));
        welcomeLable->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 25 italic 16pt \"URW Bookman\";"));
        custMainPage->setCentralWidget(centralwidget);
        menubar = new QMenuBar(custMainPage);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 502, 22));
        custMainPage->setMenuBar(menubar);
        statusbar = new QStatusBar(custMainPage);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        custMainPage->setStatusBar(statusbar);

        retranslateUi(custMainPage);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(custMainPage);
    } // setupUi

    void retranslateUi(QMainWindow *custMainPage)
    {
        custMainPage->setWindowTitle(QCoreApplication::translate("custMainPage", "MainWindow", nullptr));
        groupBox->setTitle(QString());
#if QT_CONFIG(whatsthis)
        productsTab->setWhatsThis(QCoreApplication::translate("custMainPage", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        QTreeWidgetItem *___qtreewidgetitem = prodTree->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("custMainPage", "Price", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("custMainPage", "Name", nullptr));
        addButt->setText(QCoreApplication::translate("custMainPage", "Add to my basket", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(productsTab), QCoreApplication::translate("custMainPage", "Products", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = baskTree->headerItem();
        ___qtreewidgetitem1->setText(1, QCoreApplication::translate("custMainPage", "Price", nullptr));
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("custMainPage", "Name", nullptr));
        priceLabel->setText(QCoreApplication::translate("custMainPage", "Total Price:   ", nullptr));
        buyButt->setText(QCoreApplication::translate("custMainPage", "Buy", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(basketTab), QCoreApplication::translate("custMainPage", "Basket", nullptr));
        welcomeLable->setText(QCoreApplication::translate("custMainPage", "Welcome user.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class custMainPage: public Ui_custMainPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTMAINPAGE_H
