TARGET = ant_simulator
CONFIG += c++11

HEADERS += src/game.h src/image/my_image.h src/view/my_view.h src/ant/ant.h src/struct/coord.h src/ant/anthill.h src/food/food.h src/food/pheromone.h src/buttons/menu_button.h src/struct/size.h src/cercles/cercles.h
SOURCES += main.cpp src/game.cpp src/image/my_image.cpp src/view/my_view.cpp src/ant/ant.cpp src/ant/anthill.cpp  src/food/food.cpp src/food/pheromone.cpp src/buttons/menu_button.cpp src/cercles/cercles.cpp

QT += widgets
