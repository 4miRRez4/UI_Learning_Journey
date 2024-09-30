#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QPair>
#include <QMediaPlayer>
#include "entities.h"
#include "pacmanclass.h"
#include "ghost.h"

#define BALL_SCORE      10
#define POWERBALL_SCORE 30
#define GHOST_SCORE     50
#define INTERVAL        10
#define RUNNING_INTERVAL 5
#define NORMAL_INTERVAL 10
#define PANNIC_INTERVAL 15
#define PANNIC_TIME     500
#define FLASH_INTERVAL 200

class Game : public QGraphicsScene
{
    Q_OBJECT
public:
    enum gameStatus {Playing, Win, Lose, Pause};
    Game(int, int, int, int, QString);
    ~Game();
    void wait(qreal ms);
    void start_game();
    void loadMap(int, int, int, int, QString);
    void pause_game();
    void resume_game();
    void end_game();
    Entities::moveDir backward_of_dir(Entities::moveDir currDir);

    gameStatus get_gstat();
    void set_gstat(gameStatus gs);
    int get_score();
    void set_pacman_next_dir(Entities::moveDir);


    gameStatus gstat;
    Entities ***map;
    pacManClass *pacman;
    QVector<Entities*> bigBalls;
    Entities *gate;
    Ghost *ghost[4];
signals:
    void game_ended();

    friend class pacManClass;
    friend class Ghost;
private slots:
    void bigBall_flash();
    void pacman_movement();
    void ghost_movement(int);
    void stopAndBeforePage();
private:
    int x_of_obj, y_of_obj;
    int map_width, map_height;
    int map_size;
    int mode;
    int numOfBall, numOfEat, score;

    bool tick_flag;

    QTimer *pacman_motion, *lag, *bigBall_flasher, *ghost_motion[4];

};

#endif // GAME_H
