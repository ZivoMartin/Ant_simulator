#include "my_view.h"
#include "../game.h"

My_view::My_view() : QGraphicsView(){
    this->scene = new QGraphicsScene();
    setScene(scene);
}

My_view::~My_view(){
    delete scene;
}

QGraphicsScene * My_view::get_scene(){
    return scene;
}

void My_view::keyPressEvent(QKeyEvent* event){
    int key = event->key();
    if(game->get_iter() != 0){
        if(key == Qt::Key_A) {
            game->change_view_state();
        }else if(key == Qt::Key_Up){
            zoom(1.2);
        }else if(key == Qt::Key_Down){
            zoom(0.8);
        }
    }else if(game->get_config_mode()){
        if(key == Qt::Key_Return){
            game->start_the_custom_simulation();
        }else if(key == Qt::Key_A){
            game->delete_selected_food();
        }
    }
}


void My_view::mousePressEvent(QMouseEvent* event){
    if(game->get_config_mode() && event->type() == QEvent::MouseButtonPress){
        coord coord_clic = convert(mapToScene(event->pos()));
        if(event->button() == 1){
            game->config_left_click(coord_clic);
        }else if(event->button() == 2){
            game->draw_anthill(coord_clic);
        }
    }
}

void My_view::set_game(Game *game){
    this->game = game;
}


void My_view::set_bg_color(QColor *color){
    QBrush brush(*color);
    scene->setBackgroundBrush(brush);
}

void My_view::set_bg_img(QString path){
    QImage img(path);
    img = img.scaled(game->get_screen_size()->width, game->get_screen_size()->height, Qt::IgnoreAspectRatio);
    setBackgroundBrush(img);
}

void My_view::zoom(double factor){
    setTransform(transform().scale(1.0/factor, 1.0/factor));
}

coord My_view::convert(QPointF coord_clic){
    return {static_cast<int>(coord_clic.rx()*factor_x), static_cast<int>(coord_clic.ry()*factor_y)};
}

void My_view::set_size(dim s){
    size = s;
    scene->setSceneRect(0, 0, s.width, s.height);
}

int My_view::get_factor_x(){
    return factor_x;
}

int My_view::get_factor_y(){
    return factor_y;
}

dim *My_view::get_size(){
    return &size;
}