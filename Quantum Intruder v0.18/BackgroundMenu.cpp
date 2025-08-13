#include "BackgroundMenu.h"


BackgroundMenu::BackgroundMenu(){

    _texture.loadFromFile("resources/Sprites/fondoMenu.png");

    _sprite.setTexture(_texture);




}

void BackgroundMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.draw(_sprite, states);

}
