#ifndef my_app_safe
#define my_app_safe
#include <QApplication>
#include <QEvent>
#include <QKeyEvent>
#include <iostream>

class My_application : public QApplication{

public:
    My_application(int argc, char *argv[]);
    ~My_application();
    bool event(QEvent *event);
};

#endif
