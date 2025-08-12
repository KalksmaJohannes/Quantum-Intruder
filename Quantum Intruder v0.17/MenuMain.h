#pragma once

#include <SFML/Graphics.hpp>
#include "BackgroundMenu.h"


class MenuMain{

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

    public:
        MenuMain(float width, float height);

        void update(sf::RenderWindow& window, sf::Event event);

        void draw(sf::RenderWindow& window);

        int getSelectedItemIndex();

        bool isEnterPressed();

        void resetSelection();
};
