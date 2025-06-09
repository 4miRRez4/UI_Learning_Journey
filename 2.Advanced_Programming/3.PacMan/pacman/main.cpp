#include <QApplication>
#include "logindialog.h"
#include "user.h"
#include <vector>
#include "signupdialog.h"
#include <QMessageBox>
#include "beforegamedialog.h"
//global users vector
std::vector<user> users;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // load users from csv file
    users = loadUser("users.csv");

    loginDialog w;
    //BeforeGameDialog w;
    w.show();

    return a.exec();
}
