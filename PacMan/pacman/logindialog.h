#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QMovie>
#include <QTimer>
#include "signupdialog.h"
#include <QPointer>
#include <beforegamedialog.h>
#include "user.h"
namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog();


private slots:

    void on_signUpButton_clicked();

    void on_login_pushbutton_clicked();

    void clearError();

    void on_signupSuccessful();
private:
    Ui::loginDialog *ui;
    QPointer<SignUpDialog> signUpDialog;
    BeforeGameDialog * beforeGameDlg;
    QTimer *errorClearTimer;

    QMovie *movie;
    void showError(const QString& message);
    user currentUser; // متغیر برای نگه داشتن کاربر لاگین کرده

};

#endif // LOGINDIALOG_H
