#include "Director.h"
#include <iostream>


Director::Director(sf::RenderWindow& window)
    : _window(window),
    _menuMain(window.getSize().x, window.getSize().y),
    _menuPlay(window.getSize().x, window.getSize().y),
    _menuPause(window.getSize().x, window.getSize().y),
    _menuSelectLevel(window.getSize().x, window.getSize().y),
    _menuRanking(window.getSize().x, window.getSize().y),
    _menuInstructions(window.getSize().x, window.getSize().y),
    _menuOptions(window.getSize().x, window.getSize().y),
    _menuWin(window.getSize().x, window.getSize().y),
    _menuWriteName(window.getSize().x, window.getSize().y),
    _gameplay(window),
    _gameState(MENU){

        if(!_music.openFromFile("resources/Audios/Musica.wav")){
            std::cout<<"No se pudo cargar 'Musica.wav'";
            exit(-1);
        }
        _music.setLoop(true);
        _music.setVolume(7.0f);
        _music.play();
}

void Director::update(){
    while (_window.pollEvent(event)){
        if (event.type == sf::Event::Closed){
            _window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::P) {
                if(!_isPaused && _gameState == GAMEPLAY){
                    pause();
                    _gameplay.pause();
                    _gameState = PAUSE;
                }
                else if(_isPaused && _gameState == PAUSE){
                    start();
                    _gameplay.start();
                    _gameState = GAMEPLAY;
                }
            }
        }
        if (_gameState == MENU){
            _menuMain.update(_window, event);

            if (_menuMain.isEnterPressed()){
                switch (_menuMain.getSelectedItemIndex()){
                    case 0:
                        _gameState = START_GAME;
                    break;

                    case 1:
                        _gameState = RANKING;
                    break;

                    case 2:
                        _gameState = INSTRUCTIONS;
                    break;

                    case 3:
                        _gameState = OPTIONS;
                    break;

                    case 4:
                        _window.close();
                    break;
                }
            }
        }
        else if (_gameState == START_GAME){
            _menuPlay.update(_window, event);

            if (_menuPlay.isEnterPressed()){
                switch (_menuPlay.getSelectedItemIndex()){
                    case 0: // Iniciar modo cronometrado
                        _gameplay.resetGameCompleted();
                        _gameplay.setTimeTrialMode(true);
                        _gameplay.setLevel(1);
                        _gameState = GAMEPLAY;
                        // Inicializar el modo cronometrado
                    break;

                    case 1: // Selecci¢n de niveles libre
                        _gameState = SELECT_LEVEL;
                        _gameplay.resetGameCompleted();
                        // Inicializar la selecci¢n de niveles libre
                    break;

                    case 2:
                        _menuPlay.resetSelection();
                        _menuMain.resetSelection();
                        _gameState = MENU;
                    break;
                }
            }
        }
        else if (_gameState == SELECT_LEVEL){
            _menuSelectLevel.update(_window, event);

            if (_menuSelectLevel.isEnterPressed()){
                switch (_menuSelectLevel.getSelectedItemIndex()){
                    case 0:
                        _gameplay.setTimeTrialMode(false);
                        _gameplay.setLevel(1);
                        _gameState = GAMEPLAY;
                    break;

                    case 1:
                        _gameplay.setTimeTrialMode(false);
                        _gameplay.setLevel(2);
                        _gameState = GAMEPLAY;
                    break;

                    case 2:
                        _gameplay.setTimeTrialMode(false);
                        _gameplay.setLevel(3);
                        _gameState = GAMEPLAY;
                    break;

                    case 3:
                        _gameplay.setTimeTrialMode(false);
                        _gameplay.setLevel(4);
                        _gameState = GAMEPLAY;
                    break;

                    case 4:
                        _gameplay.setTimeTrialMode(false);
                        _gameplay.setLevel(5);
                        _gameState = GAMEPLAY;
                    break;

                    case 5:
                        _gameplay.setTimeTrialMode(false);
                        _gameplay.setLevel(6);
                        _gameState = GAMEPLAY;
                    break;

                    case 6:
                        _gameplay.setTimeTrialMode(false);
                        _gameplay.setLevel(7);
                        _gameState = GAMEPLAY;
                    break;

                    case 7:
                        _gameplay.setTimeTrialMode(false);
                        _gameplay.setLevel(8);
                        _gameState = GAMEPLAY;
                    break;

                    case 8:
                        _gameplay.setTimeTrialMode(false);
                        _gameplay.setLevel(9);
                        _gameState = GAMEPLAY;
                    break;

                    case 9:
                        _menuSelectLevel.resetSelection();
                        _menuPlay.resetSelection();
                        _gameState = START_GAME;
                    break;
                }
            }
        }
        else if (_gameState == RANKING){
            _menuRanking.update(_window, event);

            if (_menuRanking.isEnterPressed()){
                switch (_menuRanking.getSelectedItemIndex()){
                    case 0:
                        _menuMain.resetSelection();
                        _gameState = MENU;
                    break;
                }
            }
        }
        else if (_gameState == INSTRUCTIONS){
            _menuInstructions.update(_window, event);

            if (_menuInstructions.isEnterPressed()){
                switch (_menuInstructions.getSelectedItemIndex()){
                    case 0:
                        _menuMain.resetSelection();
                        _gameState = MENU;
                    break;
                }
            }
        }
        else if (_gameState == OPTIONS){
            _menuOptions.update(_window, event);

            if (_menuOptions.isEnterPressed()){
                switch (_menuOptions.getSelectedItemIndex()){
                    case 0:
                        _menuOptions.setMusicActive();
                        _menuPause.setMusicActive();
                        pausePlayMusic();

                    break;

                    case 1:
                        _menuOptions.setSfxActive();
                        _menuPause.setSfxActive();
                    break;

                    case 2:
                        _menuOptions.deleteData();
                        _menuRanking.updateStrings();
                    break;

                    case 3:
                        _gameState = MENU;
                        _menuOptions.resetSelection();
                        _menuMain.resetSelection();
                    break;
                }
            }
        }
        else if (_gameState == PAUSE){
            _menuPause.update(_window, event);

            if (_menuPause.isEnterPressed()){
                switch (_menuPause.getSelectedItemIndex()){
                    case 0:
                        _menuPause.setMusicActive();
                        _menuOptions.setMusicActive();
                        pausePlayMusic();
                    break;

                    case 1:
                        _menuPause.setSfxActive();
                        _menuOptions.setSfxActive();
                    break;

                    case 2:
                        _gameState = MENU;
                        _menuPause.resetSelection();
                        _menuMain.resetSelection();
                        start();
                    break;
                }
            }
        }
        else if (_gameState == WIN){
            _menuWin.update(_window, event);

            if (_menuWin.isEnterPressed()){
                switch (_menuWin.getSelectedItemIndex()){
                    case 0:
                        _menuMain.resetSelection();

                        if (_menuRanking.isNewRecord(_menuWin.getTimeScore())){
                            _gameState = WRITE_NAME;
                            _menuWriteName.clearName();
                        }
                        else{
                            _gameState = MENU;
                        }
                    break;
                }
            }
        }
        else if (_gameState == WRITE_NAME){
            _menuWriteName.update(_window, event);

            if (_menuWriteName.isEnterPressed()){
                switch (_menuWriteName.getSelectedItemIndex()){
                    case 0:
                        Ranking ranking;

                        ranking.cargar(_menuWriteName.getName(), _menuWin.getTimeScore());

                        _menuRanking.updateRankingInformation(ranking);

                        _menuMain.resetSelection();
                        _gameState = RANKING;
                    break;
                }
            }
        }
    }

    if (_gameState == GAMEPLAY){
        if (_isPaused) {
            return;
        }
        _gameplay.update();
    }

    if (_gameplay.getGameCompleted()){
        if (_gameplay.getTimeTrialMode()){
            _gameState = WIN;
            _menuWin.setTimeScore(_gameplay.getTimeScore());
        }
        else{
            _gameState = MENU;
        }

        _gameplay.resetGameCompleted();
        _menuSelectLevel.resetSelection();
        _menuPlay.resetSelection();
        _menuMain.resetSelection();
    }

}

void Director::pausePlayMusic(){
    if(_music.getStatus() == 2){
        _music.stop();
    } else _music.play();
}

void Director::pause(){
    _isPaused = true;
}

void Director::start(){
    _isPaused = false;
}

void Director::draw(){

    _window.clear();

    if (_gameState == MENU){
        _menuMain.draw(_window);
    }
    else if (_gameState == START_GAME){
        _menuPlay.draw(_window);
    }
    else if (_gameState == SELECT_LEVEL){
        _menuSelectLevel.draw(_window);
    }
    else if (_gameState == RANKING){
        _menuRanking.draw(_window);
    }
    else if (_gameState == INSTRUCTIONS){
        _menuInstructions.draw(_window);
    }
    else if (_gameState == OPTIONS){
        _menuOptions.draw(_window);
    }
    else if (_gameState == WIN){
        _menuWin.draw(_window);
    }
    else if (_gameState == WRITE_NAME){
        _menuWriteName.draw(_window);
    }
    else if (_gameState == GAMEPLAY){
        _gameplay.draw();
    }
    else if (_gameState == PAUSE){
        _gameplay.draw();
        _menuPause.draw(_window);
    }

    _window.display();

}
