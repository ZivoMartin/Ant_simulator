#ifndef cercles_safe
#define cercles_safe

#include <QGraphicsEllipseItem>
#include <QColor>
#include <QBrush>
#include <iostream>
#include <QGraphicsScene>
#include "../struct/coord.h"
#include "../struct/coord.h"

class Circle : public QGraphicsEllipseItem{

public:
    Circle(QColor color, QGraphicsScene *scene, int size, coord xy);
    ~Circle();
    virtual void display();
    virtual void remove();
    virtual coord *get_pos();
    virtual int get_size();

protected:
    QColor color;
    QGraphicsScene *scene;

private:
    int size;
    coord position;
};



#endif