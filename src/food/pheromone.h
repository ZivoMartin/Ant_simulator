#ifndef safe_pheromone
#define safe_pheromone

#include "../cercles/cercles.h"

class Game;

class Pheromone : public Circle{

public:
    Pheromone(coord xy, Game *game, bool display_it, QColor *color);
    ~Pheromone();
    coord *get_pos() override;
    void display() override;
    void remove() override;

    
private:
    Game *game;
    coord position;
    bool visible = false;
};

#endif