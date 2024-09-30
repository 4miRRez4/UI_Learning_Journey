#ifndef GHOST_H
#define GHOST_H

#include "entities.h"
//#include "game.h"
#include <QRandomGenerator>

class Ghost : public Entities
{
public:
    enum Color {Red = 0, Orange = 1, Pink = 2, Green = 3};
    enum Status {Normal, Panic, Running};
    Game* game;

    Ghost(Game*, int);
    Color get_color();

    friend class Game;
    friend class pacManClass;
private:
    void load_ghost_animations();
    bool can_ghost_go(int, int);
    void which_dir_can_go(QVector<moveDir>&, QVector<bool>&);
    Entities::moveDir backward_of_dir(Entities::moveDir currDir);
    void chase();
    void run_from_pacman();
    void go_out_cage();
    void go_to_cage();
    void random_dir();
    void move();
    void step_up();
    void step_down();
    void step_right();
    void step_left();


    Color color;
    int animation_ind;
    int release_time;
    int panic_time;
    bool is_in_cage;
    Status stat;
    QVector<QPixmap> animations[4];
    QVector<QPixmap> panic_anim;
    QVector<QPixmap> running_anim;
};

#endif // GHOST_H
