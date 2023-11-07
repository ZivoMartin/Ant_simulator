#ifndef safe_pheromone
#define safe_pheromone

#include <QGraphicsEllipseItem>
#include <QColor>
#include <QBrush>
#include <iostream>
#include "../struct/coord.h"

class Game;

class Pheromone : public QGraphicsEllipseItem{

public:
    Pheromone(coord xy, Game *game, bool display_it, QColor *color);
    ~Pheromone();
    coord *get_pos();
    void display();
    void remove();

    
private:
    Game *game;
    coord position;
    bool visible = false;
};

#endif