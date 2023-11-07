#include "src/game.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    My_view view;
    Game game(&view);
    view.showFullScreen();
    view.show();
    return app.exec();
}