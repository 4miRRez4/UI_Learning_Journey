#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H


#include <QDialog>
#include <QVector>
#include <QString>
#include "user.h"
//#include "beforegamedialog.h"
namespace Ui {
class HistoryDialog;
}

class HistoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryDialog(user* currentUser, QWidget *parent = nullptr);
    ~HistoryDialog();

    void setUser(const QString &username); //function to set the user for whom history is displayed
private slots:
    void on_closeButt_clicked();

private:
    Ui::HistoryDialog *ui;
    QString username; // to store the username fo the current user
    void loadHistory(); // function to load history data
    user* currentUser;

};

#endif // HISTORYDIALOG_H
