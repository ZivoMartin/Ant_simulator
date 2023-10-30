#ifndef my_app_safe
#define my_app_safe
#include <QApplication>
#include <QEvent>
#include <QKeyEvent>
#include "../game.h"


class My_application : public QApplication{

public:
    My_application(int argc, char *argv[]);
    ~My_application();
    bool notify(QObject *receiver, QEvent *e) override;
    void set_game(Game *game);

private:
    Game *game;
};

#endif
