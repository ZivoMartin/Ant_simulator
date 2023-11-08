#include "food.h"
#include "../game.h"

Pheromone::Pheromone(coord xy, Game *game, bool display_it, QColor *color) : Circle(*color, game->get_view()->get_scene(), game->pheromone_size, xy){
    this->game = game;
    this->position = xy;
    if(!display_it){
        remove();
    }
} 

Pheromone::~Pheromone(){
}

void Pheromone::display(){
    scene->addItem(this);
    visible = true;
}

void Pheromone::remove(){
    scene->removeItem(this);
    visible = false;
}

coord *Pheromone::get_pos(){
    return &position;
}