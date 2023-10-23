#include "ant.h"
#include "../game.h"

Ant::Ant(Game *game, coord xy) : My_image(game->ant_img, game->get_view()->get_scene(), xy){
}   

Ant::~Ant(){}


void Ant::set_pos(coord xy){
    set_pos_img(xy);
}


