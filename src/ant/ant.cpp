#include "ant.h"
#include "../game.h"

Ant::Ant(Game *game, int id_colonie) : My_image(game->get_ant_image(id_colonie), game->get_view()->get_scene(), *(game->get_anthill(id_colonie)->get_pos())){
    this->id_colonie = id_colonie;
    this->anthill = game->get_anthill(id_colonie);
    this->hp = game->ant_base_hp;
    position = *(anthill->get_pos());
    this->game = game;
    state_count = game->time_to_recup;
}   

Ant::~Ant(){
    unsigned int nb_ant = game->get_nb_ant(); 
    for(unsigned int i=0; i<nb_ant; i++){
        if(game->get_ant(i) == this){
            game->remove_ant(i);
            break;
        }
    }
    if(current_food != nullptr){
        current_food->remove_ant(this);
        current_food->reset_opponent(this);
    }
    if(food_transported != nullptr){
        delete food_transported;
    }
}


void Ant::set_pos(coord xy){

    if(!game->is_valid_coord(&xy)){
        if(xy.x < 0 || xy.y > game->map_width){
            current_dir.x *= -1;
        }else{
            current_dir.y *= -1;
        }
    }else{
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
    // int ft = food_state;
    // printf("%d\n", ft);
    if(food_state == 0){
        Food *nearest_spot = get_nearest_spot(); 
        if(nearest_spot != nullptr && game->get_iter()>20 && get_dist(nearest_spot->get_pos(), &position)<nearest_spot->get_range_to_see_it()*nearest_spot->get_range_to_see_it()){
            go_on_this_point(nearest_spot->get_pos());
            target_pos = nearest_spot->get_pos();
            current_food = nearest_spot;
            food_state = 1;
        }else{
            Pheromone *nearest_pheromone = get_nearest_pheromone();
            if(nearest_pheromone != nullptr && game->get_iter()>20 && nearest_pheromone != nullptr && get_dist(nearest_pheromone->get_pos(), &position)<game->range_ant*game->range_ant){
                go_on_this_point(nearest_pheromone->get_pos());
                target_pos = nearest_pheromone->get_pos();
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
            int d = go_on_this_point(target_pos);
            if(current_food != nullptr && !in_fight_zone && d<current_food->get_range_to_join_fight() && food_state == 1){
                current_food->add_ant(this);
                in_fight_zone = true;
            }
            if(in_fight_zone && opponent == nullptr){
                opponent = nearest_ant();
                if(opponent !=nullptr){
                    target_pos = opponent->get_pos();
                }
            }
        }
        if(game->get_iter() % 80 == 0 && food_state == 3 && authorised_to_place_pheromone){
            current_food->add_pheromone(position, id_colonie);
        }
        if(game->get_iter() % 10 == 0 && food_state == 3 && authorised_to_place_pheromone){
            current_food->add_fake_pheromone(position, id_colonie);
        }
        int s1;
        int s2;
        if(opponent != nullptr){
            s1 = 0;
            //s1 = s2 = game->ant_size;
            s1 = s2 = 10;
        }else if(target_pos == anthill->get_pos()){
            s1 = 0;
            s1 = s2 = 10;
            // s1 = s2 = game->anthill_size;
        }else if(current_food != nullptr){
            s1 = s2 = current_food->get_size()/2;            
        }else{
            s1 = s2 = game->pheromone_size/2;
        }
        if(target_pos->x+s2 >= position.x && target_pos->x-s1 <= position.x && target_pos->y+s2 >= position.y && target_pos->y-s1 <= position.y){
            if(food_state == 3){
                delete food_transported;
                food_transported = nullptr;
                if(authorised_to_place_pheromone){
                    current_food->delete_main_ant(id_colonie);
                    authorised_to_place_pheromone = false;
                }
                food_state = 4;
            }else if(opponent != nullptr){
                if(opponent->take_damage(game->ant_damage)){
                    opponent = nullptr;
                    target_pos = current_food->get_pos();
                }
            }else if(current_food == nullptr && food_state == 1){
                current_food = affiliate_food;
                affiliate_food = nullptr;
                target_pos = current_food->get_pos();
            }else{
                food_state = 2;
            }
            current_dir.x = 0;
            current_dir.y = 0;
       }
    }else if(food_state == 2){
        state_count -= 1;
        if(state_count == 0){
            current_food->remove_ant(this);
            in_fight_zone = false;
            food_state = 3;
            state_count = game->time_to_drop;
            target_pos = anthill->get_pos();
            food_transported = new Circle(game->get_food_color(), game->get_view()->get_scene(), game->piece_food_size, position);
            if(!current_food->get_phero_path_bool(id_colonie)){
                authorised_to_place_pheromone = true;
                current_food->path_created(this);
            }
            if(current_food->decrease_nb_food_remain()){
                game->delete_food_spot(current_food, -1);
            }
        }
    }else if(food_state == 4){
        state_count -= 1;
        if(state_count == 0){
            game->add_ant(id_colonie);
            reset_state();
        }
    }
    if(current_dir.x != 0 || current_dir.y != 0){
        set_pos({current_dir.x + position.x, current_dir.y + position.y});
    }
    // printf("%d\n\n", ft);
}

void Ant::change_authorisation(){
    if(authorised_to_place_pheromone){
        authorised_to_place_pheromone = false;
    }else{
        authorised_to_place_pheromone = true;
    }
}

Ant *Ant::get_opponent(){
    return opponent;
}

void Ant::reset_opponent(){
    opponent = nullptr;
    if(current_food != nullptr){
        target_pos = current_food->get_pos();
    }
}

Pheromone *Ant::get_nearest_pheromone(){
    if(game->get_nb_food_spot() == 0) return nullptr;
    int min = -1;
    int i_spot = -1;
    int i_pheromone = -1;
    for(int i=0; i<game->get_nb_food_spot(); i++){
        Food *the_food = game->get_food(i);
        if(the_food->get_phero_path_bool(id_colonie)){
            int size2 = the_food->get_nb_phero(id_colonie); 
            for(int j=0; j<size2; j++){
                if(min == -1){
                    min = get_dist(&position, the_food->get_pheromone(j, id_colonie)->get_pos());
                    i_spot = i;
                    i_pheromone = j;
                }else{
                    int d = get_dist(&position, the_food->get_pheromone(j, id_colonie)->get_pos());
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
        return game->get_food(i_spot)->get_pheromone(i_pheromone, id_colonie);
    }
}

bool Ant::take_damage(int damage){
    hp -= damage;
    if(hp <= 0){
        delete this;
    }
    return hp<=0;
}

Food *Ant::get_nearest_spot(){
    int size = game->get_nb_food_spot();
    if(size == 0) return nullptr;
    int min = get_dist(&position, game->get_food(0)->get_pos());
    int result = 0;
    for(int i=1; i<size; i++){
        int d = get_dist(&position, game->get_food(i)->get_pos());
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
    target_pos = nullptr;
    affiliate_food = nullptr;
    food_transported = nullptr;
    opponent = nullptr;
    authorised_to_place_pheromone = false;
    food_state = 0;
    hp = game->ant_base_hp;
    state_count = game->time_to_recup;
    in_fight_zone = false;
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

Ant *Ant::nearest_ant(){
    Ant *result = nullptr;
    int min = -1;
    for(int i=0; i<game->get_nb_anthill(); i++){
        if(i != id_colonie){
            int size = current_food->get_nb_ants(i);
            for(int j=0; j<size; j++){
                int d = get_dist(&position, current_food->get_ant(j, i)->get_pos()); 
                if(d<min || min == -1){
                    min = d;
                    result = current_food->get_ant(j, i);
                }
            }
        }
    }
    return result;
}

int Ant::get_id_colonie(){
    return id_colonie;
}

int Ant::go_on_this_point(coord *xy){
    float x1 = position.x;
    float y1 = position.y;
    float d = std::sqrt(get_dist(&position, xy)) - game->ant_speed;
    if(position.x != xy->x){
        float m = (y1-xy->y)/(x1-xy->x);
        float factor = 1;
        if(position.x>xy->x){
            m = (xy->y-y1)/(xy->x-x1);
            factor = -1;
        }
        float b = y1 - m*x1;
        float new_dir_x = x1 - (xy->x - factor*(d/std::sqrt(m*m + 1)));
        current_dir.x = -1*new_dir_x;
        float new_dir_y = y1 - ((x1+new_dir_x)*m + b);
        current_dir.y = new_dir_y;
    }
    return d;
}

// coord *Ant::get_pos(){
//     return &position;
// } 