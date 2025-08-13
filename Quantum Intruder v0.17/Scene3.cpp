#include "Scene3.h"


Scene3::Scene3(): _world(b2Vec2(0.0f, 100.0f)), _player(_world, toPixels(26.5), toPixels(6)), _deathsCount(0){

    createMap();

    _isSceneClear = false;

}

void Scene3::createMap() {

    int i;

    /// Crear el piso
    for (i=0; i<32; i++){
        _blocks.emplace_back(_world, toPixels(i), toPixels(17));
    }

    /// Crear el techo
    for (i=0; i<32; i++){
        _blocks.emplace_back(_world, toPixels(i), 0.0f);
        _blocks.emplace_back(_world, toPixels(i), toPixels(3));
    }

    ///Crear background Blocks
    for (i=1; i<31; i++){
        _blocksBackground.emplace_back(_world, toPixels(i), toPixels(1));
        _blocksBackground.emplace_back(_world, toPixels(i), toPixels(2));
    }

    /// Crear la pared izquierda
    for (i=1; i<17; i++){
        _blocks.emplace_back(_world, 0.0f, toPixels(i));
    }

    for (i=4; i<17; i++){
        _blocks.emplace_back(_world, toPixels(1), toPixels(i));
    }

    for (i=4; i<17; i++){
        _blocks.emplace_back(_world, toPixels(2), toPixels(i));
    }

    /// Crear la pared derecha
    for (i=4; i<17; i++){
        _blocks.emplace_back(_world, toPixels(29), toPixels(i));
    }

    for (i=4; i<17; i++){
        _blocks.emplace_back(_world, toPixels(30), toPixels(i));
    }

    for (i=1; i<17; i++){
        _blocks.emplace_back(_world, toPixels(31), toPixels(i));
    }

    /// Crear plataformas
    for (i=3; i<5; i++){
        _blocks.emplace_back(_world, toPixels(i), toPixels(7));
    }

    for (i=8; i<29; i++){
        _blocks.emplace_back(_world, toPixels(i), toPixels(7));
    }

    for (i=3; i<5; i++){
        _blocks.emplace_back(_world, toPixels(i), toPixels(11));
    }

    for (i=8; i<29; i++){
        _blocks.emplace_back(_world, toPixels(i), toPixels(11));
    }

    _ramps.emplace_back(_world, toPixels(3), toPixels(4), true, false);
    _ramps.emplace_back(_world, toPixels(3), toPixels(16), true, true);
    _ramps.emplace_back(_world, toPixels(28), toPixels(16), false, true);

    /// Crear elevadores
    _elevators.emplace_back(_world, toPixels(6), toPixels(7), 7.0f, 17.0f, 2.0f);



    /// Crear pinchos
    _spikes.emplace_back(_world, toPixels(14), toPixels(3.76), false);

    /// Crear botones
    _buttonsOriginalPosition[0] = b2Vec2(17.5, 16.87);
    _buttonsOriginalPosition[1] = b2Vec2(17.5, 10.87);

    _buttons.emplace_back(_world, toPixels(0), toPixels(0));
    _buttons.emplace_back(_world, toPixels(0), toPixels(0));

    /// Crear lasers
    _lasersOriginalPosition[0] = b2Vec2(20.5, 14.5);
    _lasersOriginalPosition[1] = b2Vec2(20.5, 9.5);

    _lasers.emplace_back(_world, toPixels(0), toPixels(0), 5);
    _lasers.emplace_back(_world, toPixels(0), toPixels(0), 3);

    /// Crear llave
    _keyOriginalPosition = b2Vec2(27, 10.2);
    _key.emplace_back(_world, toPixels(_keyOriginalPosition.x), toPixels(_keyOriginalPosition.y));
    _key[0].spawn(b2Vec2(_keyOriginalPosition.x, _keyOriginalPosition.y));

    /// Crear puerta
    _door.emplace_back(_world, toPixels(24.5), toPixels(15.32));

    /// Crear a los robots muertos
    for (i=0; i<2; i++){
        _playersDead.emplace_back(_world, toPixels(1), toPixels(-1));
    }

    _levelImage.setTexture("resources/Sprites/bloqueNivel3.png");

}

void Scene3::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    for (const Button& button : _buttons){
        button.draw(target);
    }

    for (const Block& block : _blocks){
        block.draw(target);
    }

    for (const Ramp& ramp : _ramps){
        ramp.draw(target);
    }

    for (const Spike& spike : _spikes){
        spike.draw(target);
    }

    for (const Laser& laser : _lasers){
        laser.draw(target);
    }

    for (const Elevator& elevator : _elevators){
        elevator.draw(target);
    }

    for (const BlockBackground& blockBackground : _blocksBackground){
        blockBackground.draw(target);
    }

    _key[0].draw(target);

    _door[0].draw(target);

    for (const PlayerDead& playerDead : _playersDead){
        playerDead.draw(target);
    }

    _player.draw(target);

    _healthImage.draw(target);

    _levelImage.draw(target);

}

void Scene3::update(){

    _player.cmd();
    _player.update();

    b2Vec2 position = _player.getPosition();
    _player.endContact();

    /// Se actualizan los objetos animados del mapa
    for (Elevator& elevator : _elevators){
        elevator.update();
    }

    _key[0].update();

    _door[0].update();

    /// Se manejan las colisiones del personaje con las plataformas
    for (Block& block : _blocks){
        if (_player.isFootCollision(block)){
            _player.startContact();
        }
    }

    for (Ramp& ramp : _ramps){
        if (_player.isFootCollision(ramp)){
            _player.startContact();
        }
    }

    for (Elevator& elevator : _elevators){
        if (_player.isFootCollision(elevator)){
            _player.startContact();
        }
    }

    for (PlayerDead& playerDead : _playersDead){
        if (_player.isFootCollision(playerDead)){
            _player.startContact();
        }
    }

    /// Se manejan las colisiones del personaje con los pinchos
    for (Spike& spike : _spikes){
        if (_player.isCollision(spike)){
            _player.playSoundDead();

            _deathsCount ++;

            switch (_deathsCount){
                case 0:

                break;

                case 1:
                    _playersDead[0].spawn(position);
                    _healthImage.setTexture("resources/Sprites/dosCorazones.png");
                break;

                case 2:
                    _playersDead[1].spawn(position);
                    _healthImage.setTexture("resources/Sprites/unCorazones.png");
                break;

                case 3:
                    for (PlayerDead& playerDead : _playersDead){
                        playerDead.spawn(b2Vec2(1, -1));
                    }
                    _healthImage.setTexture("resources/Sprites/ceroCorazones.png");

                    //EFECTO MUERTE


                    _key[0].spawn(b2Vec2(_keyOriginalPosition.x, _keyOriginalPosition.y));

                    _door[0].close();

                    _elevators[0].spawn(5, 7);

                    _deathsCount = 0;

                    _healthImage.setTexture("resources/Sprites/tresCorazones.png");
                break;
            }

            _player.respawn(26.5f, 6.0f);

            break;
        }
    }

    /// Se manejan las colisiones del personaje con los laseres
    for (Laser& laser: _lasers){
        if (_player.isCollision(laser)){
            _player.playSoundDead();

            _deathsCount ++;

            switch (_deathsCount){
                case 0:

                break;

                case 1:
                    _playersDead[0].spawn(position);
                    _healthImage.setTexture("resources/Sprites/dosCorazones.png");
                break;

                case 2:
                    _playersDead[1].spawn(position);
                    _healthImage.setTexture("resources/Sprites/unCorazones.png");
                break;

                case 3:
                    for (PlayerDead& playerDead : _playersDead){
                        playerDead.spawn(b2Vec2(1, -1));
                    }
                    _healthImage.setTexture("resources/Sprites/ceroCorazones.png");

                    //EFECTO MUERTE

                    _key[0].spawn(b2Vec2(_keyOriginalPosition.x, _keyOriginalPosition.y));

                    _door[0].close();

                    _elevators[0].spawn(5, 7);

                    _deathsCount = 0;

                    _healthImage.setTexture("resources/Sprites/tresCorazones.png");
                break;
            }

            _player.respawn(26.5f, 6.0f);

            break;
        }
    }

    /// Se manejan las colisiones del personaje con los botones
    for (int i=0; i<2; i++){
        bool isPressed = false;

        if (_player.isCollision(_buttons[i])){
            _buttons[i].press(b2Vec2(_buttonsOriginalPosition[i].x, _buttonsOriginalPosition[i].y + toMeters(5.0f)));
            _lasers[i].spawn(b2Vec2(-1, -5));
            isPressed = true;
        }

        for (PlayerDead& playerDead : _playersDead){
            if (playerDead.isCollision(_buttons[i])){
                _buttons[i].press(b2Vec2(_buttonsOriginalPosition[i].x, _buttonsOriginalPosition[i].y + toMeters(5.0f)));
                _lasers[i].spawn(b2Vec2(-1, -5));
                isPressed = true;
            }
        }

        if (!isPressed){
            _buttons[i].release(_buttonsOriginalPosition[i]);
            _lasers[i].spawn(_lasersOriginalPosition[i]);
        }
    }

    /// Se maneja la colision del personaje con la llave
    if (_player.isCollision(_key[0])){
        _key[0].playSound();
        _key[0].spawn(b2Vec2(3, -5));

        _door[0].open();
    }

    /// Se maneja la colision del personaje con la puerta abierta
    if (_door[0].isDoorSensorCollision(_player)){
        _isSceneClear = true;
    }

}

b2World& Scene3::getWorld(){

    return _world;

}

void Scene3::resetScene(){

    _isSceneClear = false;

    for (PlayerDead& playerDead : _playersDead){
        playerDead.spawn(b2Vec2(1, -1));
    }

    _key[0].spawn(b2Vec2(_keyOriginalPosition.x, _keyOriginalPosition.y));

    _door[0].close();

    _deathsCount = 0;

    _elevators[0].spawn(5, 7);

    _player.respawn(26.5f, 6.0f);

    _healthImage.setTexture("resources/Sprites/tresCorazones.png");

}

bool Scene3::getSceneClear(){

    return _isSceneClear;

}

Scene3::~Scene3(){

    b2Body* body = _world.GetBodyList();

    // Destruir todos los cuerpos del world
    while (body){
        b2Body* nextBody = body->GetNext();
        _world.DestroyBody(body);
        body = nextBody;
    }

}

void Scene3::changeVolume(){

    _player.changeVolume();
    _key[0].changeVolume();

}
