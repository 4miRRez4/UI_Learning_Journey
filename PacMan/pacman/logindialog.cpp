#include "logindialog.h"
#include "ui_logindialog.h"
#include "signupdialog.h"
#include <vector>
#include <QMessageBox>
#include "user.h"

// Assuming `users` is a global or externally accessible vector
extern std::vector<user> users;


loginDialog::loginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::loginDialog)
    ,errorClearTimer(new QTimer(this))
    ,signUpDialog(nullptr)
    ,beforeGameDlg(nullptr)

{
    ui->setupUi(this);

    QPixmap pixmap(":/resrcs/imgs/bgs/b.jpg");

    ui->label_background->setPixmap(pixmap);
    ui->label_background->setScaledContents(true);

    //برای وقتی که روی sign up کلیک میکنی
    connect(ui->signUpButton, &QPushButton::clicked, this , &loginDialog::on_signUpButton_clicked);

    ui->errorLabel->setStyleSheet("QLabel {color: red; }");

    ui->errorLabel->setText("");
    //for connect the timer of disappearing the error after 5 sec
    connect(errorClearTimer, &QTimer::timeout, this, &loginDialog::clearError);

}

loginDialog::~loginDialog()
{
    delete ui;
    delete movie;
    delete signUpDialog;
}

void loginDialog::on_signUpButton_clicked()
{
    hide();
    if (!signUpDialog) {
        signUpDialog = new SignUpDialog(this);
        //connect (signUpDialog, &SignUpDialog::signupSuccessful, this, &loginDialog::on_signupSuccessful);
        connect(signUpDialog, &SignUpDialog::signupSuccessful, this, &loginDialog::on_signupSuccessful );
        connect(signUpDialog, &QDialog::finished, this, [this]() {
            //delete signUpDialog;
            signUpDialog = nullptr;
        });
    }
    signUpDialog->show();
    signUpDialog->raise();
    signUpDialog->activateWindow();

}

void loginDialog::on_signupSuccessful(){

    //QMessageBox::information(this, "Sign Up", "Sign up successful! Please log in.");
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { background-color: white; color: black; } ");
    msgBox.setWindowTitle("Sign Up");
    msgBox.setText("Sign up successful! Please log in");
    msgBox.exec();

    this->show();//انتقال به صفحه ی لاگین
}

void loginDialog::on_login_pushbutton_clicked()
{
    QString username = ui->userNamelineEdit->text();
    QString password = ui->passwordlineEdit->text();

    for(const user& user : users){
        if(user.getUsername() == username.toStdString() && user.getPassword() == password.toStdString()){
            currentUser = user;
            // ذخیره کردن کاربر لاگین کرده
        //QMessageBox::information(this, "Success", "Login successful!");
        //shor user scores or move to the next window
        //showError("Login successful!");
            QMessageBox msgBox;
            msgBox.setStyleSheet("QMessageBox { background-color: white; color: black; } ");
            msgBox.setWindowTitle("Success");
            msgBox.setText("Login successful!");
            msgBox.exec();
            this->close();
            BeforeGameDialog beforeGameDlg(&currentUser ,this);
            beforeGameDlg.exec();

            return;
        }
    }
    showError("Invalid username or password!");
}


void loginDialog::showError(const QString& message){
    ui->errorLabel->setText(message);
    errorClearTimer->start(5000);
}

void loginDialog::clearError(){
    ui->errorLabel->setText("");
    errorClearTimer->stop();
}















