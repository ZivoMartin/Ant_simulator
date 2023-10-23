#include "game.h"

Game::Game(My_view *view): QMainWindow(){
    this->view = view;
    view->resize(width, height);
    build_image();

}

Game::~Game(){
}

My_view *Game::get_view(){
    return view;
}


void Game::build_image(){
    ant_img.load("../images/ant.png");
    ant_img = ant_img.scaled(30, 30);
    anthill_img.load("../images/anthill.png");
    anthill_img = anthill_img.scaled(30, 30);
}   