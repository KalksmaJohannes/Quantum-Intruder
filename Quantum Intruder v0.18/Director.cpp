#include "Director.h"


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


    _music.openFromFile("resources/Audios/musica.mp3");
    _music.setLoop(true);
    _music.setVolume(12.0f);
    _music.play();

    _music2.openFromFile("resources/Audios/musica 2.wav");
    _music2.setLoop(true);
    _music2.setVolume(7.0f);

    _musicFinal.openFromFile("resources/Audios/musica final.wav");
    _musicFinal.setLoop(true);
    _musicFinal.setVolume(7.0f);

    _musicWin.openFromFile("resources/Audios/musica win.wav");
    _musicWin.setLoop(true);
    _musicWin.setVolume(5.0f);

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

                        changeMusic();
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

                        changeMusic();
                    break;

                    case 1:
                        _gameplay.setTimeTrialMode(false);
                        _gameplay.setLevel(2);
                        _gameState = GAMEPLAY;

                        changeMusic();
                    break;

                    case 2:
                        _gameplay.setTimeTrialMode(false);
                        _gameplay.setLevel(3);
                        _gameState = GAMEPLAY;

                        changeMusic();
                    break;

                    case 3:
                        _gameplay.setTimeTrialMode(false);
                        _gameplay.setLevel(4);
                        _gameState = GAMEPLAY;

                        changeMusic();
                    break;

                    case 4:
                        _gameplay.setTimeTrialMode(false);
                        _gameplay.setLevel(5);
                        _gameState = GAMEPLAY;

                        changeMusic();
                    break;

                    case 5:
                        _gameplay.setTimeTrialMode(false);
                        _gameplay.setLevel(6);
                        _gameState = GAMEPLAY;

                        changeMusic();
                    break;

                    case 6:
                        _gameplay.setTimeTrialMode(false);
                        _gameplay.setLevel(7);
                        _gameState = GAMEPLAY;

                        changeMusic();
                    break;

                    case 7:
                        _gameplay.setTimeTrialMode(false);
                        _gameplay.setLevel(8);
                        _gameState = GAMEPLAY;

                        changeMusic();
                    break;

                    case 8:
                        _gameplay.setTimeTrialMode(false);
                        _gameplay.setLevel(9);
                        _gameState = GAMEPLAY;

                        changeMusic();
                    break;

                    case 9:
                        _menuSelectLevel.resetSelection();
                        _menuPlay.resetSelection();
                        _gameState = START_GAME;

                        changeMusic();
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
                        pausePlaySfx();
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
                        pausePlaySfx();
                    break;

                    case 2:
                        _gameState = MENU;
                        _menuPause.resetSelection();
                        _menuMain.resetSelection();
                        _menuPlay.resetSelection();
                        _menuSelectLevel.resetSelection();
                        start();
                        changeMusic();
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
                            changeMusicWin();
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
                        changeMusicWin();
                    break;
                }
            }
        }
    }

    if (_gameState == GAMEPLAY){
        if (_isPaused) {
            return;
        }

        if (_gameplay.getTimeTrialMode() && _gameplay.getLevel() == 9) changeMusicFinal();

        _gameplay.update();
    }

    if (_gameplay.getGameCompleted()){
        changeMusic();

        if (_gameplay.getTimeTrialMode()){
            _gameState = WIN;
            _menuWin.setTimeScore(_gameplay.getTimeScore());
            changeMusicWin();
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

    if(_gameState == OPTIONS){
        if (_music.getStatus() == 2){
            _music.stop();
        }
        else{
            _music.play();
        }
    }
    else if (_gameState == PAUSE && _gameplay.getLevel() == 9 && _gameplay.getTimeTrialMode()){
        if (_musicFinal.getStatus() == 2){
            _musicFinal.stop();
        }
        else{
            _musicFinal.play();
        }
    }
    else{
        if (_music2.getStatus() == 2){
            _music2.stop();
        }
        else{
            _music2.play();
        }
    }

}

void Director::pausePlaySfx(){

    _menuMain.changeVolume();
    _menuPlay.changeVolume();
    _menuSelectLevel.changeVolume();
    _menuRanking.changeVolume();
    _menuInstructions.changeVolume();
    _menuOptions.changeVolume();
    _menuPause.changeVolume();
    _menuWin.changeVolume();
    _menuWriteName.changeVolume();
    _gameplay.changeVolume();

}

void Director::changeMusic(){

    if (_gameState == GAMEPLAY && _music.getStatus() == 2){
        _music.stop();
        _music2.play();
    }
    else if (_gameState != GAMEPLAY && _music2.getStatus() == 2){
        _music2.stop();
        _music.play();
    }
    else if (_gameState != GAMEPLAY && _musicFinal.getStatus() == 2){
        _musicFinal.stop();
        _music.play();
    }

}

void Director::changeMusicFinal(){

    if (_gameState == GAMEPLAY && _music2.getStatus() == 2){
        _music2.stop();
        _musicFinal.play();
    }

}

void Director::changeMusicWin(){

    if (_gameState == WIN && _musicFinal.getStatus() == 2){
        _musicFinal.stop();
        _musicWin.play();
    }
    else if (_gameState != WIN && _musicWin.getStatus() == 2){
        _musicWin.stop();
        _music.play();
    }

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
