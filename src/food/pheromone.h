#ifndef safe_pheromone
#define safe_pheromone

#include <QGraphicsEllipseItem>
#include <QColor>
#include <QBrush>
#include "../struct/coord.h"

class Game;

class Pheromone : public QGraphicsEllipseItem{

public:
    Pheromone(coord xy, Game *game, int h, bool display_it);
    ~Pheromone();
    coord get_pos();
    void display();
    void remove();

    
private:
    Game *game;
    coord position;
    int height;
    bool visible = false;
};

#endif