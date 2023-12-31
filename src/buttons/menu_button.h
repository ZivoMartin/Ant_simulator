#ifndef safe_button
#define safe_button
#include <iostream>
#include <QString>
#include <QPushButton>
#include <QRect>
#include <QPoint>
#include <QColor>
#include <QPalette>
#include "../view/my_view.h"
#include "../struct/coord.h"
#include "../struct/rgb.h"


class Menu_Button : public QPushButton{

public:
    Menu_Button(QString txt, My_view *view, coord xy);
    ~Menu_Button();
    void set_color(rgb *color);

private:
    My_view *view;
    coord position;
    QPalette *palette;
    QColor *color;
};

#endif