#include "Button.h"


sf::Texture Button::_texture;
bool Button::_isTextureLoaded = false;
float Button::_width = toMeters(36.0f);
float Button::_height = toMeters(10.0f);

Button::Button(b2World& world, float x, float y){

    // Definir el cuerpo de Box2D
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(toMeters(x+(pixels_per_meter/2.0f)), toMeters(y+(pixels_per_meter/2.0f)));
    _body = world.CreateBody(&bodyDef);

    // Cargar la textura una sola vez y usar la misma en todos los bloques
    if (!_isTextureLoaded){
        loadTexture();
    }

    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2.0f, _sprite.getGlobalBounds().height/2.0f);

    // Definir la forma como un rectangulo
    b2PolygonShape b2Shape;
    b2Shape.SetAsBox(_width/2.0f, _height/2.0f);

    // Definir las propiedades
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &b2Shape;
    fixtureDef.isSensor = true;

    _body->CreateFixture(&fixtureDef);

}

void Button::loadTexture(){

    _texture.loadFromFile("resources/Sprites/Button.png");
    _isTextureLoaded = true;

}

void Button::draw(sf::RenderTarget& target) const{

    // Se dibuja el sprite sobre el cuerpo
    b2Vec2 position = _body->GetPosition();
    _sprite.setPosition(toPixels(position.x), toPixels(position.y));
    target.draw(_sprite);

}

void Button::press(b2Vec2 position){

    _body->SetTransform(position, 0);
    _body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));

}

void Button::release(b2Vec2 position){

    _body->SetTransform(position, 0);
    _body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));

}

sf::FloatRect Button::getBounds() const{

    return _sprite.getGlobalBounds();

}
