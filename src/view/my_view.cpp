#include "my_view.h"

My_view::My_view() : QGraphicsView(), scene(new QGraphicsScene){
    setScene(scene);
}

My_view::~My_view(){
    delete scene;
}

QGraphicsScene * My_view::get_scene(){
    return scene;
}