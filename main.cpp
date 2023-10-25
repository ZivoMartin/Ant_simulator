#include "src/game.h"
#include "src/my_application/my_application.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    My_view view;
    view.showFullScreen();
    Game game(&view);
    view.show();
    return app.exec();
}
