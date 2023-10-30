#include "my_view.h"
#include "../game.h"

My_view::My_view() : QGraphicsView(){
    this->scene = new QGraphicsScene();
    setScene(scene);
}

My_view::~My_view(){
    delete scene;
}

QGraphicsScene * My_view::get_scene(){
    return scene;
}

void My_view::keyPressEvent(QKeyEvent* event){
    int key = event->key();
    if(key == Qt::Key_A) {
        game->change_view_state();
    }else if(key == Qt::Key_Up){
        zoom(1.2);
    }else if(key == Qt::Key_Down){
        zoom(0.8);
    }
}

void My_view::set_game(Game *game){
    this->game = game;
}

void My_view::set_bg_color(QColor *color){
    QBrush brush(*color);
    scene->setBackgroundBrush(brush);
}

void My_view::zoom(double factor){
    setTransform(transform().scale(1.0/factor, 1.0/factor));
}