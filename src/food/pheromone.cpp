#include "food.h"
#include "../game.h"

Pheromone::Pheromone(coord xy, Game *game, int s, bool display_it) : QGraphicsEllipseItem(xy.x, xy.y, s, s){
    this->height = s;
    this->game = game;
    this->position = xy;
    this->setBrush(*(game->pheromone_brush));
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

coord Pheromone::get_pos(){
    return position;
}