#include "food.h"
#include "../game.h"
#include "../ant/ant.h"

Food::Food(coord xy, Game *game, int s) : Circle(game->get_food_color(), game->get_view()->get_scene(), s, xy){
    this->game = game;
    this->position = xy;
    this->origin = xy;
    phero_tab.resize(game->get_nb_anthill());
    fake_phero_tab.resize(game->get_nb_anthill());
    ant_tab.resize(game->get_nb_anthill());
    init_main_ants_tab();
} 

Food::~Food(){
    for(int j=0; j<game->get_nb_anthill(); j++){
        if(get_phero_path_bool(j)){
            unsigned int size = phero_tab[j].size();
            for(unsigned int i=0; i<size; i++){
                delete phero_tab[j][i];
            }
            size = fake_phero_tab[j].size();
            for(unsigned int i=0; i<size; i++){
                delete fake_phero_tab[j][i];
            }
            if(main_ant[j] != nullptr){
                main_ant[j]->change_authorisation();
            }
        }
    }
    game->actualise_ant_state(this);
}

void Food::remove_ant(Ant *ant){
    int id_colonie = ant->get_id_colonie();
    int size = ant_tab[id_colonie].size();
    for(int i=0; i<size; i++){
        if(ant_tab[id_colonie][i] == ant){
            ant_tab[id_colonie].erase(ant_tab[id_colonie].begin()+i);
            break;
        }
    }
    reset_opponent(ant);
}


bool Food::decrease_nb_food_remain(){
    nb_food_remain -= 1;
    return nb_food_remain <= 0;
}


void Food::set_pos(coord xy){
    setPos(xy.x-origin.x, xy.y - origin.y);
}

void Food::add_pheromone(coord xy, int id_colonie){
    phero_tab[id_colonie].push_back(new Pheromone(xy, game, false, game->get_color(id_colonie)));
}

void Food::add_fake_pheromone(coord xy, int id_colonie){
    fake_phero_tab[id_colonie].push_back(new Pheromone(xy, game, game->get_view_state() == 1, game->get_color(id_colonie)));
}

bool Food::get_phero_path_bool(int id_colonie){
    return fake_phero_tab[id_colonie].size() != 0 || main_ant[id_colonie] != nullptr;
}

coord *Food::get_pos(){
    return &position;
}

void Food::path_created(Ant *ant){
    main_ant[ant->get_id_colonie()] = ant;
}

int Food::get_nb_phero(int id_colonie){
    return phero_tab[id_colonie].size();
}

int Food::get_nb_fake_phero(int id_colonie){
    return fake_phero_tab[id_colonie].size();
}

Pheromone *Food::get_fake_pheromone(int i, int id_colonie){
    return fake_phero_tab[id_colonie][i];
}

Pheromone *Food::get_pheromone(int i, int id_colonie){
    return phero_tab[id_colonie][i];
}

void Food::delete_main_ant(int id_colonie){
    main_ant[id_colonie] = nullptr;
}

void Food::init_main_ants_tab(){
    for(int i=0; i<game->get_nb_anthill(); i++){
        main_ant.push_back(nullptr);
    }
}

void Food::add_ant(Ant *ant){
    ant_tab[ant->get_id_colonie()].push_back(ant);
}   

Ant *Food::get_ant(int i, int id_colonie){
    return ant_tab[id_colonie][i];
}

int Food::get_nb_ants(int id_colonie){
    return ant_tab[id_colonie].size();
}

void Food::reset_opponent(Ant *ant){
    for(int i=0; i<game->get_nb_anthill(); i++){
        if(i != ant->get_id_colonie()){
            unsigned int size = ant_tab[i].size();
            for(unsigned int j=0; j<size; j++){
                if(ant_tab[i][j]->get_opponent() == ant){
                    ant_tab[i][j]->reset_opponent();
                }
            }
        }
    }
}