#include "Player.h"


Player::Player(b2World& world, float x, float y){

    // Definir el cuerpo
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(toMeters(x+(pixels_per_meter/2.0f)), toMeters(y+(pixels_per_meter/2.0f)));
    _body = world.CreateBody(&bodyDef);

    // Definir la forma como un cuadrado
    b2PolygonShape b2Shape;
    b2Shape.SetAsBox(toMeters(38.0f/2.0f), toMeters(38.0f/2.0f));

    // Definir las propiedades
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &b2Shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.0f;

    _body->CreateFixture(&fixtureDef);
    _body->SetFixedRotation(true);

    // Establecer el sprite del personaje
    _playerTexture.loadFromFile("resources/Sprites/Robot.png");
    _playerSprite.setTexture(_playerTexture);
    _playerSprite.setTextureRect({139, 0, 40, 40});
    _playerSprite.setOrigin(_playerSprite.getGlobalBounds().width/2.0f, _playerSprite.getGlobalBounds().height/2.0f);

    // Establecer el sprite del pie
    _footTexture.loadFromFile("resources/Sprites/footSensor.png");
    _footSprite.setTexture(_footTexture);
    _footSprite.setOrigin(_footSprite.getGlobalBounds().width/2.0f, _footSprite.getGlobalBounds().height/2.0f);

    // Inicializar los atributos del personaje
    _frameIdle = 0.0f;
    _frameMoving = 0.0f;
    _moveSpeed = 6.0f;
    _maxJumpForce = 5.0f;
    _currentJumpForce = 0.0f;
    _canJump = false;
    _jumpKeyReleased = true;
    _isJumping = false;
    _state = PlayerState::Idle;

    // Inicializar los sonidos del personaje
    _soundJumpBuffer.loadFromFile("resources/Audios/salto.wav");
    _soundJump.setBuffer(_soundJumpBuffer);
    _soundJump.setVolume(10.0f);

    _soundDeadBuffer.loadFromFile("resources/Audios/muerte.wav");
    _soundDead.setBuffer(_soundDeadBuffer);
    _soundDead.setVolume(12.0f);

}

void Player::cmd(){

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        _state = PlayerState::Moving;
        _moveSpeed = -6.0f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        _state = PlayerState::Moving;
        _moveSpeed = 6.0f;
    }
    else{
        _state = PlayerState::Idle;
        _moveSpeed = 0.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        if(_canJump && _jumpKeyReleased){
            _isJumping = true;
            _jumpClock.restart();
            _currentJumpForce = 0.0f;
            _jumpKeyReleased = false;
            _soundJump.play();
        }

        if (_isJumping && _currentJumpForce != _maxJumpForce){
            sf::Time timeElapsed = _jumpClock.getElapsedTime();
            _currentJumpForce = std::min(timeElapsed.asSeconds() * _maxJumpForce + 4.6f, _maxJumpForce);
            /*std::cout<<std::endl<<"TIEMPO TRANSCURRIDO = "<<timeElapsed.asSeconds()<<std::endl;
            std::cout<<std::endl<<"FUERZA DE SALTO = "<<_currentJumpForce<<std::endl;*/
            _body->ApplyLinearImpulseToCenter(b2Vec2(0, -_currentJumpForce), true);
        }
    }
    else{
        if(_canJump){
            _jumpKeyReleased = true;
        }

        if (_isJumping){
            b2Vec2 vel = _body->GetLinearVelocity();

            if (vel.y < 0.0f){
                vel.y = 0.0f;
            }

            _body->SetLinearVelocity(vel);
            _isJumping = false;
        }
    }

}

void Player::update(){

    switch (_state) {
        case PlayerState::Idle:{
            float frameSpeeds[4] = { 0.006f, 0.1f, 0.01f, 0.1f };

            /*for (b2Fixture* fixture = _body->GetFixtureList(); fixture; fixture = fixture->GetNext()){
                fixture->SetFriction(1.0f);
            }*/

            _frameIdle += frameSpeeds[int(_frameIdle)];

            if (_frameIdle > 4.0f) {
                _frameIdle = 0.0f;
            }

            _playerSprite.setTextureRect({ 0, 0 + int(_frameIdle) * 75 , 40, 40 });

            }
        break;

        case PlayerState::Moving:
            /*for (b2Fixture* fixture = _body->GetFixtureList(); fixture; fixture = fixture->GetNext()){
                fixture->SetFriction(0.0f);
            }*/

            _frameMoving += 0.2f;

            if (_frameMoving > 4.0f) {
                _frameMoving = 0.0f;
            }

            _playerSprite.setTextureRect({ 139 + int(_frameMoving) * 84, 0 , 40, 40 });

            if (_moveSpeed < 0){
                _playerSprite.setScale(-1, 1);
            }
            else if (_moveSpeed > 0){
                _playerSprite.setScale(1, 1);
            }
        break;
    }

    _body->SetLinearVelocity(b2Vec2(_moveSpeed, _body->GetLinearVelocity().y));

    b2Vec2 position = _body->GetPosition();
    _playerSprite.setPosition(toPixels(position.x), toPixels(position.y));

    _animationRespawn.update();

}

void Player::draw(sf::RenderTarget& target) const{

    b2Vec2 position = _body->GetPosition();

    _playerSprite.setPosition(toPixels(position.x), toPixels(position.y));
    _footSprite.setPosition(toPixels(position.x), toPixels(position.y)+20.0f);

    target.draw(_playerSprite);
    target.draw(_footSprite);

    if (_animationRespawn.getIsRespawning()){
        _animationRespawn.draw(target);
    }

}

sf::FloatRect Player::getBounds() const{

    return _playerSprite.getGlobalBounds();

}

sf::FloatRect Player::getFootBounds() const{

    return _footSprite.getGlobalBounds();

}

bool Player::isFootCollision(const Collisionable& collisionable) const{

    return getFootBounds().intersects(collisionable.getBounds());

}

b2Vec2 Player::getPosition() const{

    b2Vec2 position = _body->GetPosition();


    return position;
}

void Player::startContact(){

    _canJump = true;

    //std::cout << "Contact Started: _canJump = " << _canJump << std::endl;

}

void Player::endContact(){

    _canJump = false;

    //std::cout << "Contact Ended: _canJump = " << _canJump << std::endl;

}

void Player::respawn(float x, float y){

    //std::cout << "respawn: Executing respawn" << std::endl;
    _body->SetTransform(b2Vec2(x + toMeters(_playerSprite.getGlobalBounds().width/2.0f), y + toMeters(_playerSprite.getGlobalBounds().height/2.0f)), 0);
    _body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));

    _animationRespawn.respawn(x + 0.5, y + 0.5);

}

void Player::playSoundDead(){

    _soundDead.play();

}

void Player::changeVolume(){

    if (_soundJump.getVolume() != 0){
        _soundJump.setVolume(0.0f);
        _soundDead.setVolume(0.0f);
    }
    else{
        _soundJump.setVolume(10.0f);
        _soundDead.setVolume(12.0f);
    }

}
