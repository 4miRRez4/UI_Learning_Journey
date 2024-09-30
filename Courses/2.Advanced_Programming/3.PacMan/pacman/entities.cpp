#include "entities.h"

Entities::Entities(entityType t, QPixmap pm)
    : QGraphicsPixmapItem(pm)
{
    type = t;
}

Entities::entityType Entities::get_type()
{
    return type;
}

void Entities::set_curr_dir(moveDir d)
{
    currDir = d;
}

Entities::moveDir Entities::get_curr_dir()
{
    return currDir;
}

void Entities::set_next_dir(moveDir d)
{
    nextDir = d;
}

Entities::moveDir Entities::get_next_dir()
{
    return nextDir;
}

int Entities::get_x()
{
    return _x;
}

int Entities::get_y()
{
    return _y;
}

int Entities::get_score()
{
    return score;
}

void Entities::set_score(int s)
{
    score = s;
}

