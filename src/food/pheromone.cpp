#include "food.h"
#include "../game.h"

Pheromone::Pheromone(coord xy, Game *game, bool display_it, QColor *color) : QGraphicsEllipseItem(xy.x, xy.y, game->phero_img_size, game->phero_img_size){
    this->game = game;
    this->position = xy;
    QBrush brush(*color);
    this->setBrush(brush);
    if(display_it){
        display();
    }
} 

Pheromone::~Pheromone(){
    if(visible){
        game->get_view()->get_scene()->removeItem(this);
    }
}

void Pheromone::display(){
    game->get_view()->get_scene()->addItem(this);
    visible = true;
}

void Pheromone::remove(){
    game->get_view()->get_scene()->removeItem(this);
    visible = false;
}

coord *Pheromone::get_pos(){
    return &position;
}