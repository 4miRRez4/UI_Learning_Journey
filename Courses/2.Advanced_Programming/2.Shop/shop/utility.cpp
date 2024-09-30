#include "utility.h"


void emptyInputWarning(QWidget *parent){
//    CustomQMessageBox msgBox;
//    msgBox.setText("You can't leave username or password blank!!!");
//    msgBox.exec();
    QMessageBox::warning(parent, "warning", "You can't leave username or pass to blank!");
}

void saveToFile(QString fileName, QVector<customerClass> *list)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }
    else{
        QTextStream out(&file);
        for(auto it=(*list).begin(); it!=(*list).end(); it++)
        {
            out<< it->get_name() + "," + it->get_pass() + "\n";
        }
        file.close();
    }
}


void loadFromFile(QString fileName, QVector<customerClass> *list){
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly |QIODevice::Text))
    {
        if(file.size()!=0)
        {
            QTextStream in(&file);
            while(!in.atEnd())
            {
                QString line=in.readLine();
                QStringList info = line.split(',');
                customerClass tmpCust(info[0], info[1]);
                list->push_back(tmpCust);
            }
        }
    }
    file.close();
}

void loadProductsFromFile(QString fileName, QVector<productClass> *list){
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly |QIODevice::Text))
    {
        if(file.size()!=0)
        {
            QTextStream in(&file);
            while(!in.atEnd())
            {
                QString line=in.readLine();
                QStringList info = line.split(',');
                productClass tmpProd(info[0], info[1].toDouble());
                list->push_back(tmpProd);
            }
        }
    }
    file.close();
}
