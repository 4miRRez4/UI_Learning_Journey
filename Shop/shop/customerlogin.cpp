#include "customerlogin.h"
#include "ui_customerlogin.h"

#include "customersignup.h"

customerLogin::customerLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::customerLogin)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    setWindowTitle(tr("Login Page"));

    customers = new QVector<customerClass>;
    loadFromFile("customerData.txt", customers);
}

customerLogin::~customerLogin()
{
    delete ui;
}

void customerLogin::on_signUpButt_clicked()
{
    customerSignUp* customerSignUpPage = new customerSignUp(customers, this);
    this->close();
    customerSignUpPage->show();
}

void customerLogin::on_logInButt_clicked()
{
    if(!ui->nameIn->text().isEmpty() && !ui->passIn->text().isEmpty()){
        QString nameOfUsr = ui->nameIn->text();
        QVector<customerClass>::iterator usr = std::find_if(customers->begin(), customers->end(), [&nameOfUsr](const customerClass& cust) { return cust.get_name() == nameOfUsr;});

        if(usr != customers->end())
        {
            if(usr->get_pass() == ui->passIn->text()){
                custMainPage *cmp = new custMainPage(&usr, this);
                this->close();
                cmp->show();
            }else{
                QMessageBox::warning(this, "warning", "Password doesn't match with username.");
            }
        }else {
            QMessageBox::warning(this, "warning", "Invalid username.");
        }
    }else{
       emptyInputWarning(this);
//       if(ui->nameIn->text().isEmpty())
//            (*(ui->nameIn)).setStyleSheet(" background-color: #ffffcc");
//       if(ui->passIn->text().isEmpty())
//           (*(ui->passIn)).setStyleSheet(" background-color: #ffffcc");
    }
}

