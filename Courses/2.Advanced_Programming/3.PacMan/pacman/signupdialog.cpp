#include "signupdialog.h"
#include "ui_signupdialog.h"
#include <QPixmap>
#include "logindialog.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <vector>
#include <user.h>
#include "ui_signupdialog.h"

extern std::vector<user> users;

SignUpDialog::SignUpDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignUpDialog)
    ,errorClearTimer(new QTimer(this))
{
    ui->setupUi(this);
    QPixmap pixmap(":/resrcs/imgs/bgs/a.jpg");
    ui->label_background_signup->setPixmap(pixmap);
    ui->label_background_signup->setScaledContents(true);

    ui->errorLabel->setStyleSheet("QLabel {color: red; }");

    ui->errorLabel->setText("");
    //for connect the timer of disappearing the error after 5 sec
    connect(errorClearTimer, &QTimer::timeout, this, &SignUpDialog::clearError);


}

SignUpDialog::~SignUpDialog()
{
    delete ui;
}

void SignUpDialog::on_SignupButton_clicked()
{
    QString name = ui->NamelineEdit->text();
    QString lastName = ui->LastNamelineEdit->text();
    QString username = ui->UserNamelineEdit->text();
    QString password = ui->PasswordlineEdit->text();
    QString passconfirm = ui->PassConfirmlineEdit->text();
    QString phone = ui->PhonelineEdit->text();

    if(username.isEmpty() || password.isEmpty() ||
        name.isEmpty() || lastName.isEmpty() || passconfirm.isEmpty()
        || phone.isEmpty()){
        //QMessageBox::warning(this,"Input Error", "Please fill in all fields");
        showError("Please fill in all fields");
        return;
    }

    if(password != passconfirm){
        showError("Passwords do not match!");
        //QMessageBox::warning(this, "Error", "Passwords do not match!");
        return;
    }

    //برای اینکه اگر داشت ساین این میکرد و دیدیم قبلا ثبت نام کرده
    for(const user& user : users){
        if(user.getUsername() == username.toStdString()){
            showError("Username alredy exists!");
            //QMessageBox::warning(this, "Error", "Username alredy exists!");
            return;
        }
    }

    user newUser(name.toStdString(), lastName.toStdString(), username.toStdString()
                 ,password.toStdString(), phone.toStdString(), 0, 0);

    users.push_back(newUser);
    saveUser("users.csv", newUser);

    emit signupSuccessful();
    close();

}


void SignUpDialog::on_LoginButton_clicked()
{
    //بازگشت به صفحه لاگین
    this->close();
    loginDialog log;
    log.exec();
}

void SignUpDialog::showError(const QString& message){
    ui->errorLabel->setText(message);
    errorClearTimer->start(5000);
}

void SignUpDialog::clearError(){
    ui->errorLabel->setText("");
    errorClearTimer->stop();
}



