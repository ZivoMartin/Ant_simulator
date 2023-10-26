#include "ant.h"
#include "../game.h"

Ant::Ant(Game *game, coord xy) : My_image(game->ant_img, game->get_view()->get_scene(), xy){
    position = xy;
    this->game = game;
    state_count = game->time_to_recup;
}   

Ant::~Ant(){}


void Ant::set_pos(coord xy){
    goal_angle = get_angle(abs(position.x-xy.x), abs(position.y-xy.y));
    if(xy.y > position.y){
        goal_angle = 180-goal_angle;
    }if(xy.x < position.x){
        goal_angle = 360-goal_angle;
    }
    if(current_angle != goal_angle){
        rotate_to_goal();
    }
    position.x = xy.x;
    position.y = xy.y;
    set_pos_img(position);
    if(food_state == 3){
        current_food->set_pos({position.x+current_dir.x-30, position.y+current_dir.y - 30});
    }
}

void Ant::rotate_to_goal(){
    if(abs(current_angle-goal_angle) < pas_angle){
        current_angle = goal_angle;
    }else{
        if(current_angle > goal_angle){
            if(current_angle-goal_angle < 360-current_angle + goal_angle){
                current_angle = get_angle_value(current_angle - pas_angle);  
            }else{
                current_angle = get_angle_value(current_angle + pas_angle);
            }

        }else{
            if(goal_angle-current_angle < 360-goal_angle + current_angle){
                current_angle = get_angle_value(current_angle + pas_angle);  
            }else{
                current_angle = get_angle_value(current_angle - pas_angle);
            }
        }
    }
    rotate(current_angle);
}

void Ant::move(){
    if((food_state == 3 || food_state == 1 || food_state == 2) && current_food == nullptr){
        food_state = 0;
    }else{
        if(food_state == 0){
            Food *nearest_spot = get_nearest_spot(); 
            if(get_dist(nearest_spot->get_pos(), position)<game->range_ant*game->range_ant){
                go_on_this_point(nearest_spot->get_pos());
                current_food = nearest_spot;
                food_state = 1;
            }else if(random_count == 0){
                get_new_random_dir();
                random_count = 150;
            }else{
                random_count -= 1;
            }
        }else if(food_state == 1 || food_state == 3){
            go_on_this_point(target_pos);
            int s = 20;
            if(target_pos.x-s <= position.x && target_pos.x+s >= position.x && target_pos.y-s <= position.y && target_pos.y+s >= position.y){
                if(food_state == 3){
                    delete current_food;
                }
                food_state += 1;
                current_dir.x = 0;
                current_dir.y = 0;
            }
        }else if(food_state == 2){
            state_count -= 1;
            if(state_count == 0){
                food_state = 3;
                state_count = game->time_to_drop;
                target_pos = game->get_anthill_coord();
                if(current_food->decrease_nb_food_remain()){
                    game->delete_food_spot(current_food, -1);
                }
                current_food = new Food(position, game, game->piece_food_size);
            }
        }else if(food_state == 4){
            state_count -= 1;
            if(state_count == 0){
                state_count = game->time_to_recup;
                food_state = 0;
                game->add_ant();
            }
        }
        set_pos({current_dir.x + position.x, current_dir.y + position.y});
    }
   
}

Food *Ant::get_nearest_spot(){
    int size = game->get_nb_food_spot();
    int min = get_dist(position, game->get_food(0)->get_pos());
    int result = 0;
    for(int i=1; i<size; i++){
        int d = get_dist(position, game->get_food(i)->get_pos());
        if(d<min){
            min = d;
            result = i;
        }
    }
    return game->get_food(result);
}



void Ant::get_new_random_dir(){
    current_dir.x = random(-game->ant_speed, game->ant_speed);
    current_dir.y = game->ant_speed - abs(current_dir.x);
    if(random(1, 2) == 1){
        current_dir.y *= -1;
    }
}

int abs(int x){
    if(x < 0){
        return -x;
    }
    return x;
}

int get_angle(float o, float a){
    if(a == 0){
        return 90; 
    }
    double tmp = o/a;
    return std::atan(tmp) * (180.0 / M_PI);
}

int get_angle_value(int angle){
    while(angle < 0){
        angle += 360;
    }
    while(angle > 360){
        angle -= 360;
    }
    return angle;
}

void Ant::go_on_this_point(coord xy){
    float x1 = position.x;
    float y1 = position.y;
    if(position.x == xy.x){
        return;
    }
    target_pos.x = xy.x;
    target_pos.y = xy.y;
    float m = (y1-xy.y)/(x1-xy.x);
    float factor = 1;
    if(position.x>xy.x){
        m = (xy.y-y1)/(xy.x-x1);
        factor = -1;
    }
    float d = std::sqrt(get_dist(position, xy)) - game->ant_speed;
    float b = y1 - m*x1;
    float new_dir_x = x1 - (xy.x - factor*(d/std::sqrt(m*m + 1)));
    current_dir.x = -1*new_dir_x;
    float new_dir_y = y1 - ((x1+new_dir_x)*m + b);
    current_dir.y = new_dir_y;
}


// m = (y1-y2)/(x1-x2)
// factor = 1
// if(x1>x2):
//     m = (y2-y1)/(x2-x1)
//     factor = -1
// dist = math.sqrt((x1-x2)**2 + (y1-y2)**2)
// b = y1 - m*x1
// return m, dist, b, factor
// self.x = self.click_x - int(self.f*(self.d/math.sqrt(self.m**2 + 1)))
// self.y = int(self.x*self.m + self.b)
