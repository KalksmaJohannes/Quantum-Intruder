#include "AnimationRespawn.h"

AnimationRespawn::AnimationRespawn(){

    //Establecer sprite del loading
    _texture.loadFromFile("resources/Sprites/Respawn Animation.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({0, 0, 240, 240});
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2.0f, _sprite.getGlobalBounds().height/2.0f);
    _sprite.setScale(0.8, 0.8);

    //Inicializar atributos del loading
    _frames = 0;
    _isRespawning = false;

}

void AnimationRespawn::respawn(float x, float y){

    _isRespawning = true;

    _x = x;
    _y = y;

}

void AnimationRespawn::update(){

    if (_isRespawning){
        if (_frames < 11.0f) {
            _frames += 1.0f;

            _sprite.setTextureRect({ int(_frames) * 248, 0 , 240, 240 });
        }
        else{
            _isRespawning = false;
        }
    }
    else{
        _frames = 0;
    }

}

void AnimationRespawn::draw(sf::RenderTarget& target) const{

    // Se dibuja el sprite sobre el cuerpo
    _sprite.setPosition(toPixels(_x), toPixels(_y));
    target.draw(_sprite);

}

bool AnimationRespawn::getIsRespawning(){

    return _isRespawning;

}
