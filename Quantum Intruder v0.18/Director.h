#pragma once

#include <iostream>
#include "MenuMain.h"
#include "MenuPlay.h"
#include "MenuSelectLevel.h"
#include "MenuRanking.h"
#include "MenuInstructions.h"
#include "MenuOptions.h"
#include "MenuWin.h"
#include "MenuWriteName.h"
#include "Gameplay.h"
#include "MenuPause.h"


enum GameState{ MENU, START_GAME, SELECT_LEVEL, RANKING, INSTRUCTIONS, OPTIONS, PAUSE, WIN, WRITE_NAME, GAMEPLAY };

class Director {

    private:
        sf::RenderWindow& _window;

        MenuMain _menuMain;

        MenuPlay _menuPlay;

        MenuPause _menuPause;

        MenuSelectLevel _menuSelectLevel;

        MenuRanking _menuRanking;

        MenuInstructions _menuInstructions;

        MenuOptions _menuOptions;

        MenuWin _menuWin;

        MenuWriteName _menuWriteName;

        Gameplay _gameplay;

        GameState _gameState;

        sf::Event event;

        bool _isPaused = false;

        sf::Clock _gameClock;

        sf::Music _music;

        sf::Music _music2;

        sf::Music _musicFinal;

        sf::Music _musicWin;

        void pause();

        void start();

        void pausePlayMusic();

        void pausePlaySfx();

        void changeMusic();

        void changeMusicFinal();

        void changeMusicWin();

    public:
        Director(sf::RenderWindow& window);

        void update();

        void draw();
};
