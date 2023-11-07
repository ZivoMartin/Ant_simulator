#include "my_button.h"

My_Button::My_Button(QString txt, My_view *view, coord xy) : QPushButton(txt, view){
    this->position = xy;
    this->view = view;
    this->color = new QColor(100, 200, 100);
    setGeometry(QRect(QPoint(position.x, position.y), QSize(200, 50)));
    palette = new QPalette();
    palette->setColor(QPalette::Button, *color);
    this->setPalette(*palette);
}

My_Button::~My_Button(){

}


