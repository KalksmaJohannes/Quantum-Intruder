#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "BackgroundMenu.h"


class MenuWin{

    private:
        int _selectedItemIndex;

        sf::Font _font;

        sf::Text _tittle;

        sf::Text _winInformation;

        BackgroundMenu _background;

        std::vector<sf::Text> _menuItems;

        bool _enterPressed;

        sf::Time _timeScore;

        std::string timeScoreToString();

        sf::Sound _sound;

        sf::SoundBuffer _soundBuffer;

    public:
        MenuWin(float width, float height);

        void update(sf::RenderWindow& window, sf::Event event);

        void draw(sf::RenderWindow& window);

        int getSelectedItemIndex();

        void setTimeScore(sf::Time timeScore);

        sf::Time getTimeScore();

        bool isEnterPressed();

        void changeVolume();
};
