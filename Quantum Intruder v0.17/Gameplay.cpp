#include "Gameplay.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Gameplay::Gameplay(sf::RenderWindow& window): _window(window), _textColor(204, 217, 4){

    if(!_font.loadFromFile("resources/Fonts/Robot Crush.ttf")){
        std::cout<<"No se pudo cargar la fuente";
        exit(-1);
    }
    _text.setFont(_font);
    _text.setCharacterSize(50);
    _text.setFillColor(_textColor);
    _text.setPosition(930,50);
    _text.setStyle(sf::Text::Bold);
    _gameCompleted = false;
    _timeTrialMode = false;
    _level = 1;

}

void Gameplay::update(){
    switch (_level){
        case 1:
            if (!_mapa1.getSceneClear()){
                _mapa1.getWorld().Step(1 / 60.0f, 8, 3);
                _mapa1.update();
            }
            else if (_timeTrialMode){
                _level ++;
            }
            else _gameCompleted = true;
        break;

        case 2:
            if (!_mapa2.getSceneClear()){
                _mapa2.getWorld().Step(1 / 60.0f, 8, 3);
                _mapa2.update();
            }
            else if (_timeTrialMode){
                _level ++;
            }
            else _gameCompleted = true;
        break;

        case 3:
            if (!_mapa3.getSceneClear()){
                _mapa3.getWorld().Step(1 / 60.0f, 8, 3);
                _mapa3.update();
            }
            else if (_timeTrialMode){
                _level ++;
            }
            else _gameCompleted = true;
        break;

        case 4:
            if (!_mapa4.getSceneClear()){
                _mapa4.getWorld().Step(1 / 60.0f, 8, 3);
                _mapa4.update();
            }
            else if (_timeTrialMode){
                _level ++;
            }
            else _gameCompleted = true;
        break;

        case 5:
            if (!_mapa5.getSceneClear()){
                _mapa5.getWorld().Step(1 / 60.0f, 8, 3);
                _mapa5.update();
            }
            else if (_timeTrialMode){
                _level ++;
            }
            else _gameCompleted = true;
        break;

        case 6:
            if (!_mapa6.getSceneClear()){
                _mapa6.getWorld().Step(1 / 60.0f, 8, 3);
                _mapa6.update();
            }
            else if (_timeTrialMode){
                _level ++;
            }
            else _gameCompleted = true;
        break;

        case 7:
            if (!_mapa7.getSceneClear()){
                _mapa7.getWorld().Step(1 / 60.0f, 8, 3);
                _mapa7.update();
            }
            else if (_timeTrialMode){
                _level ++;
            }
            else _gameCompleted = true;
        break;

        case 8:
            if (!_mapa8.getSceneClear()){
                _mapa8.getWorld().Step(1 / 60.0f, 8, 3);
                _mapa8.update();
            }
            else if (_timeTrialMode){
                _level ++;
            }
            else _gameCompleted = true;
        break;

        case 9:
            if (!_mapa9.getSceneClear()){
                _mapa9.getWorld().Step(1 / 60.0f, 8, 3);
                _mapa9.update();
            }
            else _gameCompleted = true;
        break;
    }
    //Actualizar los minutos
    _elapsedTime = _pausedTime + _chronometrer.getElapsedTime();
    float elapsedSeconds = _elapsedTime.asSeconds();
    _minutes = static_cast<int>(elapsedSeconds) / 60;
    _seconds = static_cast<int>(elapsedSeconds) % 60;
}

void Gameplay::pause(){
    _pausedTime += _chronometrer.getElapsedTime();
}

void Gameplay::start(){
    _chronometrer.restart();
}

void Gameplay::setTimeTrialMode(bool active){

    _timeTrialMode = active;

    _chronometrer.restart();
    _pausedTime = sf::seconds(0.0f);

}

bool Gameplay::getTimeTrialMode(){

    return _timeTrialMode;

}

void Gameplay::setLevel(int level){

    _level = level;

}

void Gameplay::resetGameCompleted(){

    _gameCompleted = false;

    _mapa1.resetScene();
    _mapa2.resetScene();
    _mapa3.resetScene();
    _mapa4.resetScene();
    _mapa5.resetScene();
    _mapa6.resetScene();
    _mapa7.resetScene();
    _mapa8.resetScene();
    _mapa9.resetScene();

}

bool Gameplay::getGameCompleted(){

    return _gameCompleted;

}

sf::Time Gameplay::getTimeScore(){

    return _elapsedTime;

}

void Gameplay::draw(){

    _window.draw(_background);

    switch (_level){
        case 1:
            if (!_mapa1.getSceneClear()){
                _window.draw(_mapa1);
            }
            else if (_timeTrialMode){
                _level ++;
            }
        break;

        case 2:
            if (!_mapa2.getSceneClear()){
                _window.draw(_mapa2);
            }
            else if (_timeTrialMode){
                _level ++;
            }
        break;

        case 3:
            if (!_mapa3.getSceneClear()){
                _window.draw(_mapa3);
            }
            else if (_timeTrialMode){
                _level ++;
            }
        break;

        case 4:
            if (!_mapa4.getSceneClear()){
                _window.draw(_mapa4);
            }
            else if (_timeTrialMode){
                _level ++;
            }
        break;

        case 5:
            if (!_mapa5.getSceneClear()){
                _window.draw(_mapa5);
            }
            else if (_timeTrialMode){
                _level ++;
            }
        break;

        case 6:
            if (!_mapa6.getSceneClear()){
                _window.draw(_mapa6);
            }
            else if (_timeTrialMode){
                _level ++;
            }
        break;

        case 7:
            if (!_mapa7.getSceneClear()){
                _window.draw(_mapa7);
            }
            else if (_timeTrialMode){
                _level ++;
            }
        break;

        case 8:
            if (!_mapa8.getSceneClear()){
                _window.draw(_mapa8);
            }
            else if (_timeTrialMode){
                _level ++;
            }
        break;

        case 9:
            if (!_mapa9.getSceneClear()){
                _window.draw(_mapa9);
            }
        break;
    }

    if(_timeTrialMode){
        //std::cout<<"Time: "<<(int)_chronometrer.getElapsedTime().asSeconds()/60<<":"<<(int)_chronometrer.getElapsedTime().asSeconds()%60<<std::endl;

        // Formatear el tiempo como MM:SS
        std::ostringstream ss;
        ss << std::setfill('0') << std::setw(2) << _minutes << ":" << std::setfill('0') << std::setw(2) << _seconds;
        _text.setString("Time: " + ss.str());
        _window.draw(_text);
    }

}
