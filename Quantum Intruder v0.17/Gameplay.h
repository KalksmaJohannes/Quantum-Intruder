#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
#include "Scene6.h"
#include "Scene7.h"
#include "Scene8.h"
#include "Scene9.h"
#include "Background.h"
#include "Ranking.h"


class Gameplay{
    private:
        Scene1 _mapa1;

        Scene2 _mapa2;

        Scene3 _mapa3;

        Scene4 _mapa4;

        Scene5 _mapa5;

        Scene6 _mapa6;

        Scene7 _mapa7;

        Scene8 _mapa8;

        Scene9 _mapa9;

        Background _background;

        sf::RenderWindow& _window;

        int _level;

        bool _timeTrialMode;

        bool _gameCompleted;

        sf::Clock _chronometrer;

        sf::Time _elapsedTime;

        sf::Time _pausedTime;

        sf::Text _text;

        sf::Font _font;

        sf::Color _textColor;

        int _minutes;

        int _seconds;

        bool _isPaused = false;

        sf::Time _timeScore;

        Ranking _ranking;

    public:
        Gameplay(sf::RenderWindow& window);

        void setTimeTrialMode(bool active);

        bool getTimeTrialMode();

        void setLevel(int level);

        void resetGameCompleted();

        bool getGameCompleted();

        sf::Time getTimeScore();

        void update();

        void draw();

        void pause();

        void start();
};
