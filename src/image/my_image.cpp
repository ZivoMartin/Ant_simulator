#include "my_image.h"

My_image::My_image(QPixmap image, QGraphicsScene *scene, coord xy) : QGraphicsPixmapItem(image){
    set_pos_img(xy);
    scene->addItem(this);
}

My_image::~My_image(){}

void My_image::set_pos_img(coord xy){
    this->setPos(xy.x, xy.y);
}

void My_image::rotate(int angle){
    this->setRotation(angle);
}