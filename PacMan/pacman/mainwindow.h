#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"
#include "beforegamedialog.h"
#include "user.h"
#include <QLabel>
#include <QKeyEvent>
#include <QMainWindow>
#include <QDebug>
#include <QFontDatabase>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(user* curUsr, QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent*) override;
    ~MainWindow() override;

private slots:
    void refresh_score_labels();
    void handle_end_signal();

private:
    void initializeGraphic();
    void check_win_or_lose();

    Ui::MainWindow *ui;
    Game *game;
    user* currentUser;
    QTimer *score_timer;
    QFont font;
    static const int font_size = 15;
    static const int font_size_2 = 8;
};

#endif // MAINWINDOW_H
