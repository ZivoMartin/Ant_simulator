#include "game.h"


int random(int min, int max){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> random_nbr(min, max);
    return(random_nbr(generator));
}


Game::Game(My_view *view): QMainWindow(){
    this->view = view;
    this->anthill_coord = {map_width/2, map_height/2};
    QTransform transform = view->transform();
    double zoomFactor = 2.0;
    transform.scale(1.0 / zoomFactor, 1.0 / zoomFactor);
    view->setTransform(transform);
    view->resize(map_width, map_height);
    view->get_scene()->setSceneRect(0, 0, map_width, map_height);

    build_image();
    anthill = new Anthill(this, anthill_coord);
    init_ant_tab();
    start();
}

Game::~Game(){
    for(int i=0; i<nb_start_ant; i++){
        delete ant_tab[i];
    }
    delete anthill;
}

My_view *Game::get_view(){
    return view;
}

void Game::delete_ant(int i){
    delete ant_tab[i];
}

void Game::build_image(){
    ant_img.load("../images/ant.png");
    ant_img = ant_img.scaled(70, 70);
    anthill_img.load("../images/anthill.png");
    anthill_img = anthill_img.scaled(200, 200);
}   

void Game::init_ant_tab(){
    for(int i=0; i<nb_start_ant; i++){
        ant_tab.push_back(new Ant(this, anthill_coord));
    }
}

void Game::start(){
    QTimer::singleShot(20, this, [=](){
        move_ants();
        view->update();
        start();
    });
}

void Game::move_ants(){
    unsigned int size = ant_tab.size();
    for(unsigned int i=0; i<size; i++){
        ant_tab[i]->move();
    }
}

int get_dist(coord xy1, coord xy2){
    return (xy1.x-xy2.x)*(xy1.x-xy2.x) + (xy1.y-xy2.y)*(xy1.y-xy2.y);
}