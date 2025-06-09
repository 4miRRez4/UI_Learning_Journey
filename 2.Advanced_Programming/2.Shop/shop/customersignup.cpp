#include "customersignup.h"
#include "ui_customersignup.h"


customerSignUp::customerSignUp(QVector<customerClass> *customers, QWidget *parent) :
    QDialog (parent),
    ui(new Ui::customerSignUp), customers(customers)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    setWindowTitle(tr("SignUp Page"));
}

customerSignUp::~customerSignUp()
{
    delete ui;
}

void customerSignUp::on_signUpButt_clicked()
{
    if(!ui->nameIn->text().isEmpty() && !ui->passIn->text().isEmpty()){
        QString nameOfUsr = ui->nameIn->text();
        auto usr = std::find_if(customers->begin(), customers->end(), [&nameOfUsr](const customerClass& cust) { return cust.get_name() == nameOfUsr;});
        if(usr != customers->end()){
                QMessageBox::warning(this, "warning", "This username is already taken. Try again.");
                ui->nameIn->clear();
                ui->passIn->clear();
        }
        else{
            customerClass tmpUsr(ui->nameIn->text(), ui->passIn->text());
            customers->push_back(tmpUsr);
            saveToFile("customerData.txt", customers);
            QVector<customerClass>::iterator newCustIt = customers->end()-1;
            custMainPage *cmp = new custMainPage(&newCustIt, nullptr);
            this->close();
            cmp->show();
        }
    }
    else{
        emptyInputWarning(this);
    }
}
