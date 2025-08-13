#include "Key.h"


Key::Key(b2World& world, float x, float y){

    // Definir el cuerpo
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(toMeters(x+(pixels_per_meter/2.0f)), toMeters(y+(pixels_per_meter/2.0f)));
    _body = world.CreateBody(&bodyDef);

    // Definir la forma como un cuadrado
    b2PolygonShape b2Shape;
    b2Shape.SetAsBox(toMeters(72.0f/2.0f), toMeters(62.0f/2.0f));

    // Definir las propiedades
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &b2Shape;
    fixtureDef.isSensor = true;

    _body->CreateFixture(&fixtureDef);

    // Establecer el sprite del personaje
    _texture.loadFromFile("resources/Sprites/Key.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({0, 0, 72, 62});
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2.0f, _sprite.getGlobalBounds().height/2.0f);

    // Inicializar atributos de la llave
    _frames = 0;

    //Inicializar sonido
    _soundBuffer.loadFromFile("resources/Audios/llave.wav");
    _sound.setBuffer(_soundBuffer);
    _sound.setVolume(7.0f);

}

void Key::update(){

    _frames += 0.5f;

    if (_frames > 35.0f) {
        _frames = 0.0f;
    }

    _sprite.setTextureRect({ int(_frames) + int(_frames) * 80, 0 , 72, 62 });

}

void Key::draw(sf::RenderTarget& target) const{

    // Se dibuja el sprite sobre el cuerpo
    b2Vec2 position = _body->GetPosition();
    _sprite.setPosition(toPixels(position.x), toPixels(position.y));
    target.draw(_sprite);

}

sf::FloatRect Key::getBounds() const{

    return _sprite.getGlobalBounds();

}

void Key::spawn(b2Vec2 position){

    _body->SetTransform(position, 0);
    _body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));

}

void Key::playSound(){

    _sound.play();

}

void Key::changeVolume(){

    if (_sound.getVolume() != 0.0f){
        _sound.setVolume(0.0f);
    }
    else{
        _sound.setVolume(7.0f);
    }

}
