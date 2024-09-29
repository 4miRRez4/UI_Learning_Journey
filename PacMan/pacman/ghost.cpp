#include "ghost.h"
#include "game.h"

Ghost::Ghost(Game* g, int r) :game(g), Entities(Entities::Ghost, QPixmap())
{
    is_in_cage = true;;
    currDir = moveDir(QRandomGenerator::global()->generate() % 4);
    stat = Normal;
    color = (Color)r;
    animation_ind = 0;

    load_ghost_animations();
}


void Ghost::load_ghost_animations(){
    for(int j=0; j<2; j++)
        for(int direc=0; direc<4; direc++)
            for(int i=1; i<3; i++)
                animations[direc].push_back(QPixmap(":/resrcs/imgs/ghostsPics/" + QString::number(color) + QString::number(direc) + QString::number(i) + ".png"));
    panic_anim.push_back(QPixmap(":/resrcs/imgs/ghostsPics/bl1.png"));
    panic_anim.push_back(QPixmap(":/resrcs/imgs/ghostsPics/bl2.png"));
    running_anim.push_back(QPixmap(":/resrcs/imgs/ghostsPics/run.png"));
    setPixmap(animations[Right][0]);
}

Ghost::Color Ghost::get_color(){
    return color;
}

void Ghost::which_dir_can_go(QVector<moveDir>& canGoVec, QVector<bool>& canGoDir){
    if (can_ghost_go(_y, _x + 1)) {
        canGoDir[Right] = true;
        canGoVec.push_back(Right);
    }
    if (can_ghost_go(_y, _x - 1)) {
        canGoDir[Left] = true;
        canGoVec.push_back(Left);
    }
    if (can_ghost_go(_y + 1, _x)) {
        canGoDir[Down] = true;
        canGoVec.push_back(Down);
    }
    if (can_ghost_go(_y - 1, _x)) {
        canGoDir[Up] = true;
        canGoVec.push_back(Up);
    }
}

bool Ghost::can_ghost_go(int i, int j)
{
    if (i < 0 || j < 0)
        return false;

    if (i >= game->map_height || j >= game->map_width)
        return false;
    entityType t = game->map[i][j]->get_type();
    if(t == Wall)
        return false;
    else if(t == Gate){
        if(is_in_cage == true && release_time==0)
            return true;
        else if(stat == Running)
            return true;
        else
            return false;
    }
    return true;
}

Entities::moveDir Ghost::backward_of_dir(Entities::moveDir currDir){
    switch (currDir) {
        case Entities::Up:
            return Entities::Down;
        case Entities::Down:
            return Entities::Up;
        case Entities::Left:
            return Entities::Right;
        case Entities::Right:
            return Entities::Left;
        case Entities::Stop:
            return Entities::Stop;
    }
}

void Ghost::chase()
{
    QVector<bool> canGoDir(5, false);
    QVector<moveDir> canGoVec;
    which_dir_can_go(canGoVec, canGoDir);

    moveDir backward_dir = backward_of_dir(currDir);


    //change direction when not in intersection
    if (canGoVec.size() > 2) {
        int x_dis = this->game->pacman->get_x() - _x;
        int y_dis = this->game->pacman->get_y() - _y;
        if (y_dis > 0) {
            if (canGoDir[Down] && currDir != Up) {
                currDir = Down;
            } else {
                if (x_dis >= 0) {
                    if (canGoDir[Right])
                        currDir = Right;
                    else if (canGoDir[Left])
                        currDir = Left;
                } else {
                    if (canGoDir[Left]) {
                        currDir = Left;
                    } else if (canGoDir[Right]) {
                        currDir = Right;
                    }
                }
            }
        } else if (y_dis < 0) {
            if (canGoDir[Up] && currDir != Down) {
                currDir = Up;
            } else {
                if (x_dis >= 0) {
                    if (canGoDir[Right]) {
                        currDir = Right;
                    } else if (canGoDir[Left]) {
                        currDir = Left;
                    }
                } else {
                    if (canGoDir[Left]) {
                        currDir = Left;
                    } else if (canGoDir[Right]) {
                        currDir = Right;
                    }
                }
            }
        } else if (x_dis > 0) {
            if (canGoDir[Right] && currDir != Left) {
                currDir = Right;
            } else {
                if (canGoDir[Up]) {
                    currDir = Up;
                } else if(canGoDir[Down]) {
                    currDir = Down;
                }
            }
        } else if (x_dis < 0) {
            if (canGoDir[Left] && currDir != Right) {
                currDir = Left;
            } else {
                if (canGoDir[Up]) {
                    currDir = Up;
                } else if(canGoDir[Down]) {
                    currDir = Down;
                }
            }
        }
    } else if (canGoVec.size() == 2) {
        if (canGoDir[currDir] == false) {
            // ghost on corner
            if (canGoVec[0] == backward_dir) {
                currDir = canGoVec[1];
            } else {
                currDir = canGoVec[0];
            }
        }
    }
}

void Ghost::run_from_pacman()
{
    QVector<bool> canGoDir (5, false);
    QVector<moveDir> canGoVec;
    which_dir_can_go(canGoVec, canGoDir);

    moveDir backward_dir = backward_of_dir(currDir);

    //change direction when not in intersection
    if (canGoVec.size() > 2) {
        int x_dis = this->game->pacman->get_x() - _x;
        int y_dis = this->game->pacman->get_y() - _y;
        if (y_dis < 0) {
            if (canGoDir[Down] && currDir != Up) {
                currDir = Down;
            } else {
                if (x_dis >= 0) {
                    if (canGoDir[Left]) {
                        currDir = Left;
                    } else if (canGoDir[Right]) {
                        currDir = Right;
                    }
                } else {
                    if (canGoDir[Right]) {
                        currDir = Right;
                    } else if (canGoDir[Left]) {
                        currDir = Left;
                    }
                }
            }
        } else if (y_dis > 0) {
            if (canGoDir[Up] && currDir != Down) {
                currDir = Up;
            } else {
                if (x_dis >= 0) {
                    if (canGoDir[Left]) {
                        currDir = Left;
                    } else if (canGoDir[Right]) {
                        currDir = Right;
                    }
                } else {
                    if (canGoDir[Right]) {
                        currDir = Right;
                    } else if (canGoDir[Left]) {
                        currDir = Left;
                    }
                }
            }
        } else if (x_dis < 0) {
            if(canGoDir[Right] && currDir != Left) {
                currDir = Right;
            } else {
                if (canGoDir[Up]) {
                    currDir = Up;
                } else if(canGoDir[Down]) {
                    currDir = Down;
                }
            }
        } else if (x_dis > 0) {
            if(canGoDir[Left] && currDir != Right) {
                currDir = Left;
            } else {
                if (canGoDir[Up]) {
                    currDir = Up;
                } else if(canGoDir[Down]) {
                    currDir = Down;
                }
            }
        }
    } else if (canGoVec.size() == 2) {
        if (canGoDir[currDir] == false) {
            // ghost is on a corner
            if (canGoVec[0] == backward_dir) {
                currDir = canGoVec[1];
            } else {
                currDir = canGoVec[0];
            }
        }
    }
}

void Ghost::go_out_cage()
{
    int x_dis_from_gate= game->gate->_x - _x;
    int y_dis_from_gate= game->gate->_y - _y;

    if (x_dis_from_gate > 0)
        set_curr_dir(Right);
    else if (x_dis_from_gate < 0)
        set_curr_dir(Left);
    else {
        if (y_dis_from_gate > 0)
            set_curr_dir(Down);
        else
            set_curr_dir(Up);
    }
}

void Ghost::go_to_cage()
{
    QVector<bool> canGoDir (5, false);
    QVector<moveDir> canGoVec;
    which_dir_can_go(canGoVec, canGoDir);

    moveDir backward_dir = backward_of_dir(currDir);


    //change direction when not in intersection
    if (canGoVec.size() > 2) {
        int x_dis_from_gate = game->gate->get_x() - _x;
        int y_dis_from_gate = (game->gate->get_y() + 1) - _y;
        if (y_dis_from_gate > 0) {
            if (canGoDir[Down] && currDir != Up) {
                currDir = Down;
            } else {
                if (x_dis_from_gate >= 0) {
                    if (canGoDir[Right]) {
                        currDir = Right;
                    } else if (canGoDir[Left]) {
                        currDir = Left;
                    }
                } else {
                    if (canGoDir[Left]) {
                        currDir = Left;
                    } else if (canGoDir[Right]) {
                        currDir = Right;
                    }
                }
            }
        } else if (y_dis_from_gate < 0) {
            if (canGoDir[Up] && currDir != Down) {
                currDir = Up;
            } else {
                if (x_dis_from_gate >= 0) {
                    if (canGoDir[Right]) {
                        currDir = Right;
                    } else if (canGoDir[Left]) {
                        currDir = Left;
                    }
                } else {
                    if (canGoDir[Left]) {
                        currDir = Left;
                    } else if (canGoDir[Right]) {
                        currDir = Right;
                    }
                }
            }
        } else if (x_dis_from_gate > 0) {
            if(canGoDir[Right] && currDir != Left) {
                currDir = Right;
            } else {
                if (canGoDir[Up]) {
                    currDir = Up;
                } else if (canGoDir[Down]) {
                    currDir = Down;
                }
            }
        } else if (x_dis_from_gate < 0) {
            if(canGoDir[Left] && currDir != Right) {
                currDir = Left;
            } else {
                if (canGoDir[Up]) {
                    currDir = Up;
                } else if (canGoDir[Down]) {
                    currDir = Down;
                }
            }
        }
    } else if (canGoVec.size() == 2) {
        if (canGoDir[currDir] == false) {
            // ghost on corner
            if (canGoVec[0] == backward_dir) {
                currDir = canGoVec[1];
            } else {
                currDir = canGoVec[0];
            }
        }
    }
}

void Ghost::random_dir()
{
    QVector<bool> canGoDir (5, false);//recive this from argument
    QVector<moveDir> canGoVec;
    which_dir_can_go(canGoVec, canGoDir);
    currDir = canGoVec.at(QRandomGenerator::global()->generate() % canGoVec.size());
}

void Ghost::step_up(){
    setY(static_cast<int>(y()) - 1);
}

void Ghost::step_down()
{
    setY(static_cast<int>(y()) + 1);
}

void Ghost::step_right()
{
    setX(static_cast<int>(x()) + 1);
}

void Ghost::step_left()
{
    setX(static_cast<int>(x()) - 1);
}


void Ghost::move(){
    if (stat != Running && release_time > 0) {
        release_time--;
    } else if (stat == Panic) {
        panic_time--;
        if (panic_time <= 0) {
            stat = Normal;
            game->ghost_motion[color]->setInterval(NORMAL_INTERVAL);
        }
    }

    int x_of_ghost = static_cast<int>(x());
    int y_of_ghost = static_cast<int>(y());
    int x_coordinate_in_map = (x_of_ghost - game->x_of_obj) / Entities::ObjWidth;
    int y_coordinate_in_map = (y_of_ghost - game->y_of_obj) / Entities::ObjWidth;
    int x_distance_from_bound = (x_of_ghost - game->x_of_obj) % Entities::ObjWidth;
    int y_distance_from_bound = (y_of_ghost - game->y_of_obj) % Entities::ObjWidth;

    if (x_distance_from_bound == 0 && y_distance_from_bound == 0) {
        // updating ghost coordinate in map
        _x = x_coordinate_in_map;
        _y = y_coordinate_in_map;

        if (!is_in_cage) {
            switch (stat) {
                case Normal:
                    chase();
                    break;
                case Panic:
                    run_from_pacman();
                    break;
                default:
                    break;
            }
        } else {
            if (release_time == 0) {
                go_out_cage();
                if (game->map[_y][_x]->get_type() == Gate)
                    is_in_cage = false;
            } else {
                if (stat == Running) {
                    if (_x == game->gate->get_x() && _y == game->gate->get_y() + 1){
                        stat = Normal;
                        game->ghost_motion[color]->setInterval(NORMAL_INTERVAL);
                    }
                    else
                        go_to_cage();
                }
                else
                    random_dir();
            }
        }
    }

    QVector<QPixmap> *whichAnim;
    switch (stat) {
    case Normal:
        whichAnim = &animations[currDir];
        break;
    case Panic:
        whichAnim = &panic_anim;
        break;
    case Running:
        whichAnim = &running_anim;
        break;
    }

    animation_ind++;
    if (animation_ind >= whichAnim->size()) {
        animation_ind = 0;
    }
    setPixmap((*whichAnim)[animation_ind]);

    switch (currDir) {
        case Stop:
            break;
        case Up:
            step_up();
            break;
        case Down:
            step_down();
            break;
         case Right:
            step_right();
            break;
        case Left:
            step_left();
            break;

    }

    //did ghost hit pacman?
    if (collidesWithItem(game->pacman, Qt::IntersectsItemShape)){
        if (stat == Normal) {
            game->gstat = Game::Lose;
        } else if (stat == Panic) {
            QMediaPlayer* eat_ghost_snd = new QMediaPlayer;
            eat_ghost_snd->setMedia(QUrl("qrc:/resrcs/sounds/eat_ghost.mp3"));
            eat_ghost_snd->setVolume(75);
            eat_ghost_snd->play();

            setPixmap(QPixmap(":/rescrs/imgs/ghostsPics/run.png"));
            game->score += score;
            stat = Running;
            release_time = 200;
            is_in_cage = true;
            game->ghost_motion[color]->setInterval(RUNNING_INTERVAL);
        }
    }

}
