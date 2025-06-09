#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include <QString>
#include <QTimer>
namespace Ui {
class SignUpDialog;
}

class SignUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpDialog(QWidget *parent = nullptr);
    ~SignUpDialog();

private slots:
    void on_SignupButton_clicked();

    void on_LoginButton_clicked();
    void clearError();


signals:
    void signupSuccessful();

private:
    Ui::SignUpDialog *ui;
    QTimer *errorClearTimer;

    //const QString& username, cosnt QString& password
    void saveUserData(QString name,QString lastName,QString username,
                      QString password,QString phone, int score);

    void showError(const QString& message);

};

#endif // SIGNUPDIALOG_H
