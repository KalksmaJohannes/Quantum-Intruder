#include "Laser.h"


sf::Texture Laser::_texture;
bool Laser::_isTextureLoaded = false;
float Laser::_width = toMeters(3.0f);

Laser::Laser(b2World& world, float x, float y, float height) : _height(height){

    // Definir el cuerpo de Box2D
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(toMeters(x+(pixels_per_meter/2.0f)), toMeters(y+(pixels_per_meter/2.0f)));
    _body = world.CreateBody(&bodyDef);

    // Definir la forma como un cuadrado
    b2PolygonShape b2Shape;
    b2Shape.SetAsBox(_width/2.0f, _height/2.0f);

    // Definir las propiedades
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &b2Shape;
    fixtureDef.density = 3.2f;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.0f;

    _body->CreateFixture(&fixtureDef);
    _body->SetFixedRotation(true);

    // Cargar la textura una sola vez y usar la misma en todos los bloques
    if (!_isTextureLoaded){
        loadTexture();
    }

    _sprite.setTexture(_texture);
    _sprite.setTextureRect({0, -520, 3, int(toPixels(height))});
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2.0f, _sprite.getGlobalBounds().height/2.0f);

}

void Laser::loadTexture(){

    _texture.loadFromFile("resources/Sprites/Laser.png");
    _isTextureLoaded = true;

}

void Laser::draw(sf::RenderTarget& target) const{

    // Se dibuja el sprite sobre el cuerpo
    b2Vec2 position = _body->GetPosition();
    _sprite.setPosition(toPixels(position.x), toPixels(position.y));
    target.draw(_sprite);

}

sf::FloatRect Laser::getBounds() const{

    return _sprite.getGlobalBounds();

}

void Laser::spawn(b2Vec2 position){

    _body->SetTransform(position, 0);
    _body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));

}
