TARGET = ant_simulator
CONFIG += c++11

HEADERS += src/game.h src/image/my_image.h src/view/my_view.h src/ant/ant.h src/struct/coord.h src/ant/anthill.h src/my_application/my_application.h src/food/food.h

SOURCES += main.cpp src/game.cpp src/image/my_image.cpp src/view/my_view.cpp src/ant/ant.cpp src/ant/anthill.cpp src/my_application/my_application.cpp src/food/food.cpp

QT += widgets
