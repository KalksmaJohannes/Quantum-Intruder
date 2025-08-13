#include "Door.h"


Door::Door(b2World& world, float x, float y){

    // Definir el cuerpo
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(toMeters(x+(pixels_per_meter/2.0f)), toMeters(y+(pixels_per_meter/2.0f)));
    _body = world.CreateBody(&bodyDef);

    // Definir la forma como un rectangulo
    b2PolygonShape b2Shape;
    b2Shape.SetAsBox(toMeters(98.0f/2.0f), toMeters(95.0f/2.0f));

    // Definir las propiedades
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &b2Shape;
    fixtureDef.isSensor = true;

    _body->CreateFixture(&fixtureDef);

    // Establecer el sprite de la puerta
    _texture.loadFromFile("resources/Sprites/Door.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({0, 0, 98, 95});
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2.0f, _sprite.getGlobalBounds().height/2.0f);

    // Establecer el sprite del sensor de la puerta
    _doorSensorTexture.loadFromFile("resources/Sprites/doorSensor.png");
    _doorSensorSprite.setTexture(_doorSensorTexture);
    _doorSensorSprite.setOrigin(_doorSensorSprite.getGlobalBounds().width/2.0f, _doorSensorSprite.getGlobalBounds().height/2.0f);

    // Inicializar atributos de la puerta
    _frames = 0;
    _isKeyCollected = false;

}

void Door::open(){

    _isKeyCollected = true;

}

void Door::close(){

    _isKeyCollected = false;

}

void Door::update(){

    if (_isKeyCollected){
        if (_frames < 11.0f) {
            _frames += 0.2f;

            _sprite.setTextureRect({ int(_frames) * 144, 0 , 98, 95 });
        }
    }
    else{
        _frames = 0;

        _sprite.setTextureRect({0, 0, 98, 95});
    }

}

void Door::draw(sf::RenderTarget& target) const{

    b2Vec2 position = _body->GetPosition();

    _sprite.setPosition(toPixels(position.x), toPixels(position.y));
    target.draw(_sprite);

    if (_isKeyCollected){
        _doorSensorSprite.setPosition(toPixels(position.x), toPixels(position.y)+19.0f);
        target.draw(_doorSensorSprite);
    }

}

sf::FloatRect Door::getBounds() const{

    return _sprite.getGlobalBounds();

}

sf::FloatRect Door::getDoorSensorBounds() const{

    return _doorSensorSprite.getGlobalBounds();

}

bool Door::isDoorSensorCollision(const Collisionable& collisionable) const{

    return getDoorSensorBounds().intersects(collisionable.getBounds());

}
