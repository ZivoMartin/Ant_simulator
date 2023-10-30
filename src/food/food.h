#ifndef safe_food
#define safe_food

#include <QGraphicsEllipseItem>
#include <QColor>
#include <QBrush>
#include "pheromone.h"

class Game;

class Food : public QGraphicsEllipseItem{

public:
    Food(coord xy, Game *game, int h);
    ~Food();
    bool decrease_nb_food_remain();
    coord get_pos();
    void set_pos(coord xy);
    void add_pheromone(coord xy);
    void add_fake_pheromone(coord xy);
    bool get_phero_path_bool();
    void path_created();
    int get_nb_phero();
    Pheromone *get_pheromone(int i);
    int get_nb_fake_phero();
    Pheromone *get_fake_pheromone(int i);


private:
    Game *game;
    int nb_food_remain = 30;
    coord position;
    coord origin;
    int height;
    bool already_have_phero_path = false;
    std::vector<Pheromone*> phero_tab;
    std::vector<Pheromone*> fake_phero_tab; 
};

#endif