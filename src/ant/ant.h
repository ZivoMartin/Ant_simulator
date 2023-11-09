#ifndef safe_ant
#define safe_ant
#include "../image/my_image.h"
#include "../food/food.h"
#include "anthill.h"

class Game;


class Ant : public My_image{

public:
    Ant(Game* game, int id_colonie);
    ~Ant();

    void move();
    Ant *nearest_ant();
    Pheromone *get_nearest_pheromone();
    void rotate_to_goal();
    int go_on_this_point(coord *xy);
    bool take_damage(int damage);

    void reset_state();
    void reset_opponent();
    void change_authorisation();
    void set_pos(coord xy);


    int get_id_colonie();
    int get_food_state();
    Food *get_nearest_spot();
    Food *get_current_food();
    Food *get_affiliate_food();
    void get_new_random_dir();
    // coord *get_pos() override;
    Ant *get_opponent();

private:
    int random_count = 0;
    coord current_dir = {0, 0};
    int speed = 5;
    coord position = {0, 0};
    Game *game;
    Anthill *anthill;
    coord *target_pos = nullptr;
    int goal_angle = 0;
    int current_angle = 0;
    int pas_angle = 4;
    int food_state = 0;
    int state_count;
    Food *current_food = nullptr;
    Circle *food_transported = nullptr;
    Food *affiliate_food = nullptr;
    bool authorised_to_place_pheromone = false;
    int id_colonie;
    bool in_fight_zone = false;
    int hp;
    Ant *opponent = nullptr;
};

int get_angle(float o, float a);
int get_angle_value(int angle);
int get_dist(coord xy1, coord xy2);
#endif 