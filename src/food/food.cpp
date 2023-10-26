#include "food.h"
#include "../game.h"

Food::Food(coord xy, Game *game, int s) : QGraphicsEllipseItem(xy.x, xy.y, s, s){
    int height = s;
    this->game = game;
    this->position = xy;
    this->origin = xy;
    this->setBrush(*(game->food_brush));
    game->get_view()->get_scene()->addItem(this);
} 

Food::~Food(){
    game->get_view()->get_scene()->removeItem(this);
}

bool Food::decrease_nb_food_remain(){
    nb_food_remain -= 1;
    return nb_food_remain == 0;
}

void Food::set_pos(coord xy){
    setPos(xy.x-origin.x, xy.y - origin.y);
}



coord Food::get_pos(){
    return position;
}