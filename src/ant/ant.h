#ifndef safe_ant
#define safe_ant
#include "../image/my_image.h"
#include "../food/food.h"

class Game;


class Ant : public My_image{

public:
    Ant(Game* game, coord xy);
    ~Ant();
    void set_pos(coord xy);
    void move();
    void get_new_random_dir();
    void rotate_to_goal();
    void go_on_this_point(coord xy);
    Food *get_nearest_spot();

private:
    int random_count = 0;
    coord current_dir = {0, 0};
    int speed = 5;
    coord position = {0, 0};
    Game *game;
    coord target_pos = {0, 0};
    int goal_angle = 0;
    int current_angle = 0;
    int pas_angle = 4;
    int food_state = 0;
    int state_count;
    Food *current_food;
};

int get_angle(float o, float a);
int get_angle_value(int angle);
int get_dist(coord xy1, coord xy2);
#endif 