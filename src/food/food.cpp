#include "food.h"
#include "../game.h"

Food::Food(coord xy, Game *game, int s) : QGraphicsEllipseItem(xy.x, xy.y, s, s){
    this->height = s;
    this->game = game;
    this->position = xy;
    this->origin = xy;
    this->setBrush(*(game->food_brush));
    game->get_view()->get_scene()->addItem(this);
} 

Food::~Food(){
    game->get_view()->get_scene()->removeItem(this);
    if(already_have_phero_path){
        unsigned int size = phero_tab.size();
        for(unsigned int i=0; i<size; i++){
            delete phero_tab[i];
        }
        size = fake_phero_tab.size();
        for(unsigned int i=0; i<size; i++){
            delete fake_phero_tab[i];
        }
    }
    game->actualise_ant_state(this);
}

bool Food::decrease_nb_food_remain(){
    nb_food_remain -= 1;
    return nb_food_remain == 0;
}

void Food::set_pos(coord xy){
    setPos(xy.x-origin.x, xy.y - origin.y);
}

void Food::add_pheromone(coord xy){
    phero_tab.insert(phero_tab.begin(), new Pheromone(xy, game, game->pheromone_size, false));
}

void Food::add_fake_pheromone(coord xy){
    fake_phero_tab.insert(fake_phero_tab.begin(), new Pheromone(xy, game, game->pheromone_size, game->get_view_state() == 1));
}

bool Food::get_phero_path_bool(){
    return already_have_phero_path;
}

coord Food::get_pos(){
    return position;
}

void Food::path_created(){
    already_have_phero_path = true;
}

int Food::get_nb_phero(){
    return phero_tab.size();
}

int Food::get_nb_fake_phero(){
    return fake_phero_tab.size();
}

Pheromone *Food::get_fake_pheromone(int i){
    return fake_phero_tab[i];
}

Pheromone *Food::get_pheromone(int i){
    return phero_tab[i];
}