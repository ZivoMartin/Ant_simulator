#ifndef my_view_safe
#define my_view_safe
#include <QGraphicsView>
#include <QGraphicsScene>
#include <iostream>

class My_view : public QGraphicsView{
    
public:
    My_view();
    ~My_view();
    QGraphicsScene * get_scene();
    
private:
    QGraphicsScene *scene;

};

#endif