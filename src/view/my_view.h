#ifndef my_view_safe
#define my_view_safe
#include <QGraphicsView>
#include <QGraphicsScene>
#include <iostream>
#include <QKeyEvent>
#include <QColor>
#include <QBrush>
#include <QImage>
#include <QString>
#include <QSize>
#include <QTransform>
#include "../struct/size.h"

class Game;

class My_view : public QGraphicsView{


public:
    My_view();
    ~My_view();
    QGraphicsScene * get_scene();
    void keyPressEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void set_game(Game *game);
    void set_bg_color(QColor *color);
    void zoom(double factor);
    void set_bg_img(QString path);
    
private:
    QGraphicsScene *scene;
    Game *game;
};

#endif