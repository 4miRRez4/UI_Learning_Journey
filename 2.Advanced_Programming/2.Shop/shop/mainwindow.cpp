#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customerlogin.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //fixed size for frame
    this->setFixedSize(this->width(),this->height());
    setWindowTitle(tr("Welcome Page"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::on_empButton_clicked()
//{
//    //TODO
//}

void MainWindow::on_custButton_clicked()
{
//    customerLogin customerPage;
//    customerPage.setModal(true);
//    customerPage.exec();
    //hide();
    customerLogin* customerPage = new customerLogin(this);
    this->close();
    customerPage->show();
}

