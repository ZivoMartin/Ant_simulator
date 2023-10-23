#ifndef safe_ant
#define safe_ant
#include "../image/my_image.h"
#include "../struct/coord.h"
#include <cmath>

class Game;
int get_dist(coord xy1, coord xy2);

class Ant : public My_image{

public:
    Ant(Game* game, coord xy);
    ~Ant();
    void set_pos(coord xy);
    void move();
    void get_new_random_dir();
private:
    int random_count = 0;
    coord current_dir = {0, 0};
    int speed = 5;
    coord position = {0, 0};
};

int random(int min, int max);
int get_angle(int h, int a);
#endif 