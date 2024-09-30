#ifndef BEFOREGAMEDIALOG_H
#define BEFOREGAMEDIALOG_H

#include <QDialog>
#include "user.h"
#include "dialog.h"
//#include "mainwindow.h"
#include <QMovie>
#include <QMessageBox>
#include "historydialog.h"
class MainWindow;

namespace Ui {
class BeforeGameDialog;
}

class BeforeGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BeforeGameDialog(user* currentUser, QWidget *parent = nullptr);
    ~BeforeGameDialog();
    void updateUserScore(int newScore);

private slots:
    void on_pushButton_history_clicked();

    void on_pushButton_clicked();

    void on_pushButton_play_clicked();

    void on_pushButton_gallery_clicked();

private:

    Ui::BeforeGameDialog *ui;
    HistoryDialog *history;
    user *currentUser;
    QMovie *movie;
    MainWindow *mw;
};

#endif // BEFOREGAMEDIALOG_H
