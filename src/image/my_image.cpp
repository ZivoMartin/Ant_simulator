#include "my_image.h"

My_image::My_image(QPixmap *image, QGraphicsScene *scene, coord xy) : QGraphicsPixmapItem(*image){
    set_pos_img(xy);
    this->position = xy;
    scene->addItem(this);
    this->scene = scene;
}

My_image::~My_image(){
    scene->removeItem(this);
}

void My_image::set_pos_img(coord xy){
    position = xy;
    this->setPos(xy.x, xy.y);
}

void My_image::rotate(int angle){
    this->setRotation(angle);
}

coord *My_image::get_pos(){
    return &position;
}
