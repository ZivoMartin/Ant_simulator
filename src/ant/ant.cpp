#include "ant.h"
#include "../game.h"

Ant::Ant(Game *game, coord xy) : My_image(game->ant_img, game->get_view()->get_scene(), xy){
    position = xy;
}   

Ant::~Ant(){}


void Ant::set_pos(coord xy){
    rotate(get_angle(get_dist(xy, position), abs(position.x-xy.x)));
    position = xy;
    set_pos_img(xy);
}

void Ant::move(){
    if(random_count == 0){
        get_new_random_dir();
        random_count = 20;
    }else{
        random_count -= 1;
    }
    set_pos({current_dir.x + position.x, current_dir.y + position.y});
}

void Ant::get_new_random_dir(){
    current_dir.x = random(-speed, speed);
    current_dir.y = random(-speed+abs(current_dir.x), speed-abs(current_dir.x));
}

int abs(int x){
    if(x < 0){
        return -x;
    }
    return x;
}

int get_angle(int h, int a){
    double tmp = a/h;
    return std::acos(tmp);
}