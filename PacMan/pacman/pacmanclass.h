#ifndef PACMANCLASS_H
#define PACMANCLASS_H

#include "entities.h"
//#include "game.h"

class Game;

class pacManClass : public Entities
{
public:
    pacManClass(Game*);
    void movement();
    void load_pacman_animations();

    Game *game;
    friend class Game;
private:
    void step_up();
    void step_down();
    void step_right();
    void step_left();
    bool can_pacman_go(int, int);
    void eat_ball(int, int);


    QVector<QPixmap> animation[4];
    int animation_ind;
};

#endif // PACMANCLASS_H
