#include "BackgroundPause.h"
#include <cstdlib>
#include <iostream>

BackgroundPause::BackgroundPause(){

    srand(time(NULL));

    _texture.loadFromFile("resources/Sprites/fondoPausa.png");

    _sprite.setTexture(_texture);

}

void BackgroundPause::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.draw(_sprite, states);

}
