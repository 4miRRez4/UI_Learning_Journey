#include "beforegamedialog.h"
#include "ui_beforegamedialog.h"
#include "historydialog.h"
#include "mainwindow.h"
BeforeGameDialog::BeforeGameDialog(user* currentUser, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BeforeGameDialog)
    ,currentUser(currentUser)
    ,history(nullptr)
    ,movie(new QMovie(":/resrcs/imgs/bgs/initial_gif.gif"))

{
    ui->setupUi(this);
    ui->Gif->setMovie(movie);
    ui->Gif->setScaledContents(true);

    movie->start();
    connect(ui->pushButton_history, &QPushButton::clicked, this, &BeforeGameDialog::on_pushButton_history_clicked);
    //connect()

}

BeforeGameDialog::~BeforeGameDialog()
{
    if (history)
            delete history;
    delete ui;
}

void BeforeGameDialog::on_pushButton_history_clicked()
{
    if (!history) {
            history = new HistoryDialog(currentUser, this);
            connect(history, &HistoryDialog::finished, this, [this]() {
                history = nullptr;
            });
        }
    history->show();
    history->raise();
    history->activateWindow();
}


void BeforeGameDialog::on_pushButton_clicked()
{
    QCoreApplication::quit();
}


void BeforeGameDialog::on_pushButton_play_clicked()
{
    mw = new MainWindow(currentUser);
    mw->show();
    this->hide();
}


void BeforeGameDialog::updateUserScore(int newScore)
{
    currentUser->setScore(newScore);

    QFile file("users.csv");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, "File Error", "Unable to open file for reading");
        return;
    }

    QVector<QStringList> userRecords;
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        if (fields[2] == QString::fromStdString(currentUser->getUsername())) {
            fields[6] = QString::number(newScore); // Assuming score is in the 7th column
        }
        userRecords.append(fields);
    }
    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(this, "File Error", "Unable to open file for writing");
        return;
    }

    QTextStream out(&file);
    for (const auto &record : userRecords) {
        out << record.join(',') << "\n";
    }
    file.close();
}


void BeforeGameDialog::on_pushButton_gallery_clicked()
{
    Dialog *nd = new Dialog();
    nd->show();
    this->close();
}
