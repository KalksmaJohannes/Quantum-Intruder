#include "Elevator.h"
#include "iostream"


sf::Texture Elevator::_texture;
bool Elevator::_isTextureLoaded = false;
float Elevator::_width = toMeters(40.0f*3);
float Elevator::_height = toMeters(40.0f);

Elevator::Elevator(b2World& world, float x, float y, float upperLimit, float downLimit, float speed){

    _yDownLimit = downLimit;
    _yUpperLimit = upperLimit;
    _speed = speed;


    // Definir el cuerpo de Box2D
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(toMeters(x+(pixels_per_meter/2.0f)), toMeters(y+(pixels_per_meter/2.0f)));
    _body = world.CreateBody(&bodyDef);

    // Definir los vertices fantasma
    b2Vec2 vertices[4];
    vertices[0].Set(-_width/2.0f, -_height/2.0f);
    vertices[1].Set(_width/2.0f, -_height/2.0f);
    vertices[2].Set(_width/2.0f, _height/2.0f);
    vertices[3].Set(-_width/2.0f, _height/2.0f);

    // Definir la forma como cadena (para que despues pueda ser usado en una cadena de bloques)
    b2ChainShape b2Chain;
    b2Chain.CreateLoop(vertices, 4);

    // Definir las propiedades
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &b2Chain;
    fixtureDef.density = 0.0f;
    fixtureDef.friction = 1.0f;

    _body->CreateFixture(&fixtureDef);

    // Cargar la textura una sola vez y usar la misma en todos los bloques
    if (!_isTextureLoaded){
        loadTexture();
    }

    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2.0f, _sprite.getGlobalBounds().height/2.0f);

}

void Elevator::loadTexture(){

    _texture.loadFromFile("resources/Sprites/Elevador.png");
    _isTextureLoaded = true;

}

void Elevator::draw(sf::RenderTarget& target) const{

    b2Vec2 position = _body->GetPosition();
    _sprite.setPosition(toPixels(position.x), toPixels(position.y));
    target.draw(_sprite);

}

sf::FloatRect Elevator::getBounds() const{

    return _sprite.getGlobalBounds();

}

void Elevator::update(){

    float posY = _body->GetPosition().y;
    float posX = _body->GetPosition().x;

    if (_isPaused){
        // Si est  en pausa, verifica si el tiempo de pausa ha pasado
        if (_gameClock.getElapsedTime().asSeconds() >= _pauseDuration){
            _isPaused = false;
            _gameClock.restart();
        }
        else{
            return; // Si a£n est  en pausa, no hacer nada m s
        }
    }

    if (posY >= _yUpperLimit && _state){
        _body->SetLinearVelocity(b2Vec2(0.0f, -_speed));  // Empieza a subir

        if (posY <= _yUpperLimit + 0.5f && _state){
            _body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
            _body->SetTransform(b2Vec2(posX, _yUpperLimit+0.5f),0);
            _state = false;
            _isPaused = true; // Inicia la pausa
            _gameClock.restart(); // Reinicia el reloj para la pausa
        }
    }
    else if (posY <= _yDownLimit && !_state) {
        _body->SetLinearVelocity(b2Vec2(0.0f, _speed));  // Empieza a bajar

        if (posY >= _yDownLimit - 0.5f && !_state){
            _body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
            _body->SetTransform(b2Vec2(posX, _yDownLimit-0.5f),0);
            _state = true;
            _isPaused = true; // Inicia la pausa
            _gameClock.restart(); // Reinicia el reloj para la pausa
        }
    }
}

void Elevator::spawn(float x, float y){

    _body->SetTransform(b2Vec2(x + toMeters(_sprite.getGlobalBounds().width/2.0f), y + toMeters(_sprite.getGlobalBounds().height/2.0f)), 0);
    _body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));

    _isPaused = true;
    _state = false;
    _gameClock.restart();

}
