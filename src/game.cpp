#include "game.h"


int random(int min, int max){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> random_nbr(min, max);
    return(random_nbr(generator));
}


Game::Game(My_view *view): QMainWindow(){
    this->view = view;
    this->anthill_coord = {map_width/2, map_height/2};
    setFocusPolicy(Qt::StrongFocus);
    setup_scene();
    build_image();
    build_brush();
    anthill = new Anthill(this, anthill_coord);
    init_ant_tab();
    init_food_spots();
    start();
}

Game::~Game(){
    int size = ant_tab.size();
    for(int i=0; i<size; i++){
        delete ant_tab[i];
    }
    size = food_tab.size();
    for(int i=0; i<size; i++){
        delete food_tab[i];
    }
    delete anthill;
    delete food_brush;
    delete pheromone_brush;
    delete background_color;
    delete pheromone_background;
}




void Game::setup_scene(){
    this->background_color = new QColor(210, 180, 140);
    this->pheromone_background = new QColor(20, 20, 20);
    view->set_bg_color(background_color);
    QPointF centerPoint(anthill_coord.x-1500, anthill_coord.y-900);
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
    ant_img.load("../images/ant.png");
    ant_img = ant_img.scaled(70, 70);
    anthill_img.load("../images/anthill.png");
    anthill_img = anthill_img.scaled(200, 200);
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
    QColor color2(214, 107, 91);
    this->pheromone_brush = new QBrush(color2);
} 

void Game::init_ant_tab(){
    for(int i=0; i<nb_start_ant; i++){
        add_ant();
    }
}

void Game::init_food_spots(){
    for(int i=0; i<nb_start_food_spot; i++){
        int x = random(0, map_width);
        int y = random(0, map_height);
        while(x>anthill_coord.x-range_ant && x<anthill_coord.x+range_ant && y>anthill_coord.y-range_ant && y<anthill_coord.y+range_ant){
            x = random(0, map_width);
            y = random(0, map_height);
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

void Game::add_ant(){
    ant_tab.push_back(new Ant(this, anthill_coord));
}


void Game::start(){
    QTimer::singleShot(20, this, [=](){
        move_ants();
        view->update();
        iter += 1;
        start();
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
        if((ant_tab[i]->get_food_state() == 1 || ant_tab[i]->get_food_state() == 2) && (ant_tab[i]->get_current_food() == deleted_food || ant_tab[i]->get_current_food() == deleted_food)){
            ant_tab[i]->reset_state();
        }
    }
}

void Game::change_view_state(){
    if(view_state == 0){
        view_state = 1;
        unsigned int nb_food_spot = food_tab.size();
        for(unsigned int i=0; i<nb_food_spot; i++){
            unsigned int size = food_tab[i]->get_nb_fake_phero();
            for(unsigned int j=0; j<size; j++){
                food_tab[i]->get_fake_pheromone(j)->display();
            }
        }  
        view->set_bg_color(pheromone_background);
    }else{
        view_state = 0;
        unsigned int nb_food_spot = food_tab.size();
        for(unsigned int i=0; i<nb_food_spot; i++){
            unsigned int size = food_tab[i]->get_nb_fake_phero();
            for(unsigned int j=0; j<size; j++){
                food_tab[i]->get_fake_pheromone(j)->remove();
            }
        }
        view->set_bg_color(background_color);
    }
}


coord Game::get_anthill_coord(){
    return anthill_coord;
}

int Game::get_iter(){
    return iter;
}

int Game::get_view_state(){
    return view_state;
}

int get_dist(coord xy1, coord xy2){
    return (xy1.x-xy2.x)*(xy1.x-xy2.x) + (xy1.y-xy2.y)*(xy1.y-xy2.y);
}
