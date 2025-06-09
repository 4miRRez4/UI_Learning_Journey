#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //applying a global styleSheet for QMessageBox
    app.setStyleSheet(
        "QMessageBox {"
        "    background-color: #000000;"
        "}"
        "QMessageBox QLabel {"
        "    color: #f0f0f0;"
        "}"
        "QPushButton {"
        "    background-color: #ffffff;"
        "    color: #ffffff;"
        "}"
    );

    MainWindow w;
    w.show();
    return app.exec();
}


