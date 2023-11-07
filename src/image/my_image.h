#ifndef my_image_safe
#define my_image_safe
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsScene>
#include "../struct/coord.h"
#include <cmath>



class My_image : QGraphicsPixmapItem{

public:
    My_image(QPixmap *image, QGraphicsScene *scene, coord xy);
    ~My_image();
    void set_pos_img(coord xy);
    void rotate(int angle);

private:
    QGraphicsScene *scene;
};

#endif