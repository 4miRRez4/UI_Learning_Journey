#ifndef ENTITIES_H
#define ENTITIES_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QSound>

class Ghost;
class Game;
class pacManClass;


class Entities : public QGraphicsPixmapItem
{
public:
    enum entityType {Pacman, Ghost, Gate, Wall, Ball, BigBall, Blank};
    enum moveDir {Up = 0, Down = 1, Left = 2, Right = 3, Stop = 4};
    static const int ObjWidth = 20;

    Entities(entityType, QPixmap);
    entityType get_type();
    moveDir get_curr_dir();
    void set_curr_dir(moveDir d);
    moveDir get_next_dir();
    void set_next_dir(moveDir d);
    int get_x();
    int get_y();
    int get_score();
    void set_score(int);

    friend class Game;
    friend class Ghost;
    friend class pacManClass;
protected:
    entityType type;
    int _x, _y;
    moveDir currDir;
    moveDir nextDir;
    int score;
};

#endif // ENTITIES_H
