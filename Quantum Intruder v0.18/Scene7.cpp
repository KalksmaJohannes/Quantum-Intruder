#include "Scene7.h"


Scene7::Scene7(): _world(b2Vec2(0.0f, 100.0f)), _player(_world, toPixels(6.5), toPixels(16)), _deathsCount(0){

    createMap();

    _isSceneClear = false;

}

void Scene7::createMap() {

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
    for (i=7; i<9; i++){
        _blocks.emplace_back(_world, toPixels(i), toPixels(6));
    }

    _blocks.emplace_back(_world, toPixels(8), toPixels(7));

    for (i=14; i<23; i++){
        _blocks.emplace_back(_world, toPixels(i), toPixels(7));
    }

    _blocks.emplace_back(_world, toPixels(3), toPixels(8));
    _blocks.emplace_back(_world, toPixels(8), toPixels(8));

    for (i=14; i<23; i++){
        _blocks.emplace_back(_world, toPixels(i), toPixels(8));
    }

    _blocks.emplace_back(_world, toPixels(8), toPixels(9));

    for (i=21; i<23; i++){
        _blocks.emplace_back(_world, toPixels(i), toPixels(9));
    }

    _blocks.emplace_back(_world, toPixels(8), toPixels(10));

    for (i=21; i<23; i++){
        _blocks.emplace_back(_world, toPixels(i), toPixels(10));
    }

    for (i=7; i<9; i++){
        _blocks.emplace_back(_world, toPixels(i), toPixels(11));
    }

    for (i=21; i<23; i++){
        _blocks.emplace_back(_world, toPixels(i), toPixels(11));
    }

    _blocks.emplace_back(_world, toPixels(8), toPixels(12));

    for (i=22; i<29; i++){
        _blocks.emplace_back(_world, toPixels(i), toPixels(12));
    }

    _blocks.emplace_back(_world, toPixels(8), toPixels(13));

    for (i=26; i<29; i++){
        _blocks.emplace_back(_world, toPixels(i), toPixels(13));
    }

    _blocks.emplace_back(_world, toPixels(3), toPixels(14));
    _blocks.emplace_back(_world, toPixels(8), toPixels(14));

    for (i=26; i<29; i++){
        _blocks.emplace_back(_world, toPixels(i), toPixels(14));
    }

    _blocks.emplace_back(_world, toPixels(8), toPixels(15));

    for (i=12; i<14; i++){
        _blocks.emplace_back(_world, toPixels(i), toPixels(15));
    }

    for (i=26; i<29; i++){
        _blocks.emplace_back(_world, toPixels(i), toPixels(15));
    }

    for (i=8; i<16; i++){
        _blocks.emplace_back(_world, toPixels(i), toPixels(16));
    }

    for (i=26; i<29; i++){
        _blocks.emplace_back(_world, toPixels(i), toPixels(16));
    }

    _ramps.emplace_back(_world, toPixels(3), toPixels(4), true, false);
    _ramps.emplace_back(_world, toPixels(3), toPixels(16), true, true);
    _ramps.emplace_back(_world, toPixels(14), toPixels(15), true, true);
    _ramps.emplace_back(_world, toPixels(16), toPixels(16), true, true);
    _ramps.emplace_back(_world, toPixels(21), toPixels(12), false, false);
    _ramps.emplace_back(_world, toPixels(28), toPixels(4), false, false);

    /// Crear elevadores
    _elevators.emplace_back(_world, toPixels(10), toPixels(6), 6.0f, 16.0f, 2.0f);


    /// Crear pinchos
    for (i=22; i<26; i++){
        _spikes.emplace_back(_world, toPixels(i), toPixels(12.76), false);
    }

    /// Crear botones
    _buttonOriginalPosition = b2Vec2(5.5f, 16.87f);

    _buttons.emplace_back(_world, toPixels(0), toPixels(0));

    /// Crear lasers
    _laserOriginalPosition = b2Vec2(20.5f, 5.5f);

    _lasers.emplace_back(_world, toPixels(0), toPixels(0), 3.0f);

    /// Crear llave
    _keyOriginalPosition = b2Vec2(19.0f, 6.2f);
    _key.emplace_back(_world, toPixels(_keyOriginalPosition.x), toPixels(_keyOriginalPosition.y));
    _key[0].spawn(b2Vec2(_keyOriginalPosition.x, _keyOriginalPosition.y));

    /// Crear puerta
    _door.emplace_back(_world, toPixels(26.5), toPixels(10.32));

    /// Crear a los robots muertos
    for (i=0; i<2; i++){
        _playersDead.emplace_back(_world, toPixels(1), toPixels(-1));
    }

    _levelImage.setTexture("resources/Sprites/bloqueNivel7.png");

}

void Scene7::draw(sf::RenderTarget& target, sf::RenderStates states) const{

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

void Scene7::update(){

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

                    _elevators[0].spawn(9, 6);

                    _deathsCount = 0;

                    _healthImage.setTexture("resources/Sprites/tresCorazones.png");
                break;
            }

            _player.respawn(6.5f, 16.0f);

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

                    _elevators[0].spawn(9, 6);

                    _deathsCount = 0;

                    _healthImage.setTexture("resources/Sprites/tresCorazones.png");
                break;
            }

            _player.respawn(6.5f, 16.0f);

            break;
        }
    }

    /// Se manejan las colisiones del personaje con los botones
    for (int i=0; i<1; i++){
        bool isPressed = false;

        if (_player.isCollision(_buttons[i])){
            _buttons[i].press(b2Vec2(_buttonOriginalPosition.x, _buttonOriginalPosition.y + toMeters(5.0f)));
            _lasers[i].spawn(b2Vec2(-1, -5));
            isPressed = true;
        }

        for (PlayerDead& playerDead : _playersDead){
            if (playerDead.isCollision(_buttons[i])){
                _buttons[i].press(b2Vec2(_buttonOriginalPosition.x, _buttonOriginalPosition.y + toMeters(5.0f)));
                _lasers[i].spawn(b2Vec2(-1, -5));
                isPressed = true;
            }
        }

        if (!isPressed){
            _buttons[i].release(_buttonOriginalPosition);
            _lasers[i].spawn(_laserOriginalPosition);
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

b2World& Scene7::getWorld(){

    return _world;

}

void Scene7::resetScene(){

    _isSceneClear = false;

    for (PlayerDead& playerDead : _playersDead){
        playerDead.spawn(b2Vec2(1, -1));
    }

    _key[0].spawn(b2Vec2(_keyOriginalPosition.x, _keyOriginalPosition.y));

    _door[0].close();

    _elevators[0].spawn(9, 6);

    _deathsCount = 0;

    _player.respawn(6.5f, 16.0f);

    _healthImage.setTexture("resources/Sprites/tresCorazones.png");

}

bool Scene7::getSceneClear(){

    return _isSceneClear;

}

Scene7::~Scene7() {

    b2Body* body = _world.GetBodyList();

    // Destruir todos los cuerpos del world
    while (body){
        b2Body* nextBody = body->GetNext();
        _world.DestroyBody(body);
        body = nextBody;
    }

}

void Scene7::changeVolume(){

    _player.changeVolume();
    _key[0].changeVolume();

}
