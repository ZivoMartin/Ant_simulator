#include "my_application.h"

bool My_application::event(QEvent *event){
    std::cout << event->type() << " " << QEvent::KeyPress << std::endl;
    if (event->type() == QEvent::KeyPress){      
        printf("keypress");  
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_A){
            std::cout << "Hello World" << std::endl;
        }
    }
    return QApplication::event(event);
}

My_application::~My_application(){
}

My_application::My_application(int argc, char *argv[]) : QApplication(argc, argv){
}