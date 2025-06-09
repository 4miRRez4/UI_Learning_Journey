#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
//    void on_empButton_clicked();

    void on_custButton_clicked();

private:
    Ui::MainWindow *ui;

};
//void saveFileCustData();

#endif // MAINWINDOW_H
