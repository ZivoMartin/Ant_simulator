#ifndef safe_anthill
#define safe_anthill
#include "../image/my_image.h"
#include "../struct/coord.h"


class Game;

class Anthill : public My_image{

public:
    Anthill(Game* game, coord xy);
    ~Anthill();
    void set_pos(coord xy);
    coord *get_pos();

private:
    coord position;
};



#endif 