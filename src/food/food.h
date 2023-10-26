#ifndef safe_food
#define safe_food

#include <QGraphicsEllipseItem>
#include <QColor>
#include <QBrush>
#include "../struct/coord.h"

class Game;

class Food : public QGraphicsEllipseItem{

public:
    Food(coord xy, Game *game, int h);
    ~Food();
    bool decrease_nb_food_remain();
    coord get_pos();
    void set_pos(coord xy);
    
private:
    Game *game;
    int nb_food_remain = 30;
    coord position;
    coord origin;
};

#endif