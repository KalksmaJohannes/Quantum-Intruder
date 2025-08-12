#pragma once

#pragma once

#include <SFML/Graphics.hpp>
#include "BackgroundPause.h"


class MenuPause{

    private:
        int _selectedItemIndex;

        sf::Font _font;

        sf::Text _tittle;

        BackgroundPause _background;

        std::vector<sf::Text> _menuItems;

        bool _enterPressed;

        int _musicActive;

        int _sfxActive;

        void moveUp();

        void moveDown();

        void updateColors();

    public:
        MenuPause(float width, float height);

        void update(sf::RenderWindow& window, sf::Event event);

        void draw(sf::RenderWindow& window);

        int getSelectedItemIndex();

        bool isEnterPressed();

        void resetSelection();

        void setMusicActive();

        void setSfxActive();
};
