#include "cercles.h"
#include "../buttons/size_button.h"

Circle::Circle(QColor color, QGraphicsScene *scene, int size, coord xy) : QGraphicsEllipseItem(xy.x, xy.y, size, size){
    this->scene = scene;
    this->default_brush = new QBrush(color);
    QColor light_color(240, 178, 40);
    this->light_brush = new QBrush(light_color);
    this->size = size;
    this->position = xy;
    this->origin = xy; 
    scene->addItem(this);
    this->setBrush(*default_brush);
}

Circle::~Circle(){
    scene->removeItem(this);
    delete default_brush;
}

void Circle::display(){
    scene->addItem(this);
}

void Circle::remove(){
    scene->removeItem(this);
}

coord *Circle::get_pos(){
    return &position;
}

void Circle::set_pos(coord xy){
    setPos(xy.x-origin.x, xy.y - origin.y);
    position = xy;
}

int Circle::get_size(){
    return size;
}


void Circle::up_light(){
    this->setBrush(*light_brush);
}

void Circle::off_light(){
    this->setBrush(*default_brush);
}