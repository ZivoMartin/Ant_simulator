#include "src/game.h"
#include <QApplication>
#include "src/struct/coord.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    My_view view;
    Game game(&view);
    view.show();
    return app.exec();
}
