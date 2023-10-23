#ifndef safe_ant
#define safe_ant
#include "../image/my_image.h"
#include "../struct/coord.h"


class Game;

class Ant : public My_image{

public:
    Ant(Game* game, coord xy);
    ~Ant();
    void set_pos(coord xy);
};



#endif 