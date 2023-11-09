#ifndef cercles_safe
#define cercles_safe

#include <QGraphicsEllipseItem>
#include <QColor>
#include <QBrush>
#include <iostream>
#include <QObject>
#include <QGraphicsScene>
#include <iostream>

#include "../struct/coord.h"
#include "../struct/coord.h"

class Size_Button;

class Circle : public QGraphicsEllipseItem{

public:
    Circle(QColor color, QGraphicsScene *scene, int size, coord xy);
    ~Circle();
    virtual void display();
    virtual void remove();
    virtual coord *get_pos();
    virtual int get_size();
    virtual void set_pos(coord xy);
    void up_light();
    void off_light();

protected:
    QBrush *default_brush;
    QBrush *light_brush;
    QGraphicsScene *scene;

private:
    int size;
    coord position;
    coord origin;
};



#endif