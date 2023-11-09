#include "anthill.h"
#include "../game.h"

Anthill::Anthill(Game *game, coord xy) : My_image(game->anthill_img, game->get_view()->get_scene(), xy){
}   

Anthill::~Anthill(){
    
}


void Anthill::set_pos(coord xy){
    set_pos_img(xy);
}



