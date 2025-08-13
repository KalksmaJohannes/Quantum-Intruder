#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "BackgroundMenu.h"


class MenuPlay{

    private:
        int _selectedItemIndex;

        sf::Font _font;

        sf::Text _tittle;

        BackgroundMenu _background;

        std::vector<sf::Text> _menuItems;

        bool _enterPressed;

        void moveUp();

        void moveDown();

        void updateColors();

        sf::Sound _soundNavigate;

        sf::SoundBuffer _soundBufferNavigate;

        sf::Sound _soundSelect;

        sf::SoundBuffer _soundBufferSelect;

    public:
        MenuPlay(float width, float height);

        void update(sf::RenderWindow& window, sf::Event event);

        void draw(sf::RenderWindow& window);

        int getSelectedItemIndex();

        bool isEnterPressed();

        void resetSelection();

        void changeVolume();
};
