#include "my_application.h"

bool My_application::notify(QObject *receiver, QEvent *e){
    // std::cout << event->type() << std::endl;
    if (e->type() == QEvent::KeyPress){      
        printf("keypress");  
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);
        if (keyEvent->key() == Qt::Key_A){
            if(game != nullptr){
                std::cout << "touche a pressée !!" << std::endl;
                //game->change_view_state();
            }
        }
    }
    return false;
}

My_application::~My_application(){
}

void My_application::set_game(Game *game){
    this->game = game;
}

My_application::My_application(int argc, char *argv[]) : QApplication(argc, argv){
}