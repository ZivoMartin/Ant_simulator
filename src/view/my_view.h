#ifndef my_view_safe
#define my_view_safe
#include <QGraphicsView>
#include <QGraphicsScene>
#include <iostream>
#include <QKeyEvent>
#include <QColor>
#include <QBrush>


class Game;

class My_view : public QGraphicsView{
    
public:
    My_view();
    ~My_view();
    QGraphicsScene * get_scene();
    void keyPressEvent(QKeyEvent* event) override;
    void set_game(Game *game);
    void set_bg_color(QColor *color);
    void zoom(double factor);
    
private:
    QGraphicsScene *scene;
    Game *game;
};

#endif