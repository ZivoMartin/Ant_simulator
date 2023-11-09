#include "anthill.h"
#include "../game.h"

Anthill::Anthill(Game *game, coord xy) : My_image(game->anthill_img, game->get_view()->get_scene(), xy){
    position = xy;
    position.x += game->anthill_size/2;
    position.y += game->anthill_size/2;
}   

Anthill::~Anthill(){
    
}


void Anthill::set_pos(coord xy){
    set_pos_img(xy);
}

coord *Anthill::get_pos(){
    return &position;
}


