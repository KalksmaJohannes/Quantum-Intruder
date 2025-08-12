#include "Director.h"


int main(){

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Quantum Intruder");
    window.setFramerateLimit(60);

    Director director(window);

    while (window.isOpen()){
        director.update();
        director.draw();
    }

    return 0;
}
