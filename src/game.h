#ifndef safe_game
#define safe_game

#include <QMainWindow>
#include <iostream>
#include <random>
#include <QTimer>
#include "view/my_view.h"
#include "image/my_image.h"
#include "ant/ant.h"
#include "ant/anthill.h"


class Game : public QMainWindow{

public: 
    Game(My_view *view);
    ~Game();
    void build_image();
    My_view *get_view();
    void init_ant_tab();
    void move_ants();
    void start();
    void delete_ant(int i);

    QPixmap ant_img;
    QPixmap anthill_img;

    static const int map_height = 1000;
    static const int map_width = 1000;

private:
    My_view *view;
    std::vector<Ant*> ant_tab;
    Anthill *anthill;
    int nb_start_ant = 10;
    coord anthill_coord;

};

int random(int min, int max);
int get_dist(coord xy1, coord xy2)

#endif