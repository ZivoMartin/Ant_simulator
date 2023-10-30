#include "src/game.h"
#include "src/my_application/my_qwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    My_view view;
    Game game(&view);
    view.set_game(&game);
    view.showFullScreen();
    view.show();
    return app.exec();
}