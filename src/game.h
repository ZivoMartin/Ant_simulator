#ifndef safe_game
#define safe_game

#include <QMainWindow>
#include <random>
#include <QTimer>
#include <QPointF>
#include "view/my_view.h"
#include "image/my_image.h"
#include "ant/ant.h"
#include "ant/anthill.h"
#include "food/food.h"


class Game : public QMainWindow{

public: 
    Game(My_view *view);
    ~Game();
    void build_image();
    void build_brush();
    My_view *get_view();
    void init_ant_tab();
    void init_food_spots();
    void move_ants();
    void start();
    void delete_ant(int i);
    int get_iter();
    void setup_scene();
    Food *get_food(unsigned int i);
    int get_nb_food_spot();

    QPixmap ant_img;
    QPixmap anthill_img;

    static const int map_height = 15000;
    static const int map_width = 15000;
    static const int size_food = 100;
    static const int range_ant = 1000;
    static const int ant_speed = 5;

    QBrush *food_brush;

private:
    My_view *view;
    std::vector<Ant*> ant_tab;
    std::vector<Food*> food_tab;
    Anthill *anthill;
    int nb_start_ant = 1; 
    int nb_start_food_spot = 100; 
    coord anthill_coord;
    int iter = 0;
};

int random(int min, int max);
int get_dist(coord xy1, coord xy2);

#endif