#include "LevelImage.h"
#include <iostream>
LevelImage::LevelImage(){
    if(!_texture.loadFromFile("resources/Sprites/bloqueNivel1.png")){
        std::cout<<"No se pudo cargar la textura 'bloqueNivel'";
        exit(-1);
    }
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2.0f, _sprite.getGlobalBounds().height/2.0f);
    _sprite.setPosition(640,80);
}

void LevelImage::draw(sf::RenderTarget& target) const{

    target.draw(_sprite);

}

void LevelImage::setTexture(std::string filePath){
    if(!_texture.loadFromFile(filePath)){
        std::cout<<"No se pudo cargar la textura " << filePath;
        exit(-1);
    }
}
