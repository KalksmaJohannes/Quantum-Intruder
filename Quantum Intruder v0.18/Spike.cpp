#include "Spike.h"


sf::Texture Spike::_texture;
bool Spike::_isTextureLoaded = false;
float Spike::_width = toMeters(28.0f);
float Spike::_height = toMeters(20.0f);

Spike::Spike(b2World& world, float x, float y, bool facingUp){

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

    // Definir los vertices
    b2Vec2 vertices[3];
    if (facingUp){
        vertices[0].Set(0.0f, -_height/2.0f);
        vertices[1].Set(_width/2.0f, _height/2.0f);
        vertices[2].Set(-_width/2.0f, _height/2.0f);
    }
    else{
        vertices[0].Set(-_width/2.0f, -_height/2.0f);
        vertices[1].Set(_width/2.0f, -_height/2.0f);
        vertices[2].Set(0.0f, _height/2.0f);

        _sprite.setScale(1, -1);
    }

    // Definir la forma como cadena (para que despues pueda ser usado en una cadena de bloques)
    b2PolygonShape b2Shape;
    b2Shape.Set(vertices, 3);

    // Definir las propiedades
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &b2Shape;
    fixtureDef.isSensor = true;

    _body->CreateFixture(&fixtureDef);

    /*b2Fixture* spikeSensor = _body->CreateFixture(&fixtureDef);
    spikeSensor->GetUserData().pointer = static_cast<uintptr_t>(SPIKE_SENSOR_ID);

    // Asignar el puntero de usuario para el cuerpo
    _body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);*/

}

void Spike::loadTexture(){

    _texture.loadFromFile("resources/Sprites/Pincho.png");
    _isTextureLoaded = true;

}

void Spike::draw(sf::RenderTarget& target) const{

    // Se dibuja el sprite sobre el cuerpo
    b2Vec2 position = _body->GetPosition();
    _sprite.setPosition(toPixels(position.x), toPixels(position.y));
    target.draw(_sprite);

}

sf::FloatRect Spike::getBounds() const{

    return _sprite.getGlobalBounds();

}
