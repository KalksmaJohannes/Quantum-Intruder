#include "Block2.h"


sf::Texture Block2::_texture;
bool Block2::_isTextureLoaded = false;
float Block2::_width = toMeters(40.0f);
float Block2::_height = toMeters(40.0f);

Block2::Block2(b2World& world, float x, float y){

    // Definir el cuerpo de Box2D
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
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

void Block2::loadTexture(){

    _texture.loadFromFile("resources/Sprites/Bloque.png");
    _isTextureLoaded = true;

}

void Block2::draw(sf::RenderTarget& target) const{

    // Se dibuja el sprite sobre el cuerpo
    b2Vec2 position = _body->GetPosition();
    _sprite.setPosition(toPixels(position.x), toPixels(position.y));
    target.draw(_sprite);

}

sf::FloatRect Block2::getBounds() const{

    return _sprite.getGlobalBounds();

}
