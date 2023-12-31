#ifndef safe_food
#define safe_food

#include "pheromone.h"

class Game;
class Ant;

class Food : public Circle{

public:
    Food(coord xy, Game *game, int h);
    ~Food();
    bool decrease_nb_food_remain();
    coord *get_pos() override;
    void add_pheromone(coord xy, int id_colonie);
    void add_fake_pheromone(coord xy, int id_colonie);
    void set_main_ant(Ant *ant);
    bool get_phero_path_bool(int id_colonie);
    void path_created(Ant *ant);
    int get_nb_phero(int id_colonie);
    Pheromone *get_pheromone(int i, int id_colonie);
    int get_nb_fake_phero(int id_colonie);
    Pheromone *get_fake_pheromone(int i, int id_colonie);
    void delete_main_ant(int id_colonie);
    void init_main_ants_tab();
    void add_ant(Ant *ant);
    Ant *get_ant(int i, int id_colonie);
    void remove_ant(Ant *ant);
    int get_nb_ants(int id_colonie);
    void reset_opponent(Ant *ant);
    int get_range_to_see_it();
    int get_range_to_join_fight();

private:
    Game *game;
    int nb_food_remain = 30;
    int size;
    int range_to_see_it;
    int range_to_join_fight;
    coord position;
    coord origin;
    bool already_have_phero_path = false;
    std::vector<std::vector<Pheromone*>> phero_tab;
    std::vector<std::vector<Pheromone*>> fake_phero_tab; 
    std::vector<std::vector<Ant*>> ant_tab; 
    std::vector<Ant *>main_ant;
};

#endif