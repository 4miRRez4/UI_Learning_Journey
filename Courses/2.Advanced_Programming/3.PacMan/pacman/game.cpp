#include "game.h"
#include <QFile>
#include <QString>
#include <QDebug>

Game::Game(int x, int y, int map_wid, int map_hei, QString map_pic)
    :QGraphicsScene(x, y,  Entities::ObjWidth * map_wid, Entities::ObjWidth * map_hei)
{
    QMediaPlayer* start_snd = new QMediaPlayer;
    start_snd->setMedia(QUrl("qrc:/resrcs/sounds/start.mp3"));
    start_snd->setVolume(75);
    start_snd->play();

    x_of_obj = x;
    y_of_obj = y;
    gstat = Playing;
    pacman = new pacManClass(this);
    loadMap(x, y, map_wid, map_hei, map_pic);
}

void Game::set_gstat(gameStatus gs){
    this->gstat = gs;
}

int Game::get_score()
{
    return score;
}

Game::gameStatus Game::get_gstat(){
    return gstat;
}

void Game::set_pacman_next_dir(Entities::moveDir d){
    pacman->set_next_dir(d);
}

void Game::wait(qreal ms) {
    if (gstat != Game::gameStatus::Playing)
        return;
    gstat = Game::gameStatus::Pause;
    lag->start(int(1000 * ms));
}

void Game::loadMap(int x, int y, int map_wid, int map_hei, QString map_pic){
    map_width = map_wid;
    map_height = map_hei;
    map_size = map_wid * map_hei;
    map = new Entities**[map_hei];
    for (int i=0; i<map_hei; i++) {
        map[i] = new Entities*[map_width];
        for (int j=0; j<map_width; j++)
            map[i][j] = nullptr;
    }

    numOfBall = numOfEat = score = 0;
    QPixmap wallPix(":/resrcs/imgs/map_objects/wall.png");
    QPixmap ballPix(":/resrcs/imgs/map_objects/dot.png");
    QPixmap bigBallPix(":/resrcs/imgs/map_objects/big_ball.png");
    QPixmap gatePix(":/resrcs/imgs/map_objects/gate.png");
    QPixmap blankPix;
    QFile mapfile(map_pic);
    mapfile.open(QIODevice::ReadOnly|QIODevice::Text);


   int ghost_c = 0;
    for (int i = 0; i < map_hei; i++) {
        QByteArray line = mapfile.readLine();
        for (int j = 0; j < map_wid; j++) {
            int tmp_x = x + (j * Entities::ObjWidth);
            int tmp_y = y + (i * Entities::ObjWidth);
            switch (line[j]) {
                case '1':
                    map[i][j] = new Entities(Entities::Wall, wallPix);
                    map[i][j]->setPos(tmp_x, tmp_y);
                    addItem(map[i][j]);
                    break;

                case '6':
                    map[i][j] = new Entities(Entities::Ball, ballPix);
                    map[i][j]->set_score(BALL_SCORE);
                    map[i][j]->setPos(tmp_x, tmp_y);
                    addItem(map[i][j]);
                    numOfBall++;
                    break;

                case '~':
                    gate = new Entities(Entities::Gate, gatePix);
                    gate->_x = j;
                    gate->_y = i;
                    gate->setPos(tmp_x, tmp_y);
                    addItem(gate);
                    map[i][j] = gate;
                    break;

                case '-':
                    map[i][j] = new Entities(Entities::Blank, blankPix);
                    break;

                case '*':
                    map[i][j] = new Entities(Entities::BigBall, bigBallPix);
                    map[i][j]->set_score(POWERBALL_SCORE);
                    map[i][j]->setPos(tmp_x, tmp_y);
                    addItem(map[i][j]);
                    bigBalls.push_back(map[i][j]);
                    numOfBall++;
                    break;

                case 'p':
                    pacman = new pacManClass(this);
                    pacman->setZValue(2);
                    pacman->setPos(tmp_x, tmp_y);
                    addItem(pacman);
                    map[i][j] = pacman;
                    break;

                case 'g':
                    map[i][j] = new Entities(Entities::Blank, blankPix);
                    ghost[ghost_c] = new Ghost(this, ghost_c);
                    ghost[ghost_c]->setZValue(2);
                    ghost[ghost_c]->release_time = ghost_c * 200;
                    ghost[ghost_c]->_x = j;
                    ghost[ghost_c]->_y = i;
                    ghost[ghost_c]->set_score(GHOST_SCORE);
                    ghost[ghost_c]->setPos(tmp_x, tmp_y);
                    addItem(ghost[ghost_c]);
                    ghost_c++;
                    break;
                    }
            if (map[i][j]) {
                map[i][j]->_x = j;
                map[i][j]->_y = i;
            }
        }
    }
}

void Game::pacman_movement()
{
    pacman->movement();
    if (gstat == Win)
        end_game();
}

void Game::start_game(){


    bigBall_flasher = new QTimer(this);
    connect(bigBall_flasher, SIGNAL(timeout()), this , SLOT(bigBall_flash()));
    bigBall_flasher->start(FLASH_INTERVAL);

    pacman_motion = new QTimer(this);
    connect(pacman_motion, SIGNAL(timeout()), this , SLOT(pacman_movement()));
    pacman_motion->start(INTERVAL);

    for (int i=0; i<4; i++) {
        ghost_motion[i] = new QTimer(this);
        connect(ghost_motion[i], &QTimer::timeout, [this, i](){ghost_movement(i);} );
        ghost_motion[i]->start(NORMAL_INTERVAL);
    }
}

void Game::bigBall_flash(){
    //is there any more bigBalls?
    if (bigBalls.empty()) {
        bigBall_flasher->stop();
        return;
    }
    //then flash
    if (tick_flag) {
        for (int i=0; i<bigBalls.size(); i++)
            bigBalls.at(i)->hide();
        tick_flag = false;
    }
    else {
        for (int i=0; i<bigBalls.size(); i++)
            bigBalls.at(i)->show();
        tick_flag = true;;
    }
}

void Game::pause_game(){
    QMediaPlayer* pause_snd = new QMediaPlayer;
    pause_snd->setMedia(QUrl("qrc:/resrcs/sounds/pause.mp3"));
    pause_snd->setVolume(75);
    pause_snd->play();

    bigBall_flasher->stop();
    pacman_motion->stop();
    for(int i=0; i<4; i++)
        ghost_motion[i]->stop();
}

void Game::resume_game(){
    bigBall_flasher->start();
    pacman_motion->start();
    for(int i=0; i<4; i++)
        ghost_motion[i]->start();


    QMediaPlayer* resume_snd = new QMediaPlayer;
    resume_snd->setMedia(QUrl("qrc:/resrcs/sounds/pause.mp3"));
    resume_snd->setVolume(75);
    resume_snd->play();
}


void Game::end_game(){
    pacman_motion->stop();
    bigBall_flasher->stop();
    for (int i=0; i<4; i++)
        ghost_motion[i]->stop();

    QMediaPlayer* end_snd = new QMediaPlayer;
    end_snd->setMedia(QUrl("qrc:/resrcs/sounds/death.mp3"));
    end_snd->setVolume(100);
    end_snd->play();

    QTimer *waitingToClose = new QTimer(this);
    waitingToClose->setSingleShot(true);
    connect(waitingToClose, SIGNAL(timeout()), this, SLOT(stopAndBeforePage()));
    waitingToClose->start(2000);
    wait(0.5);
}
void Game::stopAndBeforePage(){
    emit game_ended();
}


void Game::ghost_movement(int ghost_c)
{
    ghost[ghost_c]->move();
    if (gstat == Lose)
        end_game();
}

Game::~Game()
{
    for (int i = 0; i < map_height; i++) {
        for (int j = 0; j < map_width; j++) {
            if (map[i][j] != nullptr)
                delete map[i][j];
        }
        delete[] map[i];
    }
    delete[] map;
    delete pacman_motion;
    delete bigBall_flasher;
    for (int i=0; i<4; i++) {
        delete ghost_motion[i];
    }
}
