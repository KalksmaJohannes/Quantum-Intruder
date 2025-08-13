#include "Loading.h"

Loading::Loading(){

    //Establecer sprite del loading
    _texture.loadFromFile("resources/Sprites/Cargando.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({3533, 2, 320, 240});
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2.0f, _sprite.getGlobalBounds().height/2.0f);
    _sprite.setPosition(1280/2, 720/2);
    _sprite.setScale(4, 3);

    //Inicializar atributos del loading
    _frames = 0;
    _isLoading = false;

    //Inicializar sonido
    _soundBuffer.loadFromFile("resources/Audios/pasar nivel.wav");
    _sound.setBuffer(_soundBuffer);
    _sound.setVolume(12.0f);

}

void Loading::load(){

    _isLoading = true;

    _sound.play();

}

void Loading::update(){

    if (_isLoading){
        if (_frames < 11.0f) {
            _frames += 0.3f;

            _sprite.setTextureRect({ (int(_frames) * 320) + 2 + (1 * (int)_frames), 2 , 320, 240 });
        }
        else{
            _isLoading = false;
        }
    }
    else{
        _frames = 0;

        _sprite.setTextureRect({3533, 2, 320, 240});
    }

}

void Loading::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.draw(_sprite, states);

}

void Loading::changeVolume(){

    if (_sound.getVolume() != 0.0f){
        _sound.setVolume(0.0f);
    }
    else{
        _sound.setVolume(12.0f);
    }

}
