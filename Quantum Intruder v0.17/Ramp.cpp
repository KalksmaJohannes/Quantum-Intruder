#include "Ramp.h"


sf::Texture Ramp::_texture;
bool Ramp::_isTextureLoaded = false;
float Ramp::_width = toMeters(40.0f);
float Ramp::_height = toMeters(40.0f);

Ramp::Ramp(b2World& world, float x, float y, float facingRight, float facingUp){

    // Definir el cuerpo de Box2D
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(toMeters(x+(pixels_per_meter/2.0f)), toMeters(y+(pixels_per_meter/2.0f)));
    _body = world.CreateBody(&bodyDef);

    // Cargar la textura una sola vez y usar la misma en todos los bloques
    if (!_isTextureLoaded){
        loadTexture();
    }

    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2.0f, _sprite.getGlobalBounds().height/2.0f);

    // Definir los vertices fantasma
    b2Vec2 vertices[3];
    if (facingRight){
        if (facingUp){
            vertices[0].Set(-_width/2.0f, -_height/2.0f);
            vertices[1].Set(_width/2.0f, _height/2.0f);
            vertices[2].Set(-_width/2.0f, _height/2.0f);
        }
        else{
            vertices[0].Set(-_width/2.0f, -_height/2.0f);
            vertices[1].Set(_width/2.0f, -_height/2.0f);
            vertices[2].Set(-_width/2.0f, _height/2.0f);

            _sprite.setScale(1, -1);
        }
    }
    else{
        if (facingUp){
            vertices[0].Set(_width/2.0f, -_height/2.0f);
            vertices[1].Set(-_width/2.0f, _height/2.0f);
            vertices[2].Set(_width/2.0f, _height/2.0f);

            _sprite.setScale(-1, 1);
        }
        else{
            vertices[0].Set(-_width/2.0f, -_height/2.0f);
            vertices[1].Set(_width/2.0f, -_height/2.0f);
            vertices[2].Set(_width/2.0f, _height/2.0f);

            _sprite.setScale(-1, -1);
        }
    }

    // Definir la forma como cadena (para que despues pueda ser usado en una cadena de rampas)
    b2PolygonShape b2Shape;
    b2Shape.Set(vertices, 3);

    // Definir las propiedades
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &b2Shape;
    fixtureDef.density = 0.0f;
    fixtureDef.friction = 0.0f;

    _body->CreateFixture(&fixtureDef);

}

void Ramp::loadTexture(){

    _texture.loadFromFile("resources/Sprites/Rampa.png");
    _isTextureLoaded = true;

}

void Ramp::draw(sf::RenderTarget& target) const{

    // Se dibuja el sprite sobre el cuerpo
    b2Vec2 position = _body->GetPosition();
    _sprite.setPosition(toPixels(position.x), toPixels(position.y));
    target.draw(_sprite);

}

sf::FloatRect Ramp::getBounds() const{

    return _sprite.getGlobalBounds();

}
