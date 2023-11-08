#include "cercles.h"

Circle::Circle(QColor color, QGraphicsScene *scene, int size, coord xy) : QGraphicsEllipseItem(xy.x, xy.y, size, size){
    this->scene = scene;
    this->color = color; 
    scene->addItem(this);
    QBrush brush(color);
    this->setBrush(brush);
}

Circle::~Circle(){
    scene->removeItem(this);
}

void Circle::display(){
    scene->addItem(this);
}

void Circle::remove(){
    scene->removeItem(this);
}