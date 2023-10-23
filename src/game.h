#ifndef safe_game
#define safe_game

#include <QMainWindow>
#include <iostream>
#include "view/my_view.h"
#include "image/my_image.h"
#include "src/ant/ant.h"
#include "src/ant/anthill.h"


class Game : public QMainWindow{

public: 
    Game(My_view *view);
    ~Game();
    void build_image();
    My_view *get_view();

    QPixmap ant_img;
    QPixmap anthill_img;

    static const int height = 1000;
    static const int width = 1000;

private:
    My_view *view;
    std::vector<Ant> ant_tab;
    Anthill *anthill;
    int nb_ant;

};

#endif