#include "pacmanclass.h"
#include "game.h"

pacManClass::pacManClass(Game* g) :game(g), Entities(Entities::Pacman, QPixmap(":/resrcs/imgs/pacmanPics/33.png"))
{
    currDir = Stop;
    nextDir = Stop;
    animation_ind = 2;

    load_pacman_animations();
}

void pacManClass::load_pacman_animations(){
    for(int direc=0; direc<4; direc++){
        for(int i=0; i<=5; i++)
            animation[direc].push_back(":/resrcs/imgs/pacmanPics/" + QString::number(direc) + QString::number(i) + ".png");
        for(int i=4; i>=1; i--)
            animation[direc].push_back(":/resrcs/imgs/pacmanPics/" + QString::number(direc) + QString::number(i) + ".png");
    }
}

void pacManClass::step_up(){
    animation_ind++;
    if (animation_ind == animation[Up].size())
        animation_ind = 0;
    setPixmap(animation[Up][animation_ind]);
    setY(static_cast<int>(y()) - 1);
}

void pacManClass::step_down()
{
    animation_ind++;
    if (animation_ind == animation[Down].size())
        animation_ind = 0;
    setPixmap(animation[Down][animation_ind]);
    setY(static_cast<int>(y()) + 1);
}

void pacManClass::step_right()
{
    animation_ind++;
    if (animation_ind == animation[Right].size())
        animation_ind = 0;
    setPixmap(animation[Right][animation_ind]);
    setX(static_cast<int>(x()) + 1);
}

void pacManClass::step_left()
{
    animation_ind++;
    if (animation_ind == animation[Left].size())
        animation_ind = 0;
    setPixmap(animation[Left][animation_ind]);
    setX(static_cast<int>(x()) - 1);
}


bool pacManClass::can_pacman_go(int i, int j){
    if (i < 0 || j < 0)
        return false;
    if (i >= game->map_height || j >= game->map_width)
        return false;

    auto elementType = game->map[i][j]->get_type();
    if(elementType == Entities::entityType::Wall || elementType == Entities::entityType::Gate)
        return false;

    return true;
}

void pacManClass::eat_ball(int y_coordiate_in_map, int x_coordinate_in_map)
{
    Entities *entityAtCoordinate = game->map[y_coordiate_in_map][x_coordinate_in_map];

    if(entityAtCoordinate->get_type() == Ball){
        QMediaPlayer* pacmanEatingSound = new QMediaPlayer;
        pacmanEatingSound->setMedia(QUrl("qrc:/resrcs/sounds/eat.mp3"));
        pacmanEatingSound->setVolume(75);
        pacmanEatingSound->play();

        game->score += entityAtCoordinate->get_score();
        game->numOfBall--;
    }else if(entityAtCoordinate->get_type() == BigBall){
        QMediaPlayer* pacmanEatingSound = new QMediaPlayer;
        pacmanEatingSound->setMedia(QUrl("qrc:/resrcs/sounds/eat_big_ball.mp3"));
        pacmanEatingSound->setVolume(75);
        pacmanEatingSound->play();

        game->score += entityAtCoordinate->get_score();
        game->numOfBall--;
        for (int i = 0; i < game->bigBalls.size(); i++) {
            if (game->bigBalls.at(i) == entityAtCoordinate) {
                game->bigBalls.remove(i);
                break;
            }
        }

        for (int i = 0; i < 4; i++) {
            if (game->ghost[i]->stat != Ghost::Running) {
                game->ghost[i]->stat = Ghost::Panic;
                game->ghost[i]->panic_time = PANNIC_TIME;
                game->ghost_motion[i]->setInterval(PANNIC_INTERVAL);
            }
        }
    }else {
        return;
    }

    //blank after eating ball
    QPixmap blankpix;
    game->map[_y][_x] = new Entities(Entities::Blank, blankpix);
    game->map[y_coordiate_in_map][x_coordinate_in_map] = this;
    delete entityAtCoordinate;
}

void pacManClass::movement(){
    int x_of_pacman = static_cast<int>(x());
    int y_of_pacman = static_cast<int>(y());
    int x_coordinate_in_map = (x_of_pacman - game->x_of_obj) / Entities::ObjWidth;
    int y_coordinate_in_map = (y_of_pacman - game->y_of_obj) / Entities::ObjWidth;
    int x_distance_from_bound = (x_of_pacman - game->x_of_obj) % Entities::ObjWidth;
    int y_distance_from_bound = (y_of_pacman - game->y_of_obj) % Entities::ObjWidth;
    moveDir next_dir = get_next_dir();

    //changing direction when pacman fits a block
    if (x_distance_from_bound == 0) {
        if (y_distance_from_bound == 0) {
            eat_ball(y_coordinate_in_map, x_coordinate_in_map);

            // update pacman's coordinate in map
            _x = x_coordinate_in_map;
            _y = y_coordinate_in_map;

            //has pacman eaten all balls?
            if (game->numOfBall == 0) {
                game->gstat = Game::Win;
                return;
            }
        }

        switch (next_dir) {
        case Stop:
            currDir = next_dir;
            break;
        case Up:
            if (can_pacman_go(_y - 1, _x))
                currDir = next_dir;
            break;
        case Down:
            if (can_pacman_go(_y + 1, _x))
                currDir = next_dir;
            break;
        case Left:
            if (y_distance_from_bound == 0 && can_pacman_go(_y, _x - 1))
                currDir = next_dir;
            break;
        case Right:
            if (y_distance_from_bound == 0 && can_pacman_go(_y, _x + 1))
                currDir = next_dir;
            break;
        }
    } else if (y_distance_from_bound == 0) {
        switch (next_dir) {
        case Stop:
            currDir = next_dir;
            break;
        case Left:
            if (can_pacman_go(_y, _x - 1))
                currDir = next_dir;
            break;
        case Right:
            if (can_pacman_go(_y, _x + 1)) {
                currDir = next_dir;
            }
            break;
        default:                    //when x_distance_from_bound = 0
            break;
        }
    }


    switch (currDir) {// keep moving till hitting a wall
    case Stop:
        break;
    case Up:
        if (y_distance_from_bound == 0 && !can_pacman_go(_y - 1, _x))
            currDir = next_dir = Stop;
        else
            step_up();
        break;
    case Down:
        if (y_distance_from_bound == 0 && !can_pacman_go(_y + 1, _x))
            currDir = next_dir = Stop;
        else
            step_down();
        break;
    case Left:
        if (x_distance_from_bound == 0 && !can_pacman_go(_y, _x - 1))
            currDir = next_dir = Stop;
        else
            step_left();
        break;
    case Right:
        if (x_distance_from_bound == 0 && !can_pacman_go(_y, _x + 1))
            currDir = next_dir = Stop;
        else
            step_right();
        break;
    }
}




