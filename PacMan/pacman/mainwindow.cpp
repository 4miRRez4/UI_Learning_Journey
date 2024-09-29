#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(user* curUsr, QWidget *parent) :
    QMainWindow(parent),
    currentUser(curUsr),
    ui(new Ui::MainWindow)
{
    //initializing
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    this->setWindowTitle(tr("PacMan"));
    this->setWindowIcon(QPixmap(":/resrcs/imgs/pacmanPics/32.png"));

    initializeGraphic();
}

void MainWindow::initializeGraphic(){
    int font_id = QFontDatabase::addApplicationFont(":/resrcs/arcadepi.ttf");
    font = QFont(QFontDatabase::applicationFontFamilies(font_id).at(0), font_size, 0);
    ui->scoreLabel->setFont(QFont(font));
    ui->winLabel->setFont(QFont(font));
    ui->loseLabel->setFont(QFont(font));
    ui->pauseLabel->setFont(QFont(font));

    ui->winLabel->hide();
    ui->loseLabel->hide();
    ui->pauseLabel->hide();

    ui->mainGraphic->setBackgroundBrush(Qt::black);
    ui->mainGraphic->setFocusPolicy(Qt::NoFocus);

    game = new Game(ui->mainGraphic->x(), ui->mainGraphic->y(), 30, 30, ":/resrcs/imgs/map_objects/map.txt");
    ui->mainGraphic->setScene(game);
    connect(game, &Game::game_ended, this, &MainWindow::handle_end_signal);

    score_timer = new QTimer(this);
    score_timer->start(25);
    connect(score_timer, SIGNAL(timeout()), this , SLOT(refresh_score_labels()));

//    QMediaPlayer* start_snd = new QMediaPlayer;
//    start_snd->setMedia(QUrl("qrc:/resrcs/sounds/start.mp3"));
//    start_snd->setVolume(75);
//    start_snd->play();

    game->start_game();
}

void MainWindow::refresh_score_labels(){
    ui->scoreLabel->setText("score: " + QString::number(game->get_score()));

    check_win_or_lose();
}

void MainWindow::check_win_or_lose(){
    if (game->gstat == Game::Win) {
        ui->winLabel->show();
        score_timer->stop();
    } else if (game->gstat == Game::Lose) {
        ui->loseLabel->show();
        score_timer->stop();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *ev) {
    if(game->get_gstat() == Game::gameStatus::Playing){
        switch (ev->key()) {
            case Qt::Key_Up:
            case Qt::Key_W:
                game->set_pacman_next_dir(Entities::moveDir::Up);
                break;
                [[fallthrough]];
            case Qt::Key_Down:
            case Qt::Key_S:
                game->set_pacman_next_dir(Entities::moveDir::Down);
                break;
            case Qt::Key_Left:
            case Qt::Key_A:
                game->set_pacman_next_dir(Entities::moveDir::Left);
                break;
            case Qt::Key_Right:
            case Qt::Key_D:
                game->set_pacman_next_dir(Entities::moveDir::Right);
                break;
            case Qt::Key_P:
                    game->set_gstat(Game::gameStatus::Pause);
                    game->pause_game();
                    ui->pauseLabel->show();
        }
    }else if(game->get_gstat() == Game::gameStatus::Pause){
        if(ev->key() == Qt::Key_P){
            game->set_gstat(Game::gameStatus::Playing);
            game->resume_game();
            ui->pauseLabel->hide();
        }
    }
}

void MainWindow::handle_end_signal(){
    this->close();
    BeforeGameDialog* beforePage = new BeforeGameDialog(currentUser, this);
    if(game->get_score() > currentUser->getMaxScore())
        beforePage->updateUserScore(game->get_score());

    beforePage->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

