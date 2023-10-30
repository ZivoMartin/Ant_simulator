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
        food_transported->set_pos({position.x+current_dir.x-30, position.y+current_dir.y - 30});
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
  
    if(food_state == 0){
        Food *nearest_spot = get_nearest_spot(); 
        if(get_dist(nearest_spot->get_pos(), position)<game->range_ant*game->range_ant){
            go_on_this_point(nearest_spot->get_pos());
            current_food = nearest_spot;
            food_state = 1;
        }else{
            Pheromone *nearest_pheromone = get_nearest_pheromone();
            if(nearest_pheromone != nullptr && get_dist(nearest_pheromone->get_pos(), position)<game->range_ant*game->range_ant){
                go_on_this_point(nearest_pheromone->get_pos());
                food_state = 1; 
            }else if(random_count == 0){
                get_new_random_dir();
                random_count = 150;
            }else{
                random_count -= 1;
            }   
        }
        
    }else if(food_state == 1 || food_state == 3){
        if(game->get_iter() % 7 == 0){
            go_on_this_point(target_pos);
        }
        if(game->get_iter() % 80 == 0 && food_state == 3 && authorised_to_place_pheromone){
            current_food->add_pheromone(position);
        }
        if(game->get_iter() % 10 == 0 && food_state == 3 && authorised_to_place_pheromone){
            current_food->add_fake_pheromone(position);
        }
        int s = 40;
        if(target_pos.x-s <= position.x && target_pos.x+s >= position.x && target_pos.y-s <= position.y && target_pos.y+s >= position.y){
            if(food_state == 3){
                delete food_transported;
                authorised_to_place_pheromone = false;
            }
            if(current_food == nullptr){
                current_food = affiliate_food;
                target_pos = affiliate_food->get_pos();
            }else{
                food_state += 1;
            }
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
            go_on_this_point(target_pos);
            food_transported = new Food(position, game, game->piece_food_size);
            if(!current_food->get_phero_path_bool()){
                authorised_to_place_pheromone = true;
                current_food->path_created();
            }
        }
    }else if(food_state == 4){
        state_count -= 1;
        if(state_count == 0){
            game->add_ant();
            reset_state();
        }
    }
    set_pos({current_dir.x + position.x, current_dir.y + position.y});
    
}

Pheromone *Ant::get_nearest_pheromone(){
    int size = game->get_nb_food_spot();
    int min = -1;
    int i_spot = -1;
    int i_pheromone = -1;
    for(int i=0; i<size; i++){
        Food *the_food = game->get_food(i);
        if(the_food->get_phero_path_bool()){
            int size2 = the_food->get_nb_phero(); 
            for(int j=0; j<size2; j++){
                if(min == -1){
                    min = get_dist(position, the_food->get_pheromone(j)->get_pos());
                    i_spot = i;
                    i_pheromone = j;
                }else{
                    int d = get_dist(position, the_food->get_pheromone(j)->get_pos());
                    if(d<min){
                        min = d;
                        i_spot = i;
                        i_pheromone = j;
                    }
                }
            }    
        }
        
    }
    if(min == -1){
        return nullptr;
    }else{
        affiliate_food = game->get_food(i_spot);
        return game->get_food(i_spot)->get_pheromone(i_pheromone);
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

Food *Ant::get_current_food(){
    return current_food;
}

Food *Ant::get_affiliate_food(){
    return affiliate_food;
}

int Ant::get_food_state(){
    return food_state;
}

void Ant::reset_state(){
    current_food = nullptr;
    affiliate_food = nullptr;
    food_transported = nullptr;
    food_state = 0;
    state_count = game->time_to_recup;
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