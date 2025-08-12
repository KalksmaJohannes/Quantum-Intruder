#include "Background.h"

Background::Background(){

    _texture.loadFromFile("resources/Sprites/fondo.png");

    _sprite.setTexture(_texture);




}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.draw(_sprite, states);

}
