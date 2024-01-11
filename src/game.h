#ifndef safe_game
#define safe_game

#include <QMainWindow>
#include <random>
#include <QTimer>
#include <QScreen>
#include <QPointF>
#include <QApplication>
#include "view/my_view.h"
#include "image/my_image.h"
#include "ant/ant.h"
#include "ant/anthill.h"
#include "food/food.h"
#include "buttons/menu_button.h"
#include "struct/size.h"

class Menu_Button;

class Game : public QMainWindow{

public: 
    Game(My_view *view);
    ~Game();
    void build_image();
    void build_brush();
    void init_anthill_tab();
    void init_ant_tab();
    void init_food_spots();
    void move_ants();
    void start_random_simulation();
    void play();
    void delete_ant(int i);
    int get_iter();
    void setup_scene();
    int get_nb_food_spot();
    void add_ant(int i);
    void delete_food_spot(Food *food_spot, int i);
    int get_view_state();
    void actualise_ant_state(Food *deleted_food);
    void change_view_state();
    bool is_valid_coord(coord *xy);
    void build_colors();
    int get_nb_ant();
    QPixmap *get_ant_image(int i);
    QColor *get_color(int i);
    Anthill *get_anthill(int i);
    Food *get_food(unsigned int i);
    QColor get_food_color();
    My_view *get_view();
    void delete_ant(Ant *ant);
    Ant *get_ant(int i);
    void display_menu();
    void remove_ant(int i);
    dim *get_screen_size();
    int get_nb_anthill();
    void start_config();
    void switch_state();
    bool get_config_mode();
    void start_the_custom_simulation();
    void config_right_click(coord xy);
    void erase_anthill(My_image *anthill);
    void config_left_click(coord xy);
    void erase_food(Circle *anthill);
    void delete_selected_food();
    void increase_selected_food();
    void decrease_selected_food();
    QPixmap *anthill_img;

    static const int map_height = 15000;
    static const int map_width = 15000;
    static const int size_food = 100;
    static const int piece_food_size = 20;
    static const int range_ant = 1000;
    static const int ant_speed = 5;
    static const int time_to_recup = 70;
    static const int time_to_drop = 20;
    static const int pheromone_size = 50;
    static const int phero_img_size = 70;
    static const int range_to_join_fight = 450;
    static const int ant_base_hp = 120;
    static const int ant_damage = 1;
    static const int increase_of_size = 10;
    static const int nb_start_ant = 10; 
    static const int anthill_size = 200;
    static const int ant_size = 70;

private:
    My_view *view;

    std::vector<Ant*> ant_tab;
    std::vector<Food*> food_tab;
    std::vector<Anthill*>anthill_tab;
    std::vector<QPixmap*>ant_images_tab;
    std::vector<QColor*>pheromone_color_tab;
    std::vector<int>nb_ant_tab; 

    std::vector<Circle*> draw_food_tab;
    std::vector<My_image*> draw_anthill_tab;

    unsigned int iter = 0;
    int view_state = 0;
    QColor *background_color;
    QColor *pheromone_background;
    QColor *food_color;
 
    Menu_Button *start_random_simulation_button;
    Menu_Button *start_configured_simulation;

    Size_Button *test_button;

    QScreen *screen;
    dim screen_size;

    int nb_different_colors = 6;
    int nb_anthill = 3;
    int nb_start_food_spot = 30; 
    bool config_mode = false;

    Circle *selected_food = nullptr;
};

int random(int min, int max);
int get_dist(coord *xy1, coord *xy2);

#endif
