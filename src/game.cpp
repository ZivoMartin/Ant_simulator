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
    setup_scene();
    build_image();
    build_brush();
    anthill = new Anthill(this, anthill_coord);
    init_ant_tab();
    init_food_spots();
    start();
}

Game::~Game(){
    int size = ant_tab.size();
    for(int i=0; i<size; i++){
        delete ant_tab[i];
    }
    size = food_tab.size();
    for(int i=0; i<size; i++){
        delete food_tab[i];
    }
    delete anthill;
    delete food_brush;
}

void Game::setup_scene(){
    QColor backgroundColor(210, 180, 140);
    view->get_scene()->setBackgroundBrush(backgroundColor);
    QPointF centerPoint(anthill_coord.x-1500, anthill_coord.y-900);
    view->centerOn(centerPoint);
    view->get_scene()->setSceneRect(0, 0, map_width, map_height);
    QTransform transform = view->transform();
    double zoomFactor = 2.0;
    transform.scale(1.0 / zoomFactor, 1.0 / zoomFactor);
    view->setTransform(transform);
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

Food *Game::get_food(unsigned int i){
    return food_tab[i];
}

int Game::get_nb_food_spot(){
    return food_tab.size();
}

void Game::build_brush(){
    QColor color(0, 154, 23);
    this->food_brush = new QBrush(color);
} 

void Game::init_ant_tab(){
    for(int i=0; i<nb_start_ant; i++){
        ant_tab.push_back(new Ant(this, anthill_coord));
    }
}

void Game::init_food_spots(){
    for(int i=0; i<nb_start_food_spot; i++){
        food_tab.push_back(new Food({random(0, map_width), random(0, map_height)}, this));
    }
}

void Game::start(){
    QTimer::singleShot(20, this, [=](){
        move_ants();
        view->update();
        iter += 1;
        start();
    });
}

void Game::move_ants(){
    unsigned int size = ant_tab.size();
    for(unsigned int i=0; i<size; i++){
        ant_tab[i]->move();
    }
}

int Game::get_iter(){
    return iter;
}

int get_dist(coord xy1, coord xy2){
    return (xy1.x-xy2.x)*(xy1.x-xy2.x) + (xy1.y-xy2.y)*(xy1.y-xy2.y);
}

