#include "PlayerDead.h"


sf::Texture PlayerDead::_texture;
bool PlayerDead::_isTextureLoaded = false;
float PlayerDead::_width = toMeters(38.0f);
float PlayerDead::_height = toMeters(34.0f);

PlayerDead::PlayerDead(b2World& world, float x, float y){

    // Definir el cuerpo de Box2D
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(toMeters(x+(pixels_per_meter/2.0f)), toMeters(y+(pixels_per_meter/2.0f)));
    _body = world.CreateBody(&bodyDef);

    // Definir la forma como un cuadrado
    b2PolygonShape b2Shape;
    b2Shape.SetAsBox(_width/2.0f, _height/2.0f);

    // Definir las propiedades
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &b2Shape;
    fixtureDef.density = 2.5f;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.0f;

    _body->CreateFixture(&fixtureDef);
    _body->SetFixedRotation(true);

    // Cargar la textura una sola vez y usar la misma en todos los bloques
    if (!_isTextureLoaded){
        loadTexture();
    }

    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2.0f, _sprite.getGlobalBounds().height/2.0f);

}

void PlayerDead::loadTexture(){

    _texture.loadFromFile("resources/Sprites/RobotMuerto.png");
    _isTextureLoaded = true;

}

void PlayerDead::draw(sf::RenderTarget& target) const{

    // Se dibuja el sprite sobre el cuerpo
    b2Vec2 position = _body->GetPosition();
    _sprite.setPosition(toPixels(position.x), toPixels(position.y));
    target.draw(_sprite);

}

sf::FloatRect PlayerDead::getBounds() const{

    return _sprite.getGlobalBounds();

}

void PlayerDead::spawn(b2Vec2 position){

    _body->SetTransform(position, 0);
    _body->SetLinearVelocity(b2Vec2(0.0f, -0.1f));

}
