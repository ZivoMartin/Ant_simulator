#include "food.h"
#include "../game.h"

Food::Food(coord xy, Game *game) : QGraphicsEllipseItem(xy.x, xy.y, game->size_food, game->size_food){
    this->game = game;
    this->position = xy;
    this->setBrush(*(game->food_brush));
    game->get_view()->get_scene()->addItem(this);
} 

Food::~Food(){}

bool Food::decrease_nb_food_remain(){
    nb_food_remain -= 1;
    if(nb_food_remain == 0){
        game->get_view()->get_scene()->removeItem(this);
        return true;
    }else{
        return false;
    }
}

coord Food::get_pos(){
    return position;
}