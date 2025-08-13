#include "HealthImage.h"
#include <iostream>
HealthImage::HealthImage(){
    if(!_texture.loadFromFile("resources/Sprites/tresCorazones.png")){
        std::cout<<"No se pudo cargar la textura 'tresCorazones'";
        exit(-1);
    }
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2.0f, _sprite.getGlobalBounds().height/2.0f);
    _sprite.setPosition(180,80);
}

void HealthImage::draw(sf::RenderTarget& target) const{

    target.draw(_sprite);

}

void HealthImage::setTexture(std::string filePath){
    if(!_texture.loadFromFile(filePath)){
        std::cout<<"No se pudo cargar la textura " << filePath;
        exit(-1);
    }
}
