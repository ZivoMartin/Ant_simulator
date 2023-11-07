#include "game.h"


int random(int min, int max){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> random_nbr(min, max);
    return(random_nbr(generator));
}


Game::Game(My_view *view): QMainWindow(){
    screen = QGuiApplication::primaryScreen();
    this->screen_size = {screen->geometry().width(), screen->geometry().height()};
    this->view = view;
    view->set_game(this);
    setFocusPolicy(Qt::StrongFocus);
    build_image();
    build_colors();
    build_brush();
    display_menu();
}

Game::~Game(){
    if(iter != 0){
        unsigned int i = ant_tab.size();
        while(i != 0){
            i -= 1;
            delete ant_tab[i];
        }
        int size = food_tab.size();
        for(int i=0; i<size; i++){
            delete food_tab[i];
        }
        for(int i=0; i<nb_anthill; i++){
            delete anthill_tab[i];
            delete pheromone_color_tab[i];
            delete ant_images_tab[i];
        }
        delete food_brush;
        delete background_color;
        delete pheromone_background;
    }else if(!config_mode){
        delete start_random_simulation_button;
        delete start_configured_simulation;
    }
}




void Game::setup_scene(){
    this->background_color = new QColor(210, 180, 140);
    this->pheromone_background = new QColor(20, 20, 20);
    view->set_bg_color(background_color);
    QPointF centerPoint(map_width/2, map_height/2);
    view->centerOn(centerPoint);
    view->get_scene()->setSceneRect(0, 0, map_width, map_height);
    view->zoom(4);

}

My_view *Game::get_view(){
    return view;
}

void Game::delete_ant(int i){
    delete ant_tab[i];
}

void Game::build_image(){
    for(int i=0; i<nb_different_colors; i++){
        ant_images_tab.push_back(new QPixmap());
    }
    ant_images_tab[0]->load("../images/red_ant.png");
    ant_images_tab[1]->load("../images/green_ant.png");
    ant_images_tab[2]->load("../images/blue_ant.png");
    for(int i=0; i<nb_different_colors; i++){
        *ant_images_tab[i] = ant_images_tab[i]->scaled(70, 70);
    }
    anthill_img = new QPixmap();
    anthill_img->load("../images/anthill.png");
    *anthill_img = anthill_img->scaled(200, 200);
    
} 

dim *Game::get_screen_size(){
    return &screen_size;
}

void Game::build_colors(){
    pheromone_color_tab.push_back(new QColor(200, 0, 0));
    pheromone_color_tab.push_back(new QColor(0, 200, 50));
    pheromone_color_tab.push_back(new QColor(0, 0, 200));
} 


Food *Game::get_food(unsigned int i){
    return food_tab[i];
}

int Game::get_nb_food_spot(){
    return food_tab.size();
}

void Game::build_brush(){
    QColor color(0, 154, 23);
    this->food_brush = new QBrush(color);
} 

void Game::init_ant_tab(){
    for(int i=0; i<nb_anthill; i++){
        for(int j=0; j<nb_start_ant; j++){
            add_ant(i);
        }
    }
}

void Game::init_anthill_tab(){
    for(int i=0; i<nb_anthill; i++){
        nb_ant_tab.push_back(0);
        anthill_tab.push_back(new Anthill(this, {random(0, map_width), random(0, map_height)}));
    }
}

void Game::init_food_spots(){
    for(int i=0; i<nb_start_food_spot; i++){
        int x;
        int y;
        bool valid_food = false;
        while(!valid_food){
            valid_food = true;
            x = random(0, map_width);
            y = random(0, map_height);
            for(int j=0; j<nb_anthill; j++){
                coord *anthill_coord = anthill_tab[j]->get_pos();
                if(x>anthill_coord->x-range_ant && x<anthill_coord->x+range_ant && y>anthill_coord->y-range_ant && y<anthill_coord->y+range_ant){
                    valid_food = false;
                    break;
                }
            }
        }
        food_tab.push_back(new Food({x, y}, this, size_food));
    }
}

void Game::delete_food_spot(Food *food_spot, int i){
    if(i == -1){
        i = 0;
        while(food_spot != food_tab[i]){
            i += 1;
        }
    }
    delete food_tab[i];
    food_tab.erase(food_tab.begin() + i);
}

void Game::add_ant(int id_colonie){
    nb_ant_tab[id_colonie] += 1;
    ant_tab.push_back(new Ant(this, id_colonie));
}

void Game::display_menu(){
    //view->set_bg_img("/home/martin/Travail/Perso/Ant_simulator/images/background.png");
    start_random_simulation_button = new My_Button("Start with a random simulation.", view, {static_cast<int>(screen_size.width*0.35), static_cast<int>(screen_size.height*0.5)});
    connect(start_random_simulation_button, &My_Button::released, this, &Game::start_random_simulation);
    start_configured_simulation = new My_Button("Config a simulation.", view, {static_cast<int>(screen_size.width*0.55), static_cast<int>(screen_size.height*0.5)});
    connect(start_configured_simulation, &My_Button::released, this, &Game::start_config);
}

void Game::start_config(){
    switch_state();
    config_mode = true;
    start_the_custom_simulation_button = new My_Button("Start", view, {0, 0});
    connect(start_the_custom_simulation_button, &My_Button::released, this, &Game::start_the_custom_simulation);
}

void Game::start_the_custom_simulation(){
    // init_ant_tab();
    // play();
}

void Game::start_random_simulation(){
    switch_state();
    init_anthill_tab();
    init_ant_tab();
    init_food_spots();
    play();
}

void Game::switch_state(){
    delete start_random_simulation_button;
    delete start_configured_simulation;
    setup_scene();
}



void Game::play(){
    QTimer::singleShot(20, this, [=](){
        move_ants();
        view->update();
        iter += 1;
        play();
    });
}

void Game::move_ants(){
    unsigned int size = ant_tab.size();
    for(unsigned int i=0; i<size; i++){
        ant_tab[i]->move();
    }
}

void Game::actualise_ant_state(Food *deleted_food){
    int size = ant_tab.size();
    for(int i=0; i<size; i++){
        if((ant_tab[i]->get_food_state() == 1 || ant_tab[i]->get_food_state() == 2) && ant_tab[i]->get_current_food() == deleted_food){
            ant_tab[i]->reset_state();
        }
    }
}

void Game::change_view_state(){
    if(view_state == 0){
        view_state = 1;
        unsigned int nb_food_spot = food_tab.size();
        for(unsigned int i=0; i<nb_food_spot; i++){
            for(int id_colonie=0; id_colonie<nb_anthill; id_colonie++){
                unsigned int size = food_tab[i]->get_nb_fake_phero(id_colonie);
                for(unsigned int j=0; j<size; j++){
                    food_tab[i]->get_fake_pheromone(j, id_colonie)->display();
                }
            }
        }  
        view->set_bg_color(pheromone_background);
    }else{
        view_state = 0;
        unsigned int nb_food_spot = food_tab.size();
        for(unsigned int i=0; i<nb_food_spot; i++){
            for(int id_colonie=0; id_colonie<nb_anthill; id_colonie++){
                unsigned int size = food_tab[i]->get_nb_fake_phero(id_colonie);
                for(unsigned int j=0; j<size; j++){
                    food_tab[i]->get_fake_pheromone(j, id_colonie)->remove();
                }
            }
        }
        view->set_bg_color(background_color);
    }
}


Anthill *Game::get_anthill(int i){
    return anthill_tab[i];
}

QPixmap *Game::get_ant_image(int i){
    return ant_images_tab[i];
}

QColor *Game::get_color(int i){
    QColor *color = pheromone_color_tab[i];
    return color;
}

int Game::get_nb_ant(){
    return ant_tab.size();
}

Ant *Game::get_ant(int i){
    return ant_tab[i];
}

int Game::get_iter(){
    return iter;
}

int Game::get_view_state(){
    return view_state;
}

bool Game::is_valid_coord(coord *xy){
    return xy->x>0 && xy->x<map_width && xy->y>0 && xy->y<map_height;
}

int Game::get_nb_anthill(){
    return nb_anthill;
}


void Game::remove_ant(int i){
    int id_colonie = ant_tab[i]->get_id_colonie();
    nb_ant_tab[id_colonie] -= 1;
    ant_tab.erase(ant_tab.begin()+i);
    if(nb_ant_tab[id_colonie] <= 0){
        delete anthill_tab[id_colonie];
        anthill_tab[id_colonie] = nullptr;
    }
}

bool Game::get_config_mode(){
    return config_mode;
}

int get_dist(coord *xy1, coord *xy2){
    return (xy1->x-xy2->x)*(xy1->x-xy2->x) + (xy1->y-xy2->y)*(xy1->y-xy2->y);
}


