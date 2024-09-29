#include "historydialog.h"
#include "ui_historydialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <vector>
#include "beforegamedialog.h"

HistoryDialog::HistoryDialog(user* currentUser, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HistoryDialog)
    ,currentUser(currentUser)
{
    ui->setupUi(this);
    loadHistory(); // load history data when the dialog is created

    connect(ui->closeButt,&QPushButton::clicked, this, &HistoryDialog::on_closeButt_clicked);

}

HistoryDialog::~HistoryDialog()
{
    delete ui;
}

void HistoryDialog::setUser(const QString &username){
    this->username = username;
}

void HistoryDialog::loadHistory(){

    QFile file("users.csv");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, "File Error", "Unable to open file for reading");
        return;
    }
    QTextStream in(&file);
    QVector<QStringList> userHistories; //vector to store history data
    QString line;
    int highestScore = 0;

    while(!in.atEnd()){
        line = in.readLine();
        QStringList fields = line.split(',');
        if(fields.size() >= 7 && fields[2] == QString::fromStdString(currentUser->getUsername())){ // check if the username matches
            int score = fields[6].toInt();
            if(score > highestScore){
                highestScore = score;
            }
        }
    }
    file.close();

    QString historyText;
    historyText.append(QString("<b>Highest Score:</b> %1<br><br>").arg(highestScore));

    for (const auto &history : userHistories)
    {
        QString line;
        for (int col = 0; col < history.size(); col++)
        {
            line.append(history[col]);
            if (col < history.size() - 1)
            {
                line.append(", ");
            }
        }
        historyText.append(line + "<br>");
    }

    ui->textEdit->setHtml(historyText);
    ui->textEdit->setStyleSheet("QTextEdit { color: white; background-color: black; }");
}


void HistoryDialog::on_closeButt_clicked()
{
    this->close();
}

